# PR25

A small React + Vite project with client-side routing and a lazy-loaded About page.

## Features

- Vite-powered React application
- React Router DOM navigation between `Главная` and `О нас`
- Lazy loading for the About route
- Production build via `npm run build`

## Requirements

- Node.js 18 or newer
- npm

## Installation

Install dependencies:

```bash
npm install
```

## Development

Run the development server:

```bash
npm run dev
```

Open the app in your browser at the URL shown in the terminal.

## Build

Create a production build:

```bash
npm run build
```

This command builds the app into the `dist/` folder.

## Preview production build

After building, preview the production output locally:

```bash
npm run preview
```

## Project structure

- `public/` — static public assets
- `src/` — React application source files
- `src/App.jsx` — app shell and router setup
- `src/Home.jsx` — home page component
- `src/About.jsx` — lazy-loaded about page
- `src/main.jsx` — app entry point

## Scripts

- `npm run dev` — start Vite dev server
- `npm run build` — bundle app for production
- `npm run preview` — serve the production build locally
- `npm run lint` — run ESLint
