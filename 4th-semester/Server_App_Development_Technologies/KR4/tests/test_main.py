import pytest
from httpx import AsyncClient, ASGITransport
from faker import Faker
from main import app, db

fake = Faker()

@pytest.fixture(autouse=True)
def reset_db():
    db.clear()
    yield

@pytest.mark.asyncio
async def test_create_user():
    AsyncClient(transport=ASGITransport(app=app), base_url="http://test") as ac:
        payload = {"username": fake.user_name(), "age": fake.random_int(min=19, max=99)}
        response = await ac.post("/users", json=payload)
        
        assert response.status_code == 201
        data = response.json()
        assert "id" in data
        assert data["username"] == payload["username"]
        assert data["age"] == payload["age"]

@pytest.mark.asyncio
async def test_get_existing_user():
    async with AsyncClient(transport=ASGITransport(app=app), base_url="http://test") as ac:
        payload = {"username": fake.user_name(), "age": 25}
        create_res = await ac.post("/users", json=payload)
        user_id = create_res.json()["id"]

        get_res = await ac.get(f"/users/{user_id}")
        assert get_res.status_code == 200
        assert get_res.json()["username"] == payload["username"]

@pytest.mark.asyncio
async def test_get_nonexistent_user():
    async with AsyncClient(transport=ASGITransport(app=app), base_url="http://test") as ac:
        response = await ac.get("/users/999")
        assert response.status_code == 404

@pytest.mark.asyncio
async def test_delete_existing_user():
    async with AsyncClient(transport=ASGITransport(app=app), base_url="http://test") as ac:
        payload = {"username": fake.user_name(), "age": 30}
        create_res = await ac.post("/users", json=payload)
        user_id = create_res.json()["id"]

        del_res = await ac.delete(f"/users/{user_id}")
        assert del_res.status_code == 204

@pytest.mark.asyncio
async def test_delete_already_deleted_user():
    async with AsyncClient(transport=ASGITransport(app=app), base_url="http://test") as ac:
        payload = {"username": fake.user_name(), "age": 30}
        create_res = await ac.post("/users", json=payload)
        user_id = create_res.json()["id"]

        await ac.delete(f"/users/{user_id}")
        # Повторное удаление
        del_res = await ac.delete(f"/users/{user_id}")
        assert del_res.status_code == 404