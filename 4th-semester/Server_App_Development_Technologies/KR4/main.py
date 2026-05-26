from fastapi import FastAPI, HTTPException, Response, Request
from fastapi.exceptions import RequestValidationError
from fastapi.responses import JSONResponse
from pydantic import BaseModel, EmailStr, conint, constr
from typing import Optional
from itertools import count
from threading import Lock

app = FastAPI()

class CustomExceptionA(Exception):
    def __init__(self, name: str):
        self.name = name

class CustomExceptionB(Exception):
    def __init__(self, resource_id: int):
        self.resource_id = resource_id

class ErrorResponseModel(BaseModel):
    error: str
    message: str
    status_code: int

@app.exception_handler(CustomExceptionA)
async def custom_exception_a_handler(request: Request, exc: CustomExceptionA):
    return JSONResponse(
        status_code=400,
        content=ErrorResponseModel(
            error="ConditionNotMet",
            message=f"Условие не выполнено для: {exc.name}",
            status_code=400
        ).model_dump()
    )

@app.exception_handler(CustomExceptionB)
async def custom_exception_b_handler(request: Request, exc: CustomExceptionB):
    return JSONResponse(
        status_code=404,
        content=ErrorResponseModel(
            error="ResourceNotFound",
            message=f"Ресурс с ID {exc.resource_id} не найден",
            status_code=404
        ).model_dump()
    )

@app.get("/trigger-a/{name}")
def trigger_a(name: str):
    if name == "error":
        raise CustomExceptionA(name=name)
    return {"message": "Success"}

@app.get("/trigger-b/{res_id}")
def trigger_b(res_id: int):
    raise CustomExceptionB(resource_id=res_id)


class UserRegister(BaseModel):
    username: str
    age: conint(gt=18)
    email: EmailStr
    password: constr(min_length=8, max_length=16)
    phone: Optional[str] = 'Unknown'

@app.exception_handler(RequestValidationError)
async def validation_exception_handler(request: Request, exc: RequestValidationError):
    return JSONResponse(
        status_code=422,
        content={"detail": "Ошибка валидации данных", "errors": exc.errors()}
    )

@app.post("/register")
def register_user_endpoint(user: UserRegister):
    return {"message": "Пользователь успешно зарегистрирован", "data": user.model_dump()}

db: dict[int, dict] = {}
_id_seq = count(start=1)
_id_lock = Lock()

def next_user_id() -> int:
    with _id_lock:
        return next(_id_seq)

class UserIn(BaseModel):
    username: str
    age: int

class UserOut(BaseModel):
    id: int
    username: str
    age: int

@app.post("/users", response_model=UserOut, status_code=201)
def create_user(user: UserIn):
    user_id = next_user_id()
    db[user_id] = user.model_dump()
    return {"id": user_id, **db[user_id]}

@app.get("/users/{user_id}", response_model=UserOut)
def get_user(user_id: int):
    if user_id not in db:
        raise HTTPException(status_code=404, detail="User not found")
    return {"id": user_id, **db[user_id]}

@app.delete("/users/{user_id}", status_code=204)
def delete_user(user_id: int):
    if db.pop(user_id, None) is None:
        raise HTTPException(status_code=404, detail="User not found")
    return Response(status_code=204)