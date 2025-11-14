#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#include <algorithm>

struct Circle {
    double x, y, r, r2;
};

inline bool inside(const Circle &c, double px, double py) {
    double dx = px - c.x;
    double dy = py - c.y;
    return dx*dx + dy*dy <= c.r2;
}

// точная площадь из постановки
double exact_area() {
    double S_T = 0.5;
    double S_C1 = 0.25 * M_PI - 0.5;
    double theta = asin(0.8);
    double S_C2 = 1.25 * (theta - 0.8);
    return S_T + S_C1 + 2.0 * S_C2;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // окружности по условию
    Circle c1{1.0, 1.0, 1.0};
    Circle c2{1.5, 2.0, std::sqrt(3.0) / 2.0};
    Circle c3{2.0, 1.5, std::sqrt(3.0) / 2.0};

    c1.r2 = c1.r * c1.r;
    c2.r2 = c2.r * c2.r;
    c3.r2 = c3.r * c3.r;

    // широкая область
    double lx_wide = std::min({c1.x - c1.r, c2.x - c2.r, c3.x - c3.r});
    double rx_wide = std::max({c1.x + c1.r, c2.x + c2.r, c3.x + c3.r});
    double ly_wide = std::min({c1.y - c1.r, c2.y - c2.r, c3.y - c3.r});
    double ry_wide = std::max({c1.y + c1.r, c2.y + c2.r, c3.y + c3.r});

    // узкая область пересечение проекций
    double lx_narrow = std::max({c1.x - c1.r, c2.x - c2.r, c3.x - c3.r});
    double rx_narrow = std::min({c1.x + c1.r, c2.x + c2.r, c3.x + c3.r});
    double ly_narrow = std::max({c1.y - c1.r, c2.y - c2.r, c3.y - c3.r});
    double ry_narrow = std::min({c1.y + c1.r, c2.y + c2.r, c3.y + c3.r});

    if (lx_narrow >= rx_narrow || ly_narrow >= ry_narrow) {
        std::cerr << "Ошибка: узкая область пуста!\n";
        return 1;
    }

    // точная площадь
    double S_exact = exact_area();
    std::cerr << "Exact area = " << S_exact << "\n";

    // CSV файлы
    std::ofstream fout_wide("results_wide.csv");
    std::ofstream fout_narrow("results_narrow.csv");

    fout_wide << "N,area,relative_error\n";
    fout_narrow << "N,area,relative_error\n";

    // монте-карло
    std::mt19937_64 rng(std::random_device{}());

    for (int N = 100; N <= 100000; N += 500) {
        // широкая область
        {
            std::uniform_real_distribution<> dx(lx_wide, rx_wide);
            std::uniform_real_distribution<> dy(ly_wide, ry_wide);

            int M = 0;
            for (int i = 0; i < N; i++) {
                double x = dx(rng), y = dy(rng);
                if (inside(c1, x, y) && inside(c2, x, y) && inside(c3, x, y)) {
                    M++;
                }
            }

            double area_box = (rx_wide - lx_wide) * (ry_wide - ly_wide);
            double S_MC = (double)M / N * area_box;
            double err = std::abs(S_MC - S_exact) / S_exact;
            fout_wide << N << "," << S_MC << "," << err << "\n";
        }
        // узкая область
        {
            std::uniform_real_distribution<> dx(lx_narrow, rx_narrow);
            std::uniform_real_distribution<> dy(ly_narrow, ry_narrow);

            int M = 0;
            for (int i = 0; i < N; i++) {
                double x = dx(rng), y = dy(rng);
                if (inside(c1, x, y) && inside(c2, x, y) && inside(c3, x, y)) {
                    M++;
                }
            }

            double area_box = (rx_narrow - lx_narrow) * (ry_narrow - ly_narrow);
            double S_MC = (double)M / N * area_box;
            double err = std::abs(S_MC - S_exact) / S_exact;
            fout_narrow << N << "," << S_MC << "," << err << "\n";
        }
    }
    fout_wide.close();
    fout_narrow.close();

    std::cout << "Готово! Файлы:\n";
    std::cout << "  results_wide.csv\n";
    std::cout << "  results_narrow.csv\n";

    return 0;
}
