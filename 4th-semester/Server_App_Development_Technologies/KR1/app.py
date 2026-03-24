from fastapi import FastAPI
from fastapi.responses import FileResponse
from models import User, CalculateRequest, UserAge, Feedback

my_app = FastAPI()

@my_app.get("/")
def read_root():
    return FileResponse("index.html")

@my_app.post("/calculate")
def calculate(data: CalculateRequest): return {"result": data.num1 + data.num2}

current_user = User(name="baabbabai", id=1)

@my_app.get("/users")
def get_users(): return current_user

@my_app.post("/user")
def check_user_adult(user: UserAge):
    is_adult = user.age >= 18
    return {
        "name": user.name,
        "age": user.age,
        "is_adult": is_adult
    }

feedbacks = []

@my_app.post("/feedback")
def receive_feedback(feedback: Feedback):
    feedbacks.append(feedback.model_dump())
    return {"message": f"Спасибо за отзыв, {feedback.name}!."}