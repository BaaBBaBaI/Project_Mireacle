from sqlalchemy import Column, Integer, String, Float
from sqlalchemy.orm import declarative_base

Base = declarative_base()

class Product(Base):
    __tablename__ = "products"

    id = Column(Integer, primary_key=True, index=True)
    title = Column(String, index=True)
    price = Column(Float)
    count = Column(Integer)
    
    # ВНИМАНИЕ для 9.1: Сначала оставьте эту строку закомментированной. 
    # Раскомментируйте её перед созданием второй миграции.
    # description = Column(String, nullable=False, server_default="No description")