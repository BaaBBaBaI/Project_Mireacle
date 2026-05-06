const express = require("express");
const app = express();

const PORT = process.env.PORT || 3000;
const SERVER_NAME = process.env.SERVER_NAME || "Unknown Server";

app.get("/", (req, res) => {
    res.json({
        message: "Response from backend server",
        server: SERVER_NAME,
        port: PORT
    });
});

app.listen(PORT, () => {
    console.log(`Server ${SERVER_NAME} started on port ${PORT}`);
});