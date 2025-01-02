const express = require('express');
const mongoose = require('mongoose');
const cors = require('cors');
const dotenv = require('dotenv');

// Load environment variables
dotenv.config();

const app = express();

// Middleware
app.use(cors());
app.use(express.json());

// MongoDB connection
mongoose.connect(process.env.MONGODB_URI || 'mongodb://localhost:27017/snippetdb')
    .then(() => console.log('Connected to MongoDB'))
    .catch(err => console.error('MongoDB connection error:', err));

// Snippet Schema
const snippetSchema = new mongoose.Schema({
    title: { type: String, required: true },
    code: { type: String, required: true },
    language: { type: String, default: 'javascript' },
    description: String,
    createdAt: { type: Date, default: Date.now },
    updatedAt: { type: Date, default: Date.now }
});

const Snippet = mongoose.model('Snippet', snippetSchema);

// Routes
app.get('/api/snippets', async (req, res) => {
    try {
        const snippets = await Snippet.find().sort({ createdAt: -1 });
        res.json(snippets);
    } catch (error) {
        res.status(500).json({ message: error.message });
    }
});

app.post('/api/snippets', async (req, res) => {
    try {
        const snippet = new Snippet(req.body);
        await snippet.save();
        res.status(201).json(snippet);
    } catch (error) {
        res.status(400).json({ message: error.message });
    }
});

// Delete snippet
app.delete('/api/snippets/:id', async (req, res) => {
    try {
        const snippet = await Snippet.findByIdAndDelete(req.params.id);
        if (!snippet) {
            return res.status(404).json({ message: 'Snippet not found' });
        }
        res.json({ message: 'Snippet deleted successfully' });
    } catch (error) {
        res.status(500).json({ message: error.message });
    }
});

// Start server
const PORT = process.env.PORT || 5000;
app.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`);
});