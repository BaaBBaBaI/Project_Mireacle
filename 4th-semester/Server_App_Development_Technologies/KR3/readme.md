# Контрольная работа №3

Решение контрольной работы по разработке серверных приложений. Включает API на FastAPI, JWT-аутентификацию, управление ролями (RBAC), ограничение запросов (Rate Limit) и работу с базой данных SQLite.

## Установка и запуск

1. Склонируйте репозиторий и перейдите в папку проекта.
2. Создайте и активируйте виртуальное окружение:
   ```bash
   python -m venv venv
   source venv/bin/activate  # Для macOS/Linux
   # venv\Scripts\activate   # Для Windows
   ```
3. Установите зависимости:
   ```bash
   pip install -r requirements.txt
   ```
4. Создайте файл `.env` на основе примера:
   ```bash
   cp .env.example .env
   ```
5. Запустите сервер:
   ```bash
   uvicorn main:app --reload
   ```

## Тестирование API

Документация Swagger (требует MODE=DEV в .env):
```bash
curl -u admin:supersecret [http://127.0.0.1:8000/docs](http://127.0.0.1:8000/docs)
```

Регистрация пользователя:
```bash
curl -X POST [http://127.0.0.1:8000/register](http://127.0.0.1:8000/register) \
     -H "Content-Type: application/json" \
     -d '{"username":"test_user", "password":"password123"}'
```

Авторизация (получение JWT):
```bash
curl -X POST [http://127.0.0.1:8000/login](http://127.0.0.1:8000/login) \
     -H "Content-Type: application/json" \
     -d '{"username":"test_user", "password":"password123"}'
```

Создание задачи (Todo CRUD):
```bash
curl -X POST [http://127.0.0.1:8000/todos](http://127.0.0.1:8000/todos) \
     -H "Content-Type: application/json" \
     -d '{"title": "Новая задача", "description": "Описание"}'
```