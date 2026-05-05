import time
import uuid
from typing import Optional, Annotated
from datetime import datetime

from fastapi import FastAPI, Cookie, Response, HTTPException, Header, Request
from fastapi.exceptions import RequestValidationError
from fastapi.responses import JSONResponse
from itsdangerous import Signer, BadSignature

from models import UserCreate, LoginRequest, CommonHeaders

app = FastAPI()

# redefine error code
@app.exception_handler(RequestValidationError)
async def validation_exception_handler(request: Request, exc: RequestValidationError):
    return JSONResponse(
        status_code=400,
        content={"message": "Bad Request: Missing or invalid required fields/headers", "details": exc.errors()}
    )

#  3.1
@app.post("/create_user")
def create_user(user: UserCreate):
    
    return user

#  3.2
sample_products = [
    {"product_id": 123, "name": "Smartphone", "category": "Electronics", "price": 599.99},
    {"product_id": 456, "name": "Phone Case", "category": "Accessories", "price": 19.99},
    {"product_id": 789, "name": "Iphone", "category": "Electronics", "price": 1299.99},
    {"product_id": 101, "name": "Headphones", "category": "Accessories", "price": 99.99},
    {"product_id": 202, "name": "Smartwatch", "category": "Electronics", "price": 299.99}
]



@app.get("/products/search")
def search_products(keyword: str, category: Optional[str] = None, limit: int = 10):
    results = []
    for product in sample_products:
        if keyword.lower() in product["name"].lower():
            if category and product["category"].lower() != category.lower():
                continue
            results.append(product)
    
    return results[:limit]

@app.get("/product/{product_id}")
def get_product(product_id: int):
    for product in sample_products:
        if product["product_id"] == product_id:
            return product
    raise HTTPException(status_code=404, detail="Product not found")


# 5.1, 5.2, 5.3 

SECRET_KEY = "my_super_secret_key" 
signer = Signer(SECRET_KEY)

@app.post("/login")
def login(data: LoginRequest, response: Response):

    if data.username != "user123" or data.password != "password123":
        raise HTTPException(status_code=401, detail="Unauthorized")
    
    user_id = str(uuid.uuid4())
    timestamp = int(time.time())
    

    value_to_sign = f"{user_id}.{timestamp}"
    


    session_token = signer.sign(value_to_sign).decode('utf-8')
    
    response.set_cookie(
        key="session_token",
        value=session_token,
        httponly=True,
        secure=False, # localhost (no https)? -> False : -> True
        max_age=300   # 5 mins
    )
    return {"message": "Успешный вход"}

@app.get("/profile")
def get_profile(response: Response, session_token: str | None = Cookie(default=None)):
    if not session_token:
        raise HTTPException(status_code=401, detail="Unauthorized")
    
    try:


        valid_value = signer.unsign(session_token).decode('utf-8')
        user_id, timestamp_str = valid_value.rsplit('.', 1)
        last_activity = int(timestamp_str)
    except (BadSignature, ValueError):
        raise HTTPException(status_code=401, detail="Invalid session")
    
    current_time = int(time.time())
    time_passed = current_time - last_activity
    

    if time_passed >= 300:
        raise HTTPException(status_code=401, detail="Session expired")
    

    if time_passed >= 180:
        new_value = f"{user_id}.{current_time}"
        new_token = signer.sign(new_value).decode('utf-8')
        response.set_cookie(
            key="session_token",
            value=new_token,
            httponly=True,
            secure=False,
            max_age=300
        )
    

    return {
        "user_id": user_id,
        "username": "user123",
        "message": "Доступ разрешен"
    }


# 5.4, 5.5 

@app.get("/headers")
def read_headers(headers: Annotated[CommonHeaders, Header()]):
    return {
        "User-Agent": headers.user_agent,
        "Accept-Language": headers.accept_language
    }

@app.get("/info")
def get_info(response: Response, headers: Annotated[CommonHeaders, Header()]):

    current_time_iso = datetime.now().isoformat()
    response.headers["X-Server-Time"] = current_time_iso
    
    return {
        "message": "Добро пожаловать! Ваши заголовки успешно обработаны.",
        "headers": {
            "User-Agent": headers.user_agent,
            "Accept-Language": headers.accept_language
        }
    }