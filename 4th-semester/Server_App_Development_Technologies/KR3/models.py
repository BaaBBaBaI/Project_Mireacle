from pydantic import BaseModel
from typing import Optional

class UserBase(BaseModel):
    username: str

class UserCreate(UserBase):
    password: str

class UserInDB(UserBase):
    hashed_password: str
    role: str = "guest" 

# JWT models 
class Token(BaseModel):
    access_token: str
    token_type: str

class TokenData(BaseModel):
    username: Optional[str] = None
    role: Optional[str] = None

class TodoCreate(BaseModel):
    title: str
    description: Optional[str] = None

class TodoUpdate(BaseModel):
    title: str
    description: Optional[str] = None
    completed: bool

class TodoResponse(BaseModel):
    id: int
    title: str
    description: Optional[str] = None
    completed: bool