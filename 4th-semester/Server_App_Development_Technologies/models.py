from pydantic import BaseModel, Field, field_validator

class CalculateRequest(BaseModel):
    num1: float; num2: float

class User(BaseModel):
    name: str; id: int

class UserAge(BaseModel):
    name: str; age: int

class Feedback(BaseModel):
    name: str = Field(min_length=2, max_length=50)
    message: str = Field(min_length=10, max_length=500)

    @field_validator('message')
    @classmethod

    def checkForNoForbiddenWords(cls, v: str) -> str: 
        
        v_lower = v.lower()
        forbiddenWords = ["кринж", "рофлс", "вайб"]
        for word in forbiddenWords:
            if word in v_lower:
                raise ValueError("Ошибка: Используются недопустимые символы")
        return v
    
    