const express = require('express');
const path = require('path');
const app = express();
const port = 3000;

app.use(express.static(path.join(__dirname, 'public')));

app.set('view engine', 'hbs');
app.set('views', './app_server/views');

const routes = require('./app_server/routes/index');
app.use('/', routes);

app.listen(port, () => {
  console.log(`Travlr Getaways app listening at http://localhost:${port}`);
});