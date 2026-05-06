from fastapi import FastAPI, HTTPException, Response, Request, status
from fastapi.exceptions import RequestValidationError
from fastapi.responses import JSONResponse
from itertools import count
from threading import Lock

from .models import UserCreate, ErrorResponse, UserIn, UserOut
from .exceptions import CustomExceptionA, CustomExceptionB

app = FastAPI()

@app.exception_handler(CustomExceptionA)
async def custom_exception_a_handler(request: Request, exc: CustomExceptionA):
    return JSONResponse(
        status_code=400,
        content=ErrorResponse(error_code=400, message=exc.message).model_dump()
    )

@app.exception_handler(CustomExceptionB)
async def custom_exception_b_handler(request: Request, exc: CustomExceptionB):
    return JSONResponse(
        status_code=404,
        content=ErrorResponse(error_code=404, message=exc.message).model_dump()
    )

@app.exception_handler(RequestValidationError)
async def validation_exception_handler(request: Request, exc: RequestValidationError):
    return JSONResponse(
        status_code=status.HTTP_422_UNPROCESSABLE_ENTITY,
        content={"detail": "Ошибка валидации данных", "errors": exc.errors()}
    )

@app.get("/trigger-a")
def trigger_a(fail: bool = True):
    if fail:
        raise CustomExceptionA("Не выполнено обязательное условие")
    return {"status": "ok"}

@app.get("/trigger-b")
def trigger_b():
    raise CustomExceptionB("Ресурс не найден в системе")

@app.post("/register-strict")
def register_strict(user: UserCreate):
    return {"message": "Пользователь успешно прошел валидацию", "user": user}

db: dict[int, dict] = {}
_id_seq = count(start=1)
_id_lock = Lock()

def next_user_id() -> int:
    with _id_lock:
        return next(_id_seq)

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