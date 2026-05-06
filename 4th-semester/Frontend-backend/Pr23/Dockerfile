FROM node:18-alpine
WORKDIR /app

# manifest copy
COPY package*.json ./
RUN npm install

# code copy
COPY . .

EXPOSE 3000
CMD ["npm", "start"]