# Use Node.js LTS version
FROM node:18-alpine

# Set working directory
WORKDIR /app

# Copy package files
COPY package*.json ./

# Install dependencies
RUN npm install
RUN npm install @codemirror/lang-python @codemirror/lang-cpp @codemirror/lang-html @codemirror/lang-css @codemirror/lang-sql @codemirror/lang-java

# Copy project files
COPY . .

# Start in development mode with host
CMD ["npm", "run", "dev", "--", "--host", "--force"]