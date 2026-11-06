
import os
import time
from pathlib import Path

os.environ.setdefault("MPLCONFIGDIR", "/tmp/matplotlib_cfg")

import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
from sklearn.metrics import (
    ConfusionMatrixDisplay,
    accuracy_score,
    confusion_matrix,
    f1_score,
    precision_score,
    recall_score,
    roc_auc_score,
    roc_curve,
)
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler


class LogisticRegressionGD(object):

    def __init__(self):
        self.a = np.zeros(2).reshape(1, 2)

    def sigmoid(self, x):
        x_arr = np.asarray(x, dtype=np.float64)
        z = np.clip(x_arr @ self.a, -500.0, 500.0)
        return 1.0 / (1.0 + np.exp(-z))

    def predict(self, x):
        return self.sigmoid(x)

    def predict_classes(self, x, threshold=0.5):
        return (self.predict(x) > threshold).astype(np.int64)

    def coefs(self):
        return self.a

    def LogLikelihood(self, x, Y):
        Y_arr = np.asarray(Y, dtype=np.float64).reshape(-1, 1)
        p = np.clip(self.predict(x), 1e-12, 1.0 - 1e-12)
        return float((Y_arr * np.log(p) + (1.0 - Y_arr) * np.log(1.0 - p)).sum())

    def CrossEntropy(self, x, Y):
        Y_arr = np.asarray(Y, dtype=np.float64).reshape(-1, 1)
        p = np.clip(self.predict(x), 1e-12, 1.0 - 1e-12)
        return float((-Y_arr * np.log(p) - (1.0 - Y_arr) * np.log(1.0 - p)).sum())

    def accuracy(self, x, Y, threshold=0.5):
        Y_arr = np.asarray(Y, dtype=np.float64).reshape(-1, 1)
        return float(((self.predict(x) > threshold) == Y_arr).mean())

    def f1(self, x, Y, threshold=0.5):
        Y_arr = np.asarray(Y, dtype=np.int64).ravel()
        preds = self.predict_classes(x, threshold=threshold).ravel()
        return float(f1_score(Y_arr, preds, zero_division=0))

    def fit(self, x, Y, alpha=0.01, epsylon=0.01, max_steps=10000, Rtype="LL"):
        x_arr = np.asarray(x, dtype=np.float64)
        Y_arr = np.asarray(Y, dtype=np.float64).reshape(-1, 1)
        n_samples = x_arr.shape[0]

        self.a = np.zeros(x_arr.shape[1], dtype=np.float64).reshape(x_arr.shape[1], 1)
        steps, errors = [], []
        step = 0

        for _ in range(max_steps):
            p = np.clip(self.predict(x_arr), 1e-12, 1.0 - 1e-12)
            if Rtype == "LL":
                # а) Максимизация логарифмического правдоподобия методом градиентного подъема
                new_error = float((Y_arr * np.log(p) + (1.0 - Y_arr) * np.log(1.0 - p)).sum())
                dT_a = (x_arr.T @ (Y_arr - p)) / n_samples
                self.a += alpha * dT_a
            elif Rtype == "CE":
                # б) Минимизация функции потерь (кросс-энтропии) методом градиентного спуска
                new_error = float((-Y_arr * np.log(p) - (1.0 - Y_arr) * np.log(1.0 - p)).sum())
                dT_a = -(x_arr.T @ (Y_arr - p)) / n_samples
                self.a -= alpha * dT_a
            else:
                raise ValueError(f"Неизвестный режим Rtype={Rtype}. Ожидается 'LL' или 'CE'.")

            step += 1
            steps.append(step)
            errors.append(new_error)

        return steps, errors


def run_advertising_demo(base_dir: Path):
    print("=" * 80)
    print("ЧАСТЬ 1. Демонстрационная задача (расходы на рекламу и эффект)")
    print("=" * 80)

    x = pd.DataFrame(
        np.array([39, 36, 60, 21, 27, 12, 51, 57, 54, 42, 18, 9, 48, 66, 6, 30, 24, 33, 15, 21, 100, 200])
    )
    Y = pd.DataFrame(
        np.array([1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1])
    )

    intercept = np.ones((x.shape[0], 1))
    x_ = pd.DataFrame(np.concatenate((intercept, x), axis=1))

    start_time_CE = time.time()
    regr_CE = LogisticRegressionGD()
    steps_CE, errors_CE = regr_CE.fit(x_, Y, alpha=0.01, epsylon=0.01, max_steps=10000, Rtype="CE")
    time_CE = time.time() - start_time_CE

    start_time_LL = time.time()
    regr_LL = LogisticRegressionGD()
    steps_LL, errors_LL = regr_LL.fit(x_, Y, alpha=0.01, epsylon=0.01, max_steps=10000, Rtype="LL")
    time_LL = time.time() - start_time_LL

    acc_CE = regr_CE.accuracy(x_, Y)
    acc_LL = regr_LL.accuracy(x_, Y)
    f1_CE = regr_CE.f1(x_, Y)
    f1_LL = regr_LL.f1(x_, Y)

    print(f"[CE - Градиентный спуск]   Время: {time_CE:.4f} с | Accuracy: {acc_CE:.4f} | F1: {f1_CE:.4f}")
    print(f"Коэффициенты a_CE: {regr_CE.coefs().ravel()}")
    print(f"[LL - Градиентный подъем]  Время: {time_LL:.4f} с | Accuracy: {acc_LL:.4f} | F1: {f1_LL:.4f}")
    print(f"Коэффициенты a_LL: {regr_LL.coefs().ravel()}")

    fig, axes = plt.subplots(1, 2, figsize=(13, 4.8))
    x_grid = np.linspace(0, 210, 300).reshape(-1, 1)
    x_grid_b = np.hstack([np.ones_like(x_grid), x_grid])

    axes[0].scatter(x.values, Y.values, color="royalblue", s=45, label="Исходные данные (x, Y)")
    axes[0].plot(x_grid, regr_CE.predict(x_grid_b), color="crimson", lw=2.2, label="Сигмоида P(Y=1|x)")
    axes[0].axhline(0.5, color="gray", ls="--", lw=1, label="Порог 0.5")
    axes[0].set_title("Демо-задача: Логистическая регрессия")
    axes[0].set_xlabel("Расходы на рекламу (x)")
    axes[0].set_ylabel("Вероятность эффекта P(Y=1)")
    axes[0].legend()
    axes[0].grid(True, alpha=0.3)

    axes[1].plot(steps_CE, errors_CE, label="Cross-Entropy (CE, спуск)", color="crimson", lw=2)
    axes[1].plot(steps_LL, errors_LL, label="Log-Likelihood (LL, подъем)", color="teal", lw=2)
    axes[1].axhline(0.0, color="black", lw=0.8, ls=":")
    axes[1].set_title("Сходимость CE и LL (симметрия относительно 0)")
    axes[1].set_xlabel("Шаг итерации")
    axes[1].set_ylabel("Значение целевой функции")
    axes[1].legend()
    axes[1].grid(True, alpha=0.3)

    plt.tight_layout()
    plt.savefig(base_dir / "demo_logistic_convergence.png", dpi=150)
    plt.close(fig)


def preprocess_insclass_data(csv_path: Path):
    """
    Разделение параметров (признаков) реального датасета insclass_train.csv (151 406 строк, 29 столбцов)
    по типам данных и информативности.
    """
    df = pd.read_csv(csv_path)
    print("\n" + "=" * 80)
    print("ЧАСТЬ 2. Анализ и разделение признаков реального датасета insclass_train.csv")
    print("=" * 80)
    print(f"Размер исходного датасета: {df.shape[0]} строк x {df.shape[1]} столбцов")
    print(f"Распределение целевого признака target:\n{df['target'].value_counts()} (доля класса 1: {df['target'].mean()*100:.2f}%)")

    # 1. Отделяем неинформативные (константные и почти полностью пустые) параметры:
    # - variable_3: константный признак (только одно значение 0 во всех 151 406 строках)
    # - variable_15: 99.99% пропусков (151 393 NaN)
    # - variable_9:  88.79% пропусков (134 436 NaN)
    # - variable_7:  63.17% пропусков (95 639 NaN)
    dropped_cols = ["variable_3", "variable_7", "variable_9", "variable_15"]

    # 2. Отделяем категориальные строковые признаки (dtype == object):
    # 2а) Низкокардинальные категориальные признаки -> One-Hot Encoding (pd.get_dummies)
    cat_low_cols = ["variable_1", "variable_5", "variable_20", "variable_28"]
    # 2б) Высококардинальные категориальные признаки (марка variable_21: 192 уник., модель variable_22: 1475 уник.)
    #     -> Frequency Encoding (кодирование частотой встречаемости, чтобы не раздувать матрицу на 1667 столбцов)
    cat_high_cols = ["variable_21", "variable_22"]

    # 3. Отделяем бинарные признаки (значения 0/1):
    binary_cols = [
        "variable_2", "variable_8", "variable_10", "variable_11", "variable_17",
        "variable_23", "variable_24", "variable_25", "variable_26",
    ]

    # 4. Отделяем непрерывные/дискретные числовые признаки (требующие масштабирования StandardScaler):
    numeric_cols = [
        "variable_4", "variable_6", "variable_12", "variable_13", "variable_14",
        "variable_16", "variable_18", "variable_19", "variable_27",
    ]

    print("\nСводка разделения 28 признаков (variable_1 .. variable_28):")
    print(f"  1) Удаленные неинформативные/пустые ({len(dropped_cols)}): {dropped_cols}")
    print(f"  2) Категориальные низкокардинальные -> One-Hot ({len(cat_low_cols)}): {cat_low_cols}")
    print(f"  3) Категориальные высококардинальные -> Frequency ({len(cat_high_cols)}): {cat_high_cols}")
    print(f"  4) Бинарные индикаторы 0/1 ({len(binary_cols)}): {binary_cols}")
    print(f"  5) Числовые непрерывные/дискретные -> StandardScaler ({len(numeric_cols)}): {numeric_cols}")

    df_clean = df.drop(columns=dropped_cols).copy()

    # Заполнение пропусков: для числовых и бинарных — медианой, для категориальных — модой
    for col in numeric_cols + binary_cols:
        df_clean[col] = df_clean[col].fillna(df_clean[col].median())
    for col in cat_low_cols:
        df_clean[col] = df_clean[col].fillna(df_clean[col].mode()[0])

    # Frequency encoding для высококардинальных категориальных признаков (марка и модель ТС)
    for col in cat_high_cols:
        freq_map = df_clean[col].value_counts(normalize=True)
        df_clean[col] = df_clean[col].map(freq_map).astype(np.float64)

    # One-Hot Encoding для низкокардинальных категориальных признаков
    df_encoded = pd.get_dummies(df_clean, columns=cat_low_cols, drop_first=True, dtype=np.float64)

    feature_names = [c for c in df_encoded.columns if c != "target"]
    X = df_encoded[feature_names].values.astype(np.float64)
    y = df_encoded["target"].values.reshape(-1, 1).astype(np.float64)

    X_train, X_test, y_train, y_test = train_test_split(
        X, y, test_size=0.20, random_state=42, stratify=y
    )

    scaler = StandardScaler()
    X_train_scaled = scaler.fit_transform(X_train)
    X_test_scaled = scaler.transform(X_test)

    # Добавляем столбец единиц (свободный член / intercept)
    X_train_b = np.hstack([np.ones((X_train_scaled.shape[0], 1)), X_train_scaled])
    X_test_b = np.hstack([np.ones((X_test_scaled.shape[0], 1)), X_test_scaled])

    print(f"\nРазмер матрицы признаков после кодирования и добавления intercept:")
    print(f"  X_train_b: {X_train_b.shape}, X_test_b: {X_test_b.shape}")
    return X_train_b, X_test_b, y_train, y_test, feature_names


def run_insclass_experiment(base_dir: Path):
    """Часть 2: Обучение и сравнение способов (а) LL и (б) CE на реальном insclass_train.csv."""
    csv_path = base_dir / "insclass_train.csv"
    X_train_b, X_test_b, y_train, y_test, feature_names = preprocess_insclass_data(csv_path)

    alpha = 0.1
    max_steps = 1000

    print("\n" + "-" * 80)
    print(f"Запуск обучения LogisticRegressionGD (alpha={alpha}, max_steps={max_steps})...")
    print("-" * 80)

    # Способ а) Максимизация логарифмического правдоподобия (LL) методом градиентного подъема
    t0_ll = time.perf_counter()
    model_ll = LogisticRegressionGD()
    steps_ll, hist_ll = model_ll.fit(X_train_b, y_train, alpha=alpha, max_steps=max_steps, Rtype="LL")
    time_ll = time.perf_counter() - t0_ll

    # Способ б) Минимизация кросс-энтропии (CE) методом градиентного спуска
    t0_ce = time.perf_counter()
    model_ce = LogisticRegressionGD()
    steps_ce, hist_ce = model_ce.fit(X_train_b, y_train, alpha=alpha, max_steps=max_steps, Rtype="CE")
    time_ce = time.perf_counter() - t0_ce

    # Метрики при стандартном пороге 0.5 и при пороге 0.15 (с учетом дисбаланса классов 9.55%)
    acc_train_ll = model_ll.accuracy(X_train_b, y_train, threshold=0.5)
    acc_test_ll = model_ll.accuracy(X_test_b, y_test, threshold=0.5)
    f1_train_ll = model_ll.f1(X_train_b, y_train, threshold=0.5)
    f1_test_ll = model_ll.f1(X_test_b, y_test, threshold=0.5)
    f1_test_ll_bal = model_ll.f1(X_test_b, y_test, threshold=0.15)

    acc_train_ce = model_ce.accuracy(X_train_b, y_train, threshold=0.5)
    acc_test_ce = model_ce.accuracy(X_test_b, y_test, threshold=0.5)
    f1_train_ce = model_ce.f1(X_train_b, y_train, threshold=0.5)
    f1_test_ce = model_ce.f1(X_test_b, y_test, threshold=0.5)
    f1_test_ce_bal = model_ce.f1(X_test_b, y_test, threshold=0.15)

    prob_test_ce = model_ce.predict(X_test_b).ravel()
    roc_auc = roc_auc_score(y_test.ravel(), prob_test_ce)
    weight_diff = float(np.linalg.norm(model_ll.coefs() - model_ce.coefs()))

    results_df = pd.DataFrame(
        [
            {
                "Метод": "а) Градиентный подъем (LL)",
                "Время (сек)": round(time_ll, 4),
                "Accuracy (train)": round(acc_train_ll, 4),
                "Accuracy (test, thr=0.5)": round(acc_test_ll, 4),
                "F1 (test, thr=0.5)": round(f1_test_ll, 4),
                "F1 (test, thr=0.15)": round(f1_test_ll_bal, 4),
                "ROC-AUC (test)": round(roc_auc, 4),
            },
            {
                "Метод": "б) Градиентный спуск (CE)",
                "Время (сек)": round(time_ce, 4),
                "Accuracy (train)": round(acc_train_ce, 4),
                "Accuracy (test, thr=0.5)": round(acc_test_ce, 4),
                "F1 (test, thr=0.5)": round(f1_test_ce, 4),
                "F1 (test, thr=0.15)": round(f1_test_ce_bal, 4),
                "ROC-AUC (test)": round(roc_auc, 4),
            },
        ]
    )
    print("\nСравнительная таблица результатов на реальном датасете insclass_train.csv:")
    print(results_df.to_string(index=False))
    print(f"\nНорма разности векторов весов ||a_LL - a_CE||_2 = {weight_diff:.3e}")

    # Построение графиков для отчета
    fig, axes = plt.subplots(1, 3, figsize=(17, 5))

    axes[0].plot(steps_ll, hist_ll, color="teal", lw=2, label="Log-Likelihood (LL, подъем)")
    axes[0].plot(steps_ce, hist_ce, color="crimson", lw=2, label="Cross-Entropy (CE, спуск)")
    axes[0].axhline(0, color="black", ls=":", lw=0.8)
    axes[0].set_title("Сходимость LL и CE на insclass_train.csv")
    axes[0].set_xlabel("Итерация")
    axes[0].set_ylabel("Значение функции (суммарное)")
    axes[0].legend()
    axes[0].grid(True, alpha=0.3)

    cm = confusion_matrix(y_test.ravel(), model_ce.predict_classes(X_test_b, threshold=0.5).ravel())
    disp = ConfusionMatrixDisplay(confusion_matrix=cm, display_labels=["Не рисковый (0)", "Рисковый (1)"])
    disp.plot(ax=axes[1], cmap="Blues", colorbar=False)
    axes[1].set_title("Матрица ошибок (Test, порог 0.5)")

    fpr, tpr, _ = roc_curve(y_test.ravel(), prob_test_ce)
    axes[2].plot(fpr, tpr, color="darkorange", lw=2.2, label=f"ROC-кривая (AUC = {roc_auc:.4f})")
    axes[2].plot([0, 1], [0, 1], color="navy", ls="--", lw=1.2, label="Случайный классификатор")
    axes[2].set_title("ROC-кривая на тестовой выборке")
    axes[2].set_xlabel("False Positive Rate (FPR)")
    axes[2].set_ylabel("True Positive Rate (TPR)")
    axes[2].legend(loc="lower right")
    axes[2].grid(True, alpha=0.3)

    plt.tight_layout()
    plt.savefig(base_dir / "insclass_results.png", dpi=150)
    plt.close(fig)


if __name__ == "__main__":
    base_dir = Path(__file__).resolve().parent
    run_advertising_demo(base_dir)
    run_insclass_experiment(base_dir)
