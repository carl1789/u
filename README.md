
# Online Bookstore

This is a simple online bookstore application built with the MERN stack (MongoDB, Express, React, Node.js), with the flexibility to run with an in-memory database for development and testing purposes.

## Features

*   **Dual Database Mode:**
    *   **In-Memory:** Runs without a database connection for quick development and testing.
    *   **MongoDB:** Connects to a MongoDB instance when a connection URL is provided.
*   **User Authentication:**
    *   User registration
    *   User login
*   **Book Catalogue:** View a list of available books.
*   **Responsive Design:** The user interface is designed to be responsive and work on different screen sizes.

## Technology Stack

*   **Frontend:**
    *   React
    *   React Router for routing
    *   Axios for API requests
*   **Backend:**
    *   Node.js
    *   Express.js for the server
    *   Mongoose for MongoDB object modeling
    *   In-memory store (if no MongoDB URL is provided)
*   **Database:**
    *   MongoDB (optional)

## Project Structure

The project is divided into two main directories:

*   `frontend/`: Contains the React application.
*   `backend/`: Contains the Node.js/Express server.

## Setup and Installation

Follow these steps to get the project up and running on your local machine.

### Prerequisites

*   [Node.js](https://nodejs.org/) (which includes npm)
*   [MongoDB](https://www.mongodb.com/try/download/community) (optional, only if you want to use a database)

### Backend Setup

1.  **Navigate to the backend directory:**
    ```bash
    cd backend
    ```

2.  **Install dependencies:**
    ```bash
    npm install
    ```

3.  **Run the server:**

    *   **In-Memory Mode:**
        To run the server without a database connection, simply use:
        ```bash
        npm start
        ```
        The server will start on `http://localhost:5000`.

    *   **MongoDB Mode:**
        If you have MongoDB installed and running, you can start the server with a `MONGO_URL` environment variable:
        ```bash
        MONGO_URL=mongodb://localhost:27017/bookstore npm start
        ```
        The server will connect to the specified MongoDB instance.

### Frontend Setup

1.  **Navigate to the frontend directory:**
    ```bash
    cd frontend
    ```

2.  **Install dependencies:**
    ```bash
    npm install
    ```

3.  **Start the development server:**
    ```bash
    npm start
    ```
    The application will open in your browser at `http://localhost:3000`.

## API Endpoints

The backend server provides the following API endpoints:

*   `POST /register`: Register a new user.
    *   **Request Body:** `{ "username": "yourusername", "password": "yourpassword" }`
*   `POST /login`: Log in an existing user.
    *   **Request Body:** `{ "username": "yourusername", "password": "yourpassword" }`
*   `GET /books`: Get a list of all books.
# u
