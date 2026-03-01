const express = require('express');
const app = express();
const port = 3000;

app.use(express.json());

let products = [
    { id: 1, name: 'Jordan', price: 200 },
    { id: 2, name: 'SJordan', price: 300 },
    { id: 3, name: 'AJordan', price: 250 },
    { id: 4, name: 'CJordan', price: 500 },
    { id: 5, name: 'BJordan', price: 270 },
];

app.get('/products', (req, res) => {
    res.json(products);
});


app.get('/products/:id', (req, res) => {
    const productId = products.find ( p => p.id == req.params.id);
    if (!productId) {
        res.status(404).send('Product not found');
        return;
    }
    res.json(productId);
});

app.post('/products', (req, res) => {
    const { name, price } = req.body;
    if (!name || !price) {
        res.status(400).send('Product not valid');
    }
    const newProduct = {
        id: Date.now(),
        name,
        price
    };
    products.push(newProduct);
    res.status(201).json(newProduct);
});

app.patch('/products/:id', (req, res) => {
    const productId = products.find ( p => p.id == req.params.id );
    if (!productId) {
        res.status(404).send('Product not found');
        return;
    }
    const { name, price } = req.body;
    if (name !== undefined) productId.name = name;
    if (price !== undefined) productId.price = price;

    res.json(productId);

})

// Функция удаления
app.delete('/products/:id', (req, res) => {
    products = products.filter( p => p.id != req.params.id );
    res.send("Product deleted");
})

app.listen(port, () => {
    console.log(`Listening on port ${port}`);
})