const express = require('express');
const { nanoid } = require('nanoid');
const cors = require('cors');

const app = express();
const port = 3000;

app.use(express.json());
app.use(cors({
    origin: "http://localhost:3001",
    methods: ["GET", "POST", "PATCH", "DELETE"],
    allowedHeaders: ["Content-Type", "Authorization"],
}));

let products = [
    { id: nanoid(6), name: "Барсик", category: "Мейн-кун", description: "Огромный и пушистый, отлично греет зимой.", price: 1500, stock: 2, rating: 4.9, image: "https://cdn2.thecatapi.com/images/O3btzLlsO.png" },
    { id: nanoid(6), name: "Мурзик", category: "Британская", description: "Плюшевый аристократ, любит лежать на диване.", price: 1200, stock: 1, rating: 4.7, image: "https://cdn2.thecatapi.com/images/s4wQfA0Cg.jpg" },
    { id: nanoid(6), name: "Снежок", category: "Ангорская", description: "Белоснежный красавец с гетерохромией.", price: 1000, stock: 3, rating: 4.8, image: "https://cdn2.thecatapi.com/images/7is_kXpWn.jpg" },
    { id: nanoid(6), name: "Персик", category: "Персидская", description: "Ленивый и спокойный, идеален для чтения книг.", price: 900, stock: 2, rating: 4.5, image: "https://cdn2.thecatapi.com/images/MTY2OTMyMQ.jpg" },
    { id: nanoid(6), name: "Гав", category: "Сиамская", description: "Очень разговорчивый кот, составит компанию.", price: 1100, stock: 4, rating: 4.6, image: "https://cdn2.thecatapi.com/images/5h_wJ0H0k.jpg" },
    { id: nanoid(6), name: "Рыжик", category: "Беспородный", description: "Приносит удачу и требует много вкусняшек.", price: 500, stock: 5, rating: 5.0, image: "https://cdn2.thecatapi.com/images/MTYwNDk2MA.jpg" },
    { id: nanoid(6), name: "Багира", category: "Бомбейская", description: "Мини-пантера, грациозная и загадочная.", price: 1400, stock: 1, rating: 4.9, image: "https://cdn2.thecatapi.com/images/w2D5E0QpD.jpg" },
    { id: nanoid(6), name: "Фараон", category: "Сфинкс", description: "Горячий на ощупь, любит спать под одеялом.", price: 1600, stock: 2, rating: 4.4, image: "https://cdn2.thecatapi.com/images/y-SGEWd_0.jpg" },
    { id: nanoid(6), name: "Леопольд", category: "Шотландская", description: "Добрый кот-пацифист с висячими ушками.", price: 1300, stock: 3, rating: 4.8, image: "https://cdn2.thecatapi.com/images/8r.jpg" },
    { id: nanoid(6), name: "Матроскин", category: "Полосатый", description: "Хозяйственный, умеет вышивать крестиком.", price: 800, stock: 1, rating: 4.7, image: "https://cdn2.thecatapi.com/images/150.jpg" }
];

app.get("/api/products", (req, res) => {
    res.json(products);
});

app.post("/api/products", (req, res) => {
    const newProduct = { id: nanoid(6), ...req.body };
    products.push(newProduct);
    res.status(201).json(newProduct);
});

app.patch("/api/products/:id", (req, res) => {
    const { id } = req.params;
    const index = products.findIndex(p => p.id === id);
    if (index === -1) return res.status(404).json({ error: "Товар не найден" });

    products[index] = { ...products[index], ...req.body };
    res.json(products[index]);
});

app.delete("/api/products/:id", (req, res) => {
    products = products.filter(p => p.id !== req.params.id);
    res.status(204).send();
});

app.listen(port, () => console.log(`Сервер запущен на http://localhost:${port}`));