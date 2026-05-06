const express = require('express');
const app = express();

const PORT = 3000;
const SERVER_ID = process.env.SERVER_ID || 'unknown-backend';

app.get('/', (req, res) => {
    res.json({ server: SERVER_ID });
});

// all containers network interfaces following 
app.listen(PORT, '0.0.0.0', () => {
    console.log(`Server ${SERVER_ID} running on port ${PORT}`);
}); 