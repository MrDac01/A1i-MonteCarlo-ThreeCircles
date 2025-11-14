    #include <iostream>
    #include <iomanip>
    #include <algorithm>
    #include <random>

    struct Circle { double x, y, r, r2; };

    inline bool inside(const Circle &c, double px, double py) {
        double dx = px - c.x;
        double dy = py - c.y;
        return dx*dx + dy*dy <= c.r2;
    }

    int main() {
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);

        Circle c1, c2, c3;
        if (!(std::cin >> c1.x >> c1.y >> c1.r)) return 0;
        if (!(std::cin >> c2.x >> c2.y >> c2.r)) return 0;
        if (!(std::cin >> c3.x >> c3.y >> c3.r)) return 0;

        c1.r2 = c1.r * c1.r;
        c2.r2 = c2.r * c2.r;
        c3.r2 = c3.r * c3.r;

        double lx = std::max({c1.x - c1.r, c2.x - c2.r, c3.x - c3.r});
        double rx = std::min({c1.x + c1.r, c2.x + c2.r, c3.x + c3.r});
        double ly = std::max({c1.y - c1.r, c2.y - c2.r, c3.y - c3.r});
        double ry = std::min({c1.y + c1.r, c2.y + c2.r, c3.y + c3.r});


        if (lx >= rx || ly >= ry) {
            std::cout.setf(std::ios::fixed); std::cout << std::setprecision(12) << 0.0 << "\n";
            return 0;
        }

        const int N = 2000000;
        std::mt19937_64 rng(123456); // фиксируем seed для стабильности
        std::uniform_real_distribution<> dx(lx, rx);
        std::uniform_real_distribution<> dy(ly, ry);

        int hitInTriangle = 0;

        for (int i = 0; i < N; i++) {
            double x = dx(rng);
            double y = dy(rng);
            if (inside(c1, x, y) && inside(c2, x, y) && inside(c3, x, y)) {
                ++hitInTriangle;
            }
        }

        double area_box = (rx - lx) * (ry - ly);
        double area = double(hitInTriangle) / double(N) * area_box;

        std::cout << std::fixed << std::setprecision(12) << area << "\n";

        return 0;
    }
