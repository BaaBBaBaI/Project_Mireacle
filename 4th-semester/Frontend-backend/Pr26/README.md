# PR26 GraphQL Server

## Run the server

1. Install dependencies:

   npm install

2. Start the server:

   node server.js

3. Open the GraphQL endpoint in your browser:

   http://localhost:4000/

## Test queries and mutations

Use the GraphQL IDE at `http://localhost:4000/` or send requests to the same endpoint.

### Query example

```graphql
query {
  authors {
    name
    books {
      title
    }
  }
}
```

### Mutation examples

Create a new author:

```graphql
mutation {
  createAuthor(name: "Рэй Брэдбери") {
    id
    name
  }
}
```

Create a new book for an author by ID:

```graphql
mutation {
  createBook(title: "451 градус по Фаренгейту", authorId: "2") {
    id
    title
    author {
      name
    }
  }
}
```

> Note: `authorId` must be a string matching an existing author ID.
