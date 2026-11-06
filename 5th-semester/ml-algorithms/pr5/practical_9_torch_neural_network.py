"""
Практическое занятие №9
Тема: Создание нейронной сети на PyTorch с нуля (без autograd).
(Соответствует теме методического пособия «Практическое занятие №9.pdf», файл s5_1.ipynb)

Содержание работы:
1. Реализация базового нейрона (Neuron) с линейной комбинацией весов и смещения.
2. Реализация полносвязного слоя (Layer / Dense) для векторных и пакетных (batch) вычислений.
3. Реализация функций активации (ReLU, Softmax, Linear) с прямым и обратным проходом.
4. Реализация функций потерь (MSELoss, CategoricalCrossentropyLoss) с вычислением градиентов.
5. Обучение одного нейрона / слоя методом стохастического градиентного спуска (SGD) на задаче регрессии.
6. Построение и обучение двухслойной нейронной сети (MLP) для нелинейной аппроксимации параболы y = x^2 + шум.
7. Визуализация процесса обучения нейросети по эпохам.
"""

import sys
import os

# Подключение локального пути к torch и временного каталога matplotlib
local_site = os.path.abspath(os.path.join(os.path.dirname(__file__), "../.site-packages"))
if os.path.exists(local_site) and local_site not in sys.path:
    sys.path.insert(0, local_site)

os.environ["MPLCONFIGDIR"] = "/tmp/matplotlib_cfg"

import torch
import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_regression


# =====================================================================
# 1. Базовый Нейрон (Neuron)
# =====================================================================
class BasicNeuron:
    """Простейший нейрон для скалярного произведения с вектором входов"""
    def __init__(self, weights, bias):
        self.weights = weights
        self.bias = bias

    def forward(self, input_vec):
        return torch.dot(self.weights, input_vec) + self.bias


# =====================================================================
# 2. Слой нейронов (Layer)
# =====================================================================
class SimpleLayer:
    """Слой нейронов с поддержкой векторных и матричных (батчевых) входов"""
    def __init__(self, weights, biases):
        self.weights = weights
        self.biases = biases

    def forward_vector(self, input_vec):
        return torch.mv(self.weights, input_vec) + self.biases

    def forward_batch(self, inputs):
        return inputs @ self.weights.T + self.biases


# =====================================================================
# 3. Функции активации
# =====================================================================
class Activation_ReLU:
    """Функция активации ReLU с прямым и обратным проходом"""
    def forward(self, inputs):
        self.inputs = inputs
        self.output = inputs.clip(min=0)
        return self.output

    def backward(self, dvalues):
        with torch.no_grad():
            self.dinputs = dvalues.clone()
            self.dinputs[self.inputs <= 0] = 0.0


class Activation_Linear:
    """Линейная функция активации (тождественная)"""
    def forward(self, inputs):
        self.inputs = inputs
        self.output = inputs
        return self.output

    def backward(self, dvalues):
        with torch.no_grad():
            self.dinputs = dvalues.clone()


class Softmax:
    """Функция активации Softmax для многоклассовой классификации"""
    def forward(self, inputs):
        exp = torch.exp(inputs - torch.max(inputs, dim=1, keepdim=True)[0])
        probs = exp / exp.sum(dim=1, keepdim=True)
        return probs


# =====================================================================
# 4. Функции потерь (Loss)
# =====================================================================
class Loss:
    def calculate(self, output, y):
        sample_losses = self.forward(output, y)
        data_loss = sample_losses.mean()
        return data_loss


class MSELoss(Loss):
    """Среднеквадратичная ошибка (MSE) с градиентом"""
    def forward(self, y_pred, y_true):
        sample_losses = torch.mean((y_true - y_pred) ** 2, dim=1)
        return sample_losses

    def backward(self, dvalues, y_true):
        with torch.no_grad():
            self.dinputs = -2.0 * (y_true - dvalues) / len(dvalues)


class CategoricalCrossentropyLoss(Loss):
    """Категориальная кросс-энтропия"""
    def forward(self, y_pred, y_true):
        y_pred_clipped = torch.clamp(y_pred, 1e-15, 1.0 - 1e-15)
        if len(y_true.shape) == 1:
            correct_confidences = y_pred_clipped[range(len(y_pred)), y_true]
        else:
            correct_confidences = torch.sum(y_pred_clipped * y_true, dim=1)
        negative_log_likelihoods = -torch.log(correct_confidences)
        return negative_log_likelihoods


# =====================================================================
# 5. Обучаемый Нейрон с ручным градиентным спуском
# =====================================================================
class TrainableNeuron:
    """Нейрон с аналитическим вычислением градиентов для SGD"""
    def __init__(self, n_inputs):
        self.weights = torch.randn(n_inputs, dtype=torch.float32)
        self.bias = torch.tensor(0.0, dtype=torch.float32)

    def forward(self, inputs):
        self.inputs = inputs
        return inputs @ self.weights + self.bias

    def backward(self, dvalues):
        with torch.no_grad():
            self.dweights = self.inputs.T.mv(dvalues)
            self.dbiases = dvalues.sum()


class MSELossNeuron:
    """MSE для отдельного нейрона"""
    def forward(self, y_pred, y_true):
        return (y_pred - y_true) ** 2

    def backward(self, y_pred, y_true):
        with torch.no_grad():
            self.dinputs = -2.0 * (y_true - y_pred) / len(y_true)


# =====================================================================
# 6. Полносвязный слой Dense с прямым и обратным распространением
# =====================================================================
class Dense:
    """Полносвязный слой нейронной сети с вычислением dweights, dbiases, dinputs"""
    def __init__(self, n_inputs, n_neurons):
        self.weights = torch.randn(n_inputs, n_neurons, dtype=torch.float32) * 0.1
        self.biases = torch.zeros(n_neurons, dtype=torch.float32)

    def forward(self, inputs):
        self.inputs = inputs
        self.output = inputs @ self.weights + self.biases
        return self.output

    def backward(self, dvalues):
        with torch.no_grad():
            self.dweights = self.inputs.T @ dvalues
            self.dbiases = dvalues.sum(dim=0)
            self.dinputs = dvalues @ self.weights.T


# =====================================================================
# 7. Демонстрация и эксперименты
# =====================================================================
def run_all_experiments():
    print("=" * 70)
    print("ПРАКТИЧЕСКОЕ ЗАНЯТИЕ №9: СОЗДАНИЕ НЕЙРОННОЙ СЕТИ НА TORCH С НУЛЯ")
    print("=" * 70)

    # 1. Базовый расчет нейрона (из методички)
    print("\n--- 1. Базовый расчет нейрона ---")
    inputs = torch.tensor([1.0, 2.0, 3.0, 2.5])
    weights = torch.tensor([0.2, 0.8, -0.5, 1.0])
    bias = 2.0
    neuron = BasicNeuron(weights, bias)
    res = neuron.forward(inputs)
    print(f"Входы  : {inputs.tolist()}")
    print(f"Веса   : {weights.tolist()}, bias = {bias}")
    print(f"Выход  : {res.item():.4f} (ожидается: 4.8000)")

    # 2. Пакетная обработка слоем (из методички)
    print("\n--- 2. Обработка батчем в слое Layer ---")
    inputs_batch = torch.tensor([[1.0, 2.0, 3.0, 2.5],
                                 [2.0, 5.0, -1.0, 2.0],
                                 [-1.5, 2.7, 3.3, -0.8]])
    layer_weights = torch.tensor([[0.2, 0.8, -0.5, 1.0],
                                  [0.5, -0.91, 0.26, -0.5],
                                  [-0.26, -0.27, 0.17, 0.87]])
    layer_biases = torch.tensor([2.0, 3.0, 0.5])
    layer = SimpleLayer(layer_weights, layer_biases)
    out_batch = layer.forward_batch(inputs_batch)
    print("Выход слоя (размерность 3x3):")
    print(out_batch)

    # 3. Функции активации
    print("\n--- 3. Функции активации (ReLU, Softmax) ---")
    relu_out = Activation_ReLU().forward(out_batch)
    softmax_out = Softmax().forward(out_batch)
    print("После ReLU (отрицательные обнулены):")
    print(relu_out)
    print("После Softmax (вероятности по строкам):")
    print(softmax_out)
    print("Сумма вероятностей по объектам:", softmax_out.sum(dim=1).tolist())

    # 4. Обучение одного нейрона на make_regression
    print("\n--- 4. Обучение TrainableNeuron методом SGD на make_regression ---")
    X_np, y_np, coef_true = make_regression(n_samples=100, n_features=4, n_informative=4, coef=True, bias=0.0, random_state=42)
    X_t = torch.from_numpy(X_np).to(dtype=torch.float32)
    y_t = torch.from_numpy(y_np).to(dtype=torch.float32)

    neuron_train = TrainableNeuron(4)
    loss_neuron = MSELossNeuron()
    lr = 0.05

    for epoch in range(101):
        y_pred = neuron_train.forward(X_t)
        l = loss_neuron.forward(y_pred, y_t)
        loss_neuron.backward(y_pred, y_t)
        neuron_train.backward(loss_neuron.dinputs)

        neuron_train.weights -= lr * neuron_train.dweights
        neuron_train.bias -= lr * neuron_train.dbiases

        if epoch % 20 == 0:
            print(f"  Эпоха {epoch:3d} | MSE Loss: {l.mean().item():.8f}")

    print("\nИстинные коэффициенты задачи регрессии :", np.round(coef_true, 4).tolist())
    print("Выученные веса нейрона (SGD)           :", np.round(neuron_train.weights.tolist(), 4))

    # 5. Обучение слоя Dense(4, 1) на make_regression
    print("\n--- 5. Обучение полносвязного слоя Dense(4, 1) ---")
    dense1 = Dense(4, 1)
    loss_dense = MSELoss()
    y_col = y_t.view(-1, 1)

    for epoch in range(101):
        out = dense1.forward(X_t)
        data_loss = loss_dense.calculate(out, y_col)
        loss_dense.backward(out, y_col)
        dense1.backward(loss_dense.dinputs)

        dense1.weights -= lr * dense1.dweights
        dense1.biases -= lr * dense1.dbiases

        if epoch % 20 == 0:
            print(f"  Эпоха {epoch:3d} | Dense MSE Loss: {data_loss.item():.8f}")

    print("Веса Dense слоя:", np.round(dense1.weights.flatten().tolist(), 4))

    # 6. Нелинейная регрессия: Двухслойный перцептрон (MLP)
    print("\n--- 6. Аппроксимация нелинейной функции y = x^2 + шум двухслойной нейросетью ---")
    torch.manual_seed(42)
    X_curve = torch.linspace(-1, 1, 100).view(-1, 1)
    y_curve = X_curve.pow(2) + 0.2 * torch.rand(X_curve.size())

    fc1 = Dense(1, 10)
    relu1 = Activation_ReLU()
    fc2 = Dense(10, 1)
    loss_mlp = MSELoss()
    lr_mlp = 0.02

    epochs = 2001
    save_epochs = [0, 200, 400, 800, 1400, 2000]
    predictions_history = {}
    losses_history = []

    for epoch in range(epochs):
        # Прямой проход (forward)
        out1 = fc1.forward(X_curve)
        out2 = relu1.forward(out1)
        out3 = fc2.forward(out2)

        data_loss = loss_mlp.calculate(out3, y_curve)
        losses_history.append(data_loss.item())

        if epoch in save_epochs:
            predictions_history[epoch] = out3.detach().clone()
            print(f"  Эпоха {epoch:4d} | MSE Loss: {data_loss.item():.6f}")

        # Обратный проход (backward)
        loss_mlp.backward(out3, y_curve)
        fc2.backward(loss_mlp.dinputs)
        relu1.backward(fc2.dinputs)
        fc1.backward(relu1.dinputs)

        # Обновление параметров весов (SGD)
        fc1.weights -= lr_mlp * fc1.dweights
        fc1.biases -= lr_mlp * fc1.dbiases
        fc2.weights -= lr_mlp * fc2.dweights
        fc2.biases -= lr_mlp * fc2.dbiases

    # 7. Визуализация результатов обучения
    fig, axes = plt.subplots(2, 3, figsize=(15, 9))
    axes = axes.flatten()

    for idx, ep in enumerate(save_epochs):
        ax = axes[idx]
        ax.scatter(X_curve.numpy(), y_curve.numpy(), color="orange", s=25, alpha=0.7, label="Данные (x^2 + шум)")
        ax.plot(X_curve.numpy(), predictions_history[ep].numpy(), color="green", lw=2.5, label="Прогноз нейросети")
        ax.set_title(f"Эпоха {ep} (Loss: {losses_history[ep]:.4f})", fontsize=11)
        ax.set_xlim(-1.1, 1.1)
        ax.set_ylim(-0.2, 1.4)
        ax.grid(True, linestyle="--", alpha=0.5)
        ax.legend(fontsize=9)

    plt.suptitle("Динамика аппроксимации параболы многослойной нейросетью (Dense(1,10) -> ReLU -> Dense(10,1))", fontsize=13)
    plt.tight_layout()
    plt.savefig("neural_network_learning_dynamics.png", dpi=150)
    print("\nГрафик динамики обучения сохранен в 'neural_network_learning_dynamics.png'.")

    plt.figure(figsize=(8, 4))
    plt.plot(losses_history, color="blue", lw=2)
    plt.title("Кривая обучения (MSE Loss по эпохам)")
    plt.xlabel("Эпоха")
    plt.ylabel("MSE Loss")
    plt.grid(True, linestyle="--", alpha=0.5)
    plt.tight_layout()
    plt.savefig("loss_curve.png", dpi=150)
    print("Кривая ошибки сохранена в 'loss_curve.png'.")

    print("\nВсе тесты и эксперименты успешно завершены.")


if __name__ == "__main__":
    run_all_experiments()

