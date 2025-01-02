
# Code Snippet Library
### Video Demo:
[Link to Youtube](https://youtu.be/HJtLT0c89qQ)


## Thoughts

The project originated from a concept that emerged when I began my studies in computer science.

The goal was to create a way to organize my notes related to code, especially when I started studying data structures.

Driven by my desire to improve my learning and skills, I wanted to push myself further and decided to embark on this endeavor.

<i>CS50 gave me the opportunity to do it</i> ❤.

Conceived as a full-stack application, it's not as massive as a commercial application, but I aimed to capture the spirit of it by applying relevant concepts and getting used to them.

I saw this as an opportunity to work with key concepts of application development, utilizing technologies in demand in the market, as my goal is to enhance my developer skills.

The purpose of this web application is to manage data, handle easy and simple interactions, and deliver dynamic content on both the server and client sides.

Finally, I must say that achieving this project required many hours of work, sweat, and commitment, but it was truly worthwhile and an exciting journey!

Thanks to you in advance fo reading these lines!

# Description

## Core Functionality

- Create, read, update, and delete code snippets
- Syntax highlighting for multiple programming languages
- Real-time search functionality with keyboard shortcuts
- Dark/Light theme toggle with system preference detection
- Export snippets individually or in bulk
- Copy to clipboard functionality
- Language-specific filtering

## Supported Languages
- JavaScript
- Python
- Java
- C++
- C
- HTML
- CSS
- SQL

## Project Structure

It's divided into two main components:
- Backend
- Frontend

Both are contained in separated directories, with their respective configuration files and
source code.

## Technologies Applied & Design Decisions

Mostly of these technologies are well requested in the computer development field.
I believe, the most important aspect of any study project, is to work with technologies which help me to gain an opportunity to work professionally, help me to earn a better perspective in programming knowledge and why not! Enjoy the ride .

## Backend Stack

### Node.js & Express.js
Chosen for:
- Excellent performance for I/O operations
- Large ecosystem of packages
- JavaScript across full stack reduces context switching
- Express.js provides clean routing and middleware architecture
- Perfect for REST APIs with minimal boilerplate

### MongoDB
Selected because:
- Flexible schema perfect for evolving code snippets structure
- JSON-like documents match our data format naturally
- Excellent scalability for growing snippet collections
- Rich query capabilities for search functionality
- Start with a non relational database too 😁

### Mongoose
Implemented for:
- Schema validation ensures data consistency
- Simplified database operations with intuitive API
- Built-in type casting and validation
- Middleware capabilities for data processing

## Frontend Stack

### React 18
Chosen because:
- Component-based architecture perfect for reusable UI elements
- Virtual DOM for efficient updates
- Large ecosystem and community support ✌
- Latest features like automatic batching improve performance
- Tempted by Angular, but I was short on time to learn TypeScript as well.
React came to the rescue !

### Tailwind CSS
Selected for:
- Rapid UI development with utility classes
- Built-in dark mode support
- Highly customizable design system
- Small production bundle size with PurgeCSS
- Responsive design made simple

### CodeMirror
Implemented because:
- Robust code editing capabilities
- Extensive language support
- Customizable themes
- Built-in features like syntax highlighting

### Lucide React
Chosen for:
- Lightweight SVG icons
- Consistent design language
- Easy and fast customization
- Tree-shakeable for optimal bundle size 👌

### Axios
Selected over fetch for:
- Consistent error handling
- Request/response interceptors
- Automatic JSON transformation
- Better browser support
- Progress monitoring capabilities

### Zustand
Preferred over Redux/Context for:
- Minimal boilerplate
- Simple yet powerful state management
- Built-in persist middleware
- Excellent TypeScript support
- Small bundle size

## Development Tools

### Docker
Implemented for:
- Consistent development environments
- Easy deployment
- Isolated services
- Simple scaling capabilities
- Environment variable management
- A must to learn in developing

### Vite
Chosen over Create React App for:
- Lightning-fast hot module replacement
- Modern development experience
- Better build times
- Optimized production builds
- Native ESM support
- Create React App gave me a headache when I tried
- Better community to find help

### ESLint
Implemented for:
- Code consistency
- Error prevention
- Best practices enforcement
- Automatic code formatting
- Custom rule configuration

### PostCSS
Selected because:
- Required for Tailwind CSS
- Future CSS features today
- Autoprefixer for browser compatibility
- CSS optimization and minification


## Main Backend Components

## index.js
***

## Purpose
This is the main entry point for the backend server.
Setting up the core infrastructure for handling code snippet operations.

## Key Components

### Dependencies
```javascript

const express = require('express');
const mongoose = require('mongoose');
const cors = require('cors');
const dotenv = require('dotenv');
````

- express
  Web framework for routing and middleware
- mongoose
   MongoDB object modeling tool
- cors
   Enables cross-origin requests (necessary for frontend communication)
- dotenv
   Loads environment variables for configuration

```javascript
Database Schema
javascriptCopyconst snippetSchema = new mongoose.Schema({
    title: { type: String, required: true },
    code: { type: String, required: true },
    language: { type: String, default: 'javascript' },
    description: String,
    createdAt: { type: Date, default: Date.now },
    updatedAt: { type: Date, default: Date.now }
});
````
Defines the structure for code snippets with:

- Required title and code fields
- Default JavaScript language
- Optional description
- Automatic timestamps

### API Endpoints - Mongoose

GET /api/snippets: Retrieves all snippets, sorted by creation date
POST /api/snippets: Creates new snippets with validation
DELETE /api/snippets/:id: Removes specific snippets

### Error Handling
Implements basic error handling for:

- Database connection issues
- Invalid requests
- Missing resources
- Server errors

## .env
***

## Purpose
This is the Configuration file that stores environment variables for the application. It keep sensitive data and configuration settings separate from the codebase.

## Key Components

### Environment Variables
```javascript
PORT=5000
MONGODB_URI=mongodb://localhost:27017/snippetdb
````
### Defined variables

- PORT: Server port configuration for the Express application
- MONGODB_URI: MongoDB connection string specifying database location and name

### Design Decisions

Port Configuration:

- Default port set to 5000
- Commonly used for development environments
- Avoids conflicts with standard ports (3000 for React, etc.)


### MongoDB Connection

- Uses local MongoDB instance
- Database name 'snippetdb' for code snippets storage
- Standard MongoDB port (27017)

### Security Considerations

- Environment variables separate sensitive data from code
- Not committed to version control
- Allows different configurations per environment
- Follows security best practices for configuration management

### Usage

- Loaded using dotenv package
- Referenced in application using process.env
- Can be overridden by deployment environment variables

## Dockerfile
***

## Purpose
Docker configuration file that defines how to build the backend container image, ensuring consistent development and deployment environments.

## Key Components

### Base Image Selection
```dockerfile
FROM node:18-alpine
````

### Uses Node.js LTS (Long Term Support) version 18
- Alpine-based for minimal image size
- Ensures stability and security updates

### Working Directory
````dockerfile
WORKDIR /app
````
- Creates and sets /app as working directory
- Isolates application files
- Provides consistent file path references

### Dependency Installation
````dockerfile
COPY package*.json ./
 RUN npm install
````
- Copies package files first for better caching
- Installs all required npm packages
- Layer optimization for faster builds

### Application Files
````dockerfile
COPY . .
````
- Copies all project files to container
- Happens after dependency installation to leverage Docker cache

### Port Configuration
````dockerfile
EXPOSE 5000
````
- Exposes port 5000 for container communication
- Matches backend server port
- Documents service networking requirements

### Application Startup
````dockerfile
CMD ["npm", "start"]
````
- Defines default command to start server
- Uses npm script defined in package.json
- Can be overridden at runtime

## Design Decisions in File

#### Alpine Base

- Minimizes container size
- Reduces attack surface
- Improves deployment speed

#### Layer Ordering

- Optimizes build cache usage
- Speeds up rebuilds
- Follows Docker best practices

#### Node LTS

- Ensures long-term stability
- Regular security updates
- Better compatibility

## Main Frontend Components

## App.jsx
***

## Purpose
Main frontend application component that manages the code snippet library's user interface and functionality.
It has multiple functionalities as snippet management, search, theme toggling, and code editing.

## Key Components

### Dependencies
```javascript
// React and Core Dependencies
import { useState, useEffect, useCallback } from "react";

// CodeMirror Language Support
import { javascript } from "@codemirror/lang-javascript";
import { python } from "@codemirror/lang-python";
// ... other language imports

// UI Components and Icons
import { Copy, Check, Menu, Trash2, Download, Search } from "lucide-react";

// Custom Components
import CodeEditor from "./components/CodeEditor";
import ThemeToggle from "./components/ThemeToggle";
import { useToast } from "./components/ui/use-toast";
````

### React hooks for state and lifecycle management
- CodeMirror language support for syntax highlighting
- UI icons from lucide-react
- Custom components for editor and theme functionality

## Core Features

### State Management
```javascript
javascriptCopyconst [snippets, setSnippets] = useState([]);
const [currentSnippet, setCurrentSnippet] = useState({/*...*/});
const [searchTerm, setSearchTerm] = useState("");
````

- Manages snippet collection
- Handles current editing state
- Controls search and filter state


### Keyboard Shortcuts

```javascript
const handleKeyboard = useCallback((e) => {
    if ((e.ctrlKey || e.metaKey) && e.key === "f") {
      e.preventDefault();
      setSearchVisible(true);
      document.getElementById("search-input")?.focus();
    }
    if (e.key === "Escape") {
      setSearchVisible(false);
    }
  }, []);

  useEffect(() => {
    window.addEventListener("keydown", handleKeyboard);
    return () => window.removeEventListener("keydown", handleKeyboard);
  }, [handleKeyboard]);

  useEffect(() => {
    const fetchSnippets = async () => {
      try {
        const response = await axios.get("http://localhost:5000/api/snippets");
        setSnippets(response.data);
      } catch (error) {
        console.error("Error fetching snippets:", error);
      }
    };
    fetchSnippets();
  }, []);
````

### Global keyboard shortcuts for search
- Event cleanup on unmount


### CRUD Operations

- handleSubmit
Creates/updates snippets
- handleDelete
Removes snippets
- handleCopy
Copies code to clipboard
```javascript
const handleSubmit = async (e) => {
    e.preventDefault();

    const errors = {
      title: !currentSnippet.title.trim(),
      language: !currentSnippet.language.trim(),
      description: !currentSnippet.description.trim(),
      code: !currentSnippet.code.trim(),
    };

    setFormErrors(errors);

    if (errors.title || errors.language || errors.description || errors.code) {
      toast({
        variant: "destructive",
        title: "Empty fields",
        description: "Do not forget to fill in Title, Description and Code.",
      });
      return;
    }

    if (checkDuplicateTitle(currentSnippet.title)) {
      toast({
        variant: "destructive",
        title: "Duplicate Title",
        description:
          "A snippet with this title already exists. Please choose a different title.",
      });
      setFormErrors((prev) => ({ ...prev, title: true }));
      return;
    }

    try {
      const response = await axios.post(
        "http://localhost:5000/api/snippets",
        currentSnippet
      );
      setSnippets([response.data, ...snippets]);
      setCurrentSnippet({
        title: "",
        code: "",
        language: "javascript",
        description: "",
      });

      toast({
        title: "Success",
        description: "Snippet saved successfully!",
      });
    } catch (error) {
      console.error("Error saving snippet:", error);
      toast({
        variant: "destructive",
        title: "Error",
        description:
          error.response?.data?.message ||
          "Failed to save snippet. Please try again.",
      });
    }
  };
 const handleDelete = async (id) => {
    try {
      await axios.delete(`http://localhost:5000/api/snippets/${id}`);
      setSnippets(snippets.filter((snippet) => snippet._id !== id));
      toast({
        variant: "info",
        title: "Success!",
        description: "Snippet deleted successfully!",
      });
    } catch (error) {
      console.error("Error deleting snippet:", error);
      toast({
        variant: "destructive",
        title: "Error",
        description: "Failed to delete snippet. Please try again.",
      });
    }
  };

  const handleCopy = async (code, id) => {
    try {
      await navigator.clipboard.writeText(code);
      setCopiedId(id);
      setTimeout(() => setCopiedId(null), 2000);
      toast({
        title: "Success",
        description: "Code copied to clipboard!",
      });
    } catch (error) {
      console.error("Error copying to clipboard:", error);
      toast({
        variant: "destructive",
        title: "Error",
        description: "Failed to copy code. Please try again.",
      });
    }
  };

````
### Search & Filter
```javascript
  const filteredSnippets = snippets.filter((snippet) => {
    const searchLower = searchTerm.toLowerCase();
    const matchesSearch =
      snippet.title.toLowerCase().includes(searchLower) ||
      snippet.description.toLowerCase().includes(searchLower) ||
      snippet.code.toLowerCase().includes(searchLower);
    const matchesLanguage =
      selectedLanguages.length === 0 ||
      selectedLanguages.includes(snippet.language);
    return matchesSearch && matchesLanguage;
  });
````
- Text-based search across all fields
- Language-based filtering
- Highlighted search matches

### Error Handling

- Form validation with visual feedback
- Toast notifications for operations
- API error handling
- Duplicate title checking

## Design Decisions

### Layout Structure:

- Split view with sidebar and editor
- Fixed header and footer
- Responsive design considerations

### Theme Implementation

- Dark/light mode support
- Consistent styling across components
- Tailwind CSS for styling

### User Experience

- Immediate feedback for actions
- Keyboard shortcuts
- Hover states for actions
## CodeEditor.jsx
***

## Purpose
Acts as a wrapper around CodeMirror with added theme synchronization.
It is a vital component built on CodeMirror that provides syntax highlighting, theme support, and code editing capabilities for the snippet library.

## Key Components

### Dependencies
```javascript
import { useEffect, useState } from "react";
import CodeMirror from "@uiw/react-codemirror";
import { EditorView } from "@codemirror/view";
import PropTypes from "prop-types";
````

### React hooks for state/effects
- CodeMirror for core editor functionality
- EditorView for theme customization
- PropTypes for type checking

## Core Features
### Theme Management
```javascript
javascriptCopyconst [currentTheme, setCurrentTheme] = useState(localStorage.getItem('theme'));

useEffect(() => {
    const handleThemeChange = () => {
        setCurrentTheme(localStorage.getItem('theme'));
    };
    window.addEventListener('themeChange', handleThemeChange);
    return () => window.removeEventListener('themeChange', handleThemeChange);
}, []);
````

- Syncs with app-wide theme
- Listens for theme changes
- Cleans up event listeners

### Editor Configuration
````javascript
<CodeMirror
    value={value}
    height="100%"
    width="100%"
    theme={currentTheme === 'dark' ? 'dark' : 'light'}
    extensions={[...extensions]}
/>
````

### Full size editor
- Theme-aware styling
- Language extensions support

### Theme Customization

```javascript
EditorView.theme({
    '&': {
        backgroundColor: currentTheme === 'dark' ? '#1e293b' : '#ffffff',
        color: currentTheme === 'dark' ? '#ffffff' : '#1e293b',
    },
    '.cm-content': {
        color: currentTheme === 'dark' ? '#ffffff' : '#1e293b',
        caretColor: currentTheme === 'dark' ? '#ffffff' : '#1e293b'
    },
    '&.cm-focused .cm-cursor': {
        borderLeftColor: currentTheme === 'dark' ? '#ffffff' : '#1e293b'
    },
    '&.cm-focused .cm-selectionBackground, ::selection': {
        backgroundColor: currentTheme === 'dark' ? 'rgba(255,255,255,0.2)' : 'rgba(0,0,0,0.2)'
    },
    '.cm-gutters': {
        backgroundColor: currentTheme === 'dark' ? '#1e293b' : '#ffffff',
        color: currentTheme === 'dark' ? '#ffffff' : '#1e293b',
        borderRight: currentTheme === 'dark' ? '1px solid #334155' : '1px solid #e2e8f0'
    }
})
````
### Theme-specific colors
- Custom cursor and selection styles
- Gutter styling
- Consistent with app theme

```javascript
basicSetup={{
        lineNumbers: true,
        highlightActiveLineGutter: true,
        highlightSpecialChars: true,
        foldGutter: true,
        drawSelection: true,
        dropCursor: true,
        allowMultipleSelections: true,
        indentOnInput: true,
        bracketMatching: true,
        closeBrackets: true,
        autocompletion: true,
        rectangularSelection: true,
        crosshairCursor: true,
        highlightActiveLine: true,
        highlightSelectionMatches: true,
        closeBracketsKeymap: true,
        defaultKeymap: true,
        searchKeymap: true,
        historyKeymap: true,
        foldKeymap: true,
        completionKeymap: true,
        lintKeymap: true,
    }}
````

### Editor Features

- Line numbers
- Syntax highlighting
- Code folding
- Auto-completion
- Search functionality
- Selection handling
- Multiple selections
- History management

```javascript
CodeEditor.propTypes = {
    value: PropTypes.string.isRequired,
    onChange: PropTypes.func.isRequired,
    extensions: PropTypes.array.isRequired,
};
````
### Error Handling

- PropTypes validation
- Event listener cleanup
- Theme fallback defaults

## Design Decisions

### Theme Integration

- Real-time theme synchronization
- Consistent color scheme
- Smooth transitions

### Editor Setup

- Comprehensive feature set
- Full width/height layout
- Optimized for code editing

### User Experience

- Standard editor shortcuts
- Professional appearance

## Conclusion

From using React and MongoDB to containerizing the backend with Docker.
Every decision was made to ensure to learn how to apply in this scale,
core concepts in design, decision taking and implementation of these technologies.

This endevour is a testament to my growth and dedication to becoming a better developer.
It’s not just a project, but a step towards mastering full-stack development.
Thank you for reading and following along with my process CS50 😊.
I hope it inspires others to embark on their own learning journeys.
