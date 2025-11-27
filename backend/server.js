const express = require('express');
const mongoose = require('mongoose');
const bodyParser = require('body-parser');
const cors = require('cors');

const app = express();
const port = 5000;

app.use(cors());
app.use(bodyParser.json());

const MONGO_URL = process.env.MONGO_URL;

let User, Book;


// --- Seed Books ---
const seedBooks = async () => {
  try {
    await Book.deleteMany({});
    const books = [
      { title: 'The Great Gatsby', author: 'F. Scott Fitzgerald', price: 10.99, cover: 'https://m.media-amazon.com/images/I/81QuEGw8VPL._AC_UF1000,1000_QL80_.jpg' },
      { title: 'To Kill a Mockingbird', author: 'Harper Lee', price: 12.50, cover: 'https://m.media-amazon.com/images/I/81a4kCNuH+L._AC_UF1000,1000_QL80_.jpg' },
      { title: '1984', author: 'George Orwell', price: 9.99, cover: 'https://m.media-amazon.com/images/I/71rpa1-kyvL._AC_UF1000,1000_QL80_.jpg' },
      { title: 'The Catcher in the Rye', author: 'J.D. Salinger', price: 8.75, cover: 'https://m.media-amazon.com/images/I/91HPG31dTwL._AC_UF1000,1000_QL80_.jpg' },
    ];
    await Book.insertMany(books);
    console.log('Books seeded');
  } catch (err) {
    console.error('Error seeding books:', err);
  }
};

if (MONGO_URL) {
  // --- MongoDB Mode ---
  mongoose.connect(MONGO_URL, { useNewUrlParser: true, useUnifiedTopology: true });
  const db = mongoose.connection;
  db.on('error', console.error.bind(console, 'MongoDB connection error:'));
  db.once('open', () => {
    console.log('Connected to MongoDB');
    seedBooks();
  });

  const userSchema = new mongoose.Schema({
    username: { type: String, required: true, unique: true },
    password: { type: String, required: true },
  });

  const bookSchema = new mongoose.Schema({
    title: String,
    author: String,
    price: Number,
    cover: String,
  });

  User = mongoose.model('User', userSchema);
  Book = mongoose.model('Book', bookSchema);

} else {
  // --- In-Memory Mode ---
  console.log('Running in in-memory mode');
  let users = [];
  let books = [];
  let nextUserId = 1;

  const InMemoryUser = {
    create: async (userData) => {
      const existingUser = users.find(u => u.username === userData.username);
      if (existingUser) {
        const error = new Error('User already exists');
        error.code = 11000; 
        throw error;
      }
      const newUser = { ...userData, _id: nextUserId++ };
      users.push(newUser);
      return newUser;
    },
    findOne: async (query) => {
      return users.find(u => u.username === query.username && u.password === query.password);
    },
    save: async function() {
        return InMemoryUser.create(this);
    }
  };

  const InMemoryBook = {
    find: async () => books,
    deleteMany: async () => {
      books = [];
      return { deletedCount: books.length };
    },
    insertMany: async (bookData) => {
      books.push(...bookData);
      return bookData;
    },
  };
  
  User = function(data) {
    this.username = data.username;
    this.password = data.password;
  };
  User.prototype.save = async function() {
    return InMemoryUser.create(this);
  };
  User.findOne = InMemoryUser.findOne;


  Book = InMemoryBook;
  seedBooks();
}

// --- API Routes ---
app.post('/register', async (req, res) => {
  try {
    const { username, password } = req.body;
    const newUser = new User({ username, password });
    await newUser.save();
    res.status(201).json({ message: 'User registered successfully' });
  } catch (err) {
    if (err.code === 11000) {
        return res.status(400).json({ error: 'Username already exists' });
    }
    res.status(400).json({ error: 'Registration failed' });
  }
});

app.post('/login', async (req, res) => {
  try {
    const { username, password } = req.body;
    const user = await User.findOne({ username, password });
    if (user) {
      res.status(200).json({ message: 'Login successful' });
    } else {
      res.status(401).json({ error: 'Invalid credentials' });
    }
  } catch (err) {
    res.status(500).json({ error: 'Login failed' });
  }
});

app.get('/books', async (req, res) => {
  try {
    const books = await Book.find();
    res.status(200).json(books);
  } catch (err) {
    res.status(500).json({ error: 'Failed to fetch books' });
  }
});

app.listen(port, () => {
  console.log(`Server is running on http://localhost:${port}`);
});