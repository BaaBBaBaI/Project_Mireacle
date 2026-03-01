import React from "react";

export default function ProductItem({ product, onDelete, onEdit }) {
    return (
        <div className="productCard" style={{ border: '1px solid #ccc', padding: '15px', borderRadius: '8px', marginBottom: '10px' }}>
            <div style={{ display: 'flex', gap: '15px' }}>
                <img src={product.image || "https://via.placeholder.com/100"} alt={product.name} width="100" style={{ borderRadius: '8px' }} />
                <div>
                    <h3>{product.name} <span style={{fontSize: '0.6em', color: 'gray'}}>⭐ {product.rating}</span></h3>
                    <p><strong>Категория:</strong> {product.category}</p>
                    <p><em>{product.description}</em></p>
                    <p><strong>Цена:</strong> {product.price} руб/сутки | <strong>В наличии:</strong> {product.stock} шт.</p>
                </div>
            </div>
            <div style={{ marginTop: '10px' }}>
                <button onClick={() => onEdit(product)}>Редактировать</button>
                <button onClick={() => onDelete(product.id)} style={{ marginLeft: '10px', color: 'red' }}>Удалить</button>
            </div>
        </div>
    );
}