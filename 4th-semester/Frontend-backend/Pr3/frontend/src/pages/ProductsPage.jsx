import React, { useEffect, useState } from "react";
import {api} from "../api";
import Product from "../components/ProductItem";

export default function ProductsPage() {
    const [products, setProducts] = useState([]);
    const [loading, setLoading] = useState(true);

    useEffect(() => {
        loadProducts();
    }, []);

    const loadProducts = async () => {
        try {
            const data = await api.getProducts();
            setProducts(data);
        } catch (error) {
            console.log(error);
            console.error(error);
        } finally {
            setLoading(false);
        }
    };

    const handleDelete = async (id) => {
        if (!window.confirm("Точно удалить?")) return;
        try {
            await api.deleteProduct(id);
            setProducts(prev => prev.filter(p => p.id !== id));
        } catch (err) {
            alert("Ошибка удаления");
        }
    };

    return (
        <div style={{ maxWidth: '800px', margin: '0 auto', padding: '20px' }}>
            <h1>Аренда Котов</h1>
            {loading ? <p>Загрузка каталога...</p> : (
                <div>
                    {products.map(p => (
                        <Product
                            key={p.id}
                            product={p}
                            onEdit={() => alert("Добавь модалку по примеру из лекции!")}
                            onDelete={handleDelete}
                        />
                    ))}
                </div>
            )}
        </div>
    );



}