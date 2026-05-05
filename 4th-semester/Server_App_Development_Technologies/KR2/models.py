from pydantic import BaseModel, EmailStr, Field, field_validator, model_validator
import re


class UserCreate(BaseModel):
    name: str
    email: EmailStr
    age: int | None = Field(None, gt=0)
    is_subscribed: bool = False


class LoginRequest(BaseModel):
    username: str
    password: str


class CommonHeaders(BaseModel):
    user_agent: str
    accept_language: str

    @field_validator('accept_language')
    @classmethod
    def validate_language(cls, v: str) -> str:  
        if not re.match(r'^[a-zA-Z0-9,\-;\.=\s]+$', v):
            raise ValueError("Invalid Accept-Language format")
        return v