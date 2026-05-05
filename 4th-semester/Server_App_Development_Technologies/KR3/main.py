import os
import secrets
from dotenv import load_dotenv

from fastapi import FastAPI, Depends, HTTPException, status, Request
from fastapi.security import HTTPBasic, HTTPBasicCredentials
from fastapi.openapi.docs import get_swagger_ui_html
from fastapi.openapi.utils import get_openapi
from slowapi import Limiter, _rate_limit_exceeded_handler
from slowapi.util import get_remote_address
from slowapi.errors import RateLimitExceeded    

from models import UserCreate, TodoCreate, TodoUpdate, TodoResponse
from auth import (
    fake_users_db, get_password_hash, verify_password, create_access_token, 
    ACCESS_TOKEN_EXPIRE_MINUTES, get_current_user, RoleChecker, UserInDB
)
from database import get_db_connection

load_dotenv()

MODE = os.getenv("MODE", "DEV")
DOCS_USER = os.getenv("DOCS_USER", "admin")
DOCS_PASSWORD = os.getenv("DOCS_PASSWORD", "secret")

app = FastAPI(docs_url=None, redoc_url=None, openapi_url=None)

limiter = Limiter(key_func=get_remote_address)
app.state.limiter = limiter
app.add_exception_handler(RateLimitExceeded, _rate_limit_exceeded_handler)

security_basic = HTTPBasic()

def verify_docs_auth(credentials: HTTPBasicCredentials = Depends(security_basic)):
    is_user_ok = secrets.compare_digest(credentials.username, DOCS_USER)
    is_pass_ok = secrets.compare_digest(credentials.password, DOCS_PASSWORD)
    if not (is_user_ok and is_pass_ok):
        raise HTTPException(
            status_code=status.HTTP_401_UNAUTHORIZED,
            detail="Invalid credentials",
            headers={"WWW-Authenticate": "Basic"},
        )
    return credentials

if MODE == "DEV":
    @app.get("/docs", include_in_schema=False)
    async def get_swagger_documentation(credentials: HTTPBasicCredentials = Depends(verify_docs_auth)):
        return get_swagger_ui_html(openapi_url="/openapi.json", title="Docs")

    @app.get("/openapi.json", include_in_schema=False)
    async def openapi(credentials: HTTPBasicCredentials = Depends(verify_docs_auth)):
        return get_openapi(title="FastAPI", version="1.0.0", routes=app.routes)
elif MODE == "PROD":
    @app.get("/docs", include_in_schema=False)
    @app.get("/redoc", include_in_schema=False)
    @app.get("/openapi.json", include_in_schema=False)
    async def hidden_docs():
        raise HTTPException(status_code=404, detail="Not Found")



# jwt
@app.post("/register", status_code=201)
@limiter.limit("1/minute")
def register(request: Request, user: UserCreate):
    for db_user in fake_users_db.values():
        if secrets.compare_digest(db_user.username, user.username):
            raise HTTPException(status_code=409, detail="User already exists")
    
    hashed_pass = get_password_hash(user.password)
    fake_users_db[user.username] = UserInDB(username=user.username, hashed_password=hashed_pass, role="user")
    return {"message": "New user created"}

@app.post("/login")
@limiter.limit("5/minute")
def login(request: Request, user: UserCreate):
    db_user = next((u for u in fake_users_db.values() if secrets.compare_digest(u.username, user.username)), None)
    
    if not db_user:
        raise HTTPException(status_code=404, detail="User not found")
        
    if not verify_password(user.password, db_user.hashed_password):
        raise HTTPException(status_code=401, detail="Authorization failed")
        
    access_token = create_access_token(
        data={"sub": db_user.username, "role": db_user.role},
        expires_delta=timedelta(minutes=ACCESS_TOKEN_EXPIRE_MINUTES)
    )
    return {"access_token": access_token, "token_type": "bearer"}


# RBAC endpoints
allow_admin = RoleChecker(["admin"])
allow_user = RoleChecker(["admin", "user"])
allow_guest = RoleChecker(["admin", "user", "guest"])

@app.get("/admin_only")
def admin_data(current_user: UserInDB = Depends(allow_admin)):
    return {"message": f"Welcome Admin {current_user.username}, you can create resources!"}

@app.get("/user_area")
def user_data(current_user: UserInDB = Depends(allow_user)):
    return {"message": f"Welcome {current_user.username}, you can read and update resources."}


@app.post("/db_register")
def db_register(user: UserCreate):
    conn = get_db_connection()
    cursor = conn.cursor()
    try:
        cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", (user.username, user.password))
        conn.commit()
    except sqlite3.IntegrityError:
        conn.close()
        raise HTTPException(status_code=400, detail="Username already exists in DB")
    conn.close()
    return {"message": "User registered successfully!"}



# CRUD for Todo
@app.post("/todos", status_code=201, response_model=TodoResponse)
def create_todo(todo: TodoCreate):
    conn = get_db_connection()
    cursor = conn.cursor()
    cursor.execute(
        "INSERT INTO todos (title, description, completed) VALUES (?, ?, 0)", 
        (todo.title, todo.description)
    )
    conn.commit()
    todo_id = cursor.lastrowid
    
    cursor.execute("SELECT * FROM todos WHERE id = ?", (todo_id,))
    new_todo = dict(cursor.fetchone())
    new_todo['completed'] = bool(new_todo['completed'])
    conn.close()
    
    return new_todo

@app.get("/todos/{todo_id}", response_model=TodoResponse)
def get_todo(todo_id: int):
    conn = get_db_connection()
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM todos WHERE id = ?", (todo_id,))
    row = cursor.fetchone()
    conn.close()
    
    if not row:
        raise HTTPException(status_code=404, detail="Todo not found")
        
    todo = dict(row)
    todo['completed'] = bool(todo['completed'])
    return todo

@app.put("/todos/{todo_id}", response_model=TodoResponse)
def update_todo(todo_id: int, todo: TodoUpdate):
    conn = get_db_connection()
    cursor = conn.cursor()
    
    cursor.execute("SELECT id FROM todos WHERE id = ?", (todo_id,))
    if not cursor.fetchone():
        conn.close()
        raise HTTPException(status_code=404, detail="Todo not found")
        
    cursor.execute(
        "UPDATE todos SET title = ?, description = ?, completed = ? WHERE id = ?",
        (todo.title, todo.description, int(todo.completed), todo_id)
    )
    conn.commit()
    
    cursor.execute("SELECT * FROM todos WHERE id = ?", (todo_id,))
    updated_todo = dict(cursor.fetchone())
    updated_todo['completed'] = bool(updated_todo['completed'])
    conn.close()
    
    return updated_todo

@app.delete("/todos/{todo_id}")
def delete_todo(todo_id: int):
    conn = get_db_connection()
    cursor = conn.cursor()
    
    cursor.execute("SELECT id FROM todos WHERE id = ?", (todo_id,))
    if not cursor.fetchone():
        conn.close()
        raise HTTPException(status_code=404, detail="Todo not found")
        
    cursor.execute("DELETE FROM todos WHERE id = ?", (todo_id,))
    conn.commit()
    conn.close()
    
    return {"message": "Todo deleted successfully"}

MODE = os.getenv("MODE", "DEV")
DOCS_USER = os.getenv("DOCS_USER", "admin")
DOCS_PASSWORD = os.getenv("DOCS_PASSWORD", "secret")

print(f"ОЖИДАЕМЫЙ ЛОГИН: {DOCS_USER}")
print(f"ОЖИДАЕМЫЙ ПАРОЛЬ: {DOCS_PASSWORD}")