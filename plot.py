import pandas as pd
import matplotlib.pyplot as plt

# Файлы с результатами (положите рядом с этим скриптом)
FILE_WIDE = "results_wide.csv"
FILE_NARROW = "results_narrow.csv"

# Загружаем CSV
df_wide = pd.read_csv(FILE_WIDE)
df_narrow = pd.read_csv(FILE_NARROW)

# Площадь wide
plt.figure(figsize=(8,5))
plt.plot(df_wide["N"], df_wide["area"])
plt.xlabel("N")
plt.ylabel("Площадь (wide)")
plt.title("Оценка площади vs N (широкая область)")
plt.grid(True)
plt.tight_layout()
plt.savefig("plot_area_wide.png", dpi=200)
plt.close()

# Площадь narrow
plt.figure(figsize=(8,5))
plt.plot(df_narrow["N"], df_narrow["area"])
plt.xlabel("N")
plt.ylabel("Площадь (narrow)")
plt.title("Оценка площади vs N (узкая область)")
plt.grid(True)
plt.tight_layout()
plt.savefig("plot_area_narrow.png", dpi=200)
plt.close()

# Ошибка wide
plt.figure(figsize=(8,5))
plt.plot(df_wide["N"], df_wide["relative_error"])
plt.xlabel("N")
plt.ylabel("Относительная ошибка (wide)")
plt.title("Ошибка vs N (широкая область)")
plt.grid(True)
plt.tight_layout()
plt.savefig("plot_error_wide.png", dpi=200)
plt.close()

# Ошибка narrow
plt.figure(figsize=(8,5))
plt.plot(df_narrow["N"], df_narrow["relative_error"])
plt.xlabel("N")
plt.ylabel("Относительная ошибка (narrow)")
plt.title("Ошибка vs N (узкая область)")
plt.grid(True)
plt.tight_layout()
plt.savefig("plot_error_narrow.png", dpi=200)
plt.close()

print("Графики готовы:")
print("  plot_area_wide.png")
print("  plot_area_narrow.png")
print("  plot_error_wide.png")
print("  plot_error_narrow.png")
