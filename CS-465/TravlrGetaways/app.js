const express = require('express');
const path = require('path');
const hbs = require('hbs');
const app = express();

// Set up view engine
app.set('view engine', 'hbs');
app.set('views', path.join(__dirname, 'app_server', 'views'));
hbs.registerPartials(path.join(__dirname, 'app_server', 'views', 'partials'));

// Routes
app.use('/', require('./app_server/routes/index'));

// Serve static files
app.use(express.static(path.join(__dirname, 'public')));

const port = process.env.PORT || 3000;
app.listen(port, () => {
  console.log(`Server running on port ${port}`);
});