from sqlalchemy import Column, Integer, String, Float
from pydantic import BaseModel, EmailStr, constr, conint
from typing import Optional
from .database import Base

class Product(Base):
    __tablename__ = "products"

    id = Column(Integer, primary_key=True, index=True)
    title = Column(String, index=True)
    price = Column(Float)
    count = Column(Integer)
    
    # description = Column(String, nullable=False, server_default="Нет описания")

class UserCreate(BaseModel):
    username: str
    age: conint(gt=18)
    email: EmailStr
    password: constr(min_length=8, max_length=16)
    phone: Optional[str] = 'Unknown'

class ErrorResponse(BaseModel):
    error_code: int
    message: str

class UserIn(BaseModel):
    username: str
    age: int

class UserOut(BaseModel):
    id: int
    username: str
    age: int