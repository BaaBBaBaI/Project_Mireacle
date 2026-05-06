# Контрольная работа №4

Проект демонстрирует навыки работы с миграциями БД (Alembic), кастомной обработкой исключений, сложной Pydantic-валидацией и асинхронным тестированием FastAPI.

## 🛠 Установка и запуск

1. **Склонируйте репозиторий и перейдите в папку:**
   ```bash
   git clone <url_репозитория>
   cd FAPI_KR4
   ```
2. **Установите зависимости:**
   ```bash
   python -m venv venv
   source venv/bin/activate  # Для Windows: venv\Scripts\activate
   pip install -r requirements.txt
   ```
3. **Запуск сервера:**
   ```bash
   uvicorn src.main:app --reload
   ```

---
