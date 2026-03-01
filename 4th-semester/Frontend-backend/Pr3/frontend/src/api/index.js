import axios from "axios";

const apiClient = axios.create({
    baseURL: "http://localhost:3000/api",
    headers: {
        "Content-Type": "application/json",
        "accept": "application/json",
    }
});

export const api = {
    getProducts: async () => {
        let response = await apiClient.get("/products");
        return response.data;
    },
    createProduct: async (product) =>  await apiClient.post("/products", product),
    updateProduct: async (product) =>  await apiClient.put("/products", product),
    deleteProduct: async (id) =>  await apiClient.delete(`/products/${id}`),
};