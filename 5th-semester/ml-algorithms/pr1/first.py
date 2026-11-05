import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

kukuruz_data = pd.read_csv("Corn_hyperspectrum.csv", sep=";", decimal=",")

sample = kukuruz_data.iloc[110:160].copy()
x = sample["wavelength"].values
Y = sample["Spectr"].values

X_poly = np.column_stack([np.ones_like(x), x, x**2])
w_analytic = np.linalg.inv(X_poly.T @ X_poly) @ X_poly.T @ Y
a0_an, a1_an, a2_an = w_analytic

x_space = np.linspace(x.min(), x.max(), 200)
Y_pred_an_line = a0_an + a1_an * x_space + a2_an * (x_space**2)
Y_pred_an = a0_an + a1_an * x + a2_an * (x**2)

mse_an = np.mean((Y - Y_pred_an) ** 2)
r2_an = 1 - np.sum((Y - Y_pred_an) ** 2) / np.sum((Y - Y.mean()) ** 2)

x_mean = x.mean()
x_std = x.std()
x_norm = (x - x_mean) / x_std


class QuadraticRegression:

    def __init__(self):
        self.w = np.zeros(3)

    def _features(self, x_in):
        return np.column_stack([np.ones_like(x_in), x_in, x_in**2])

    def predict(self, x_in):
        return self._features(x_in) @ self.w

    def fit(self, x_in, Y_in, alpha=0.01, epsylon=1e-8, max_steps=10000):
        X_mat = self._features(x_in)
        n = len(Y_in)
        steps, errors = [], []

        for step in range(1, max_steps + 1):
            pred = X_mat @ self.w
            grad = -2 * (X_mat.T @ (Y_in - pred)) / n
            self.w -= alpha * grad

            error = np.mean((Y_in - pred) ** 2)
            steps.append(step)
            errors.append(error)

            if step > 1 and abs(errors[-2] - error) < epsylon:
                break
        return steps, errors


model_gd = QuadraticRegression()
steps, errors = model_gd.fit(x_norm, Y, alpha=0.05, max_steps=15000)

w0, w1, w2 = model_gd.w
a2_gd = w2 / (x_std**2)
a1_gd = (w1 / x_std) - (2 * w2 * x_mean / (x_std**2))
a0_gd = w0 - (w1 * x_mean / x_std) + (w2 * (x_mean**2) / (x_std**2))

Y_pred_gd = a0_gd + a1_gd * x + a2_gd * (x**2)
Y_pred_gd_line = a0_gd + a1_gd * x_space + a2_gd * (x_space**2)
mse_gd = np.mean((Y - Y_pred_gd) ** 2)

print(
    f"МНК: a0 = {a0_an:.4f}, a1 = {a1_an:.6f}, a2 = {a2_an:.8f} | MSE = {mse_an:.2e}, R^2 = {r2_an:.4f}"
)
print(
    f"GD:  a0 = {a0_gd:.4f}, a1 = {a1_gd:.6f}, a2 = {a2_gd:.8f} | MSE = {mse_gd:.2e} (шагов: {len(steps)})"
)

plt.figure(figsize=(10, 6))
plt.scatter(
    x, Y, color="royalblue", s=40, alpha=0.8, label="Данные спектра (50 точек)"
)
plt.plot(
    x_space,
    Y_pred_an_line,
    color="crimson",
    linewidth=2.5,
    label=f"МНК (аналитически): MSE={mse_an:.2e}",
)
plt.plot(
    x_space,
    Y_pred_gd_line,
    color="forestgreen",
    linestyle="--",
    linewidth=2,
    label=f"Градиентный спуск: MSE={mse_gd:.2e}",
)

plt.title("Параболическая регрессия: сравнение МНК и градиентного спуска")
plt.xlabel("Длина волны (wavelength), нм")
plt.ylabel("Спектральный отклик (Spectr)")
plt.legend()
plt.grid(True, linestyle=":", alpha=0.6)
plt.tight_layout()
plt.show()