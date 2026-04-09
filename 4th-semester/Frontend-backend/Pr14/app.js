const form = document.getElementById('todo-form');
const input = document.getElementById('todo-input');
const list = document.getElementById('todo-list');

// задачи с localstorage
function loadTasks() {
    const tasks = JSON.parse(localStorage.getItem('tasks') || '[]');
    list.innerHTML = tasks.map((task, index) =>
        `<li class="task-item">
            <span>${task}</span>
            <button class="delete-btn" onclick="deleteTask(${index})">✖</button>
        </li>`
    ).join('');
}

// функция добвления задачи
function addTask(text) {
    const tasks = JSON.parse(localStorage.getItem('tasks') || '[]');
    tasks.push(text);
    localStorage.setItem('tasks', JSON.stringify(tasks));
    loadTasks();
}

// функция удаления задачи
window.deleteTask = function(index) {
    const tasks = JSON.parse(localStorage.getItem('tasks') || '[]');
    tasks.splice(index, 1);
    localStorage.setItem('tasks', JSON.stringify(tasks));
    loadTasks();
}

// handler отправки формы
form.addEventListener('submit', (e) => {
    e.preventDefault();
    const text = input.value.trim();
    if (text) {
        addTask(text);
    }
    input.value = '';
});

loadTasks();


if ('serviceWorker' in navigator) {
    window.addEventListener('load', async () => {
        try {
            const registration = await navigator.serviceWorker.register('/sw.js');
            console.log('ServiceWorker успешно зарегистрирован. Область видимости:', registration.scope);
        } catch (err) {
            console.error('Ошибка регистрации ServiceWorker:', err);
        }
    });
}