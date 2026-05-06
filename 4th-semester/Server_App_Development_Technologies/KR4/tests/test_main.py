import pytest
from httpx import AsyncClient, ASGITransport
from faker import Faker

from src.main import app, db

fake = Faker()

@pytest.fixture(autouse=True)
def clear_db():
    db.clear()
    yield

@pytest.fixture
async def async_client():
    transport = ASGITransport(app=app)
    async with AsyncClient(transport=transport, base_url="http://test") as ac:
        yield ac

@pytest.mark.asyncio
async def test_create_user(async_client: AsyncClient):
    payload = {"username": fake.user_name(), "age": fake.random_int(min=20, max=60)}
    response = await async_client.post("/users", json=payload)
    
    assert response.status_code == 201
    data = response.json()
    assert data["username"] == payload["username"]
    assert data["age"] == payload["age"]
    assert "id" in data

@pytest.mark.asyncio
async def test_get_existing_user(async_client: AsyncClient):
    payload = {"username": fake.user_name(), "age": 25}
    create_resp = await async_client.post("/users", json=payload)
    user_id = create_resp.json()["id"]
    
    response = await async_client.get(f"/users/{user_id}")
    assert response.status_code == 200
    assert response.json()["id"] == user_id

@pytest.mark.asyncio
async def test_get_nonexistent_user(async_client: AsyncClient):
    response = await async_client.get("/users/999")
    assert response.status_code == 404
    assert response.json()["detail"] == "User not found"

@pytest.mark.asyncio
async def test_delete_user(async_client: AsyncClient):
    payload = {"username": fake.user_name(), "age": 30}
    create_resp = await async_client.post("/users", json=payload)
    user_id = create_resp.json()["id"]
    
    delete_resp = await async_client.delete(f"/users/{user_id}")
    assert delete_resp.status_code == 204
    
    get_resp = await async_client.get(f"/users/{user_id}")
    assert get_resp.status_code == 404

@pytest.mark.asyncio
async def test_delete_nonexistent_user(async_client: AsyncClient):
    response = await async_client.delete("/users/999")
    assert response.status_code == 404