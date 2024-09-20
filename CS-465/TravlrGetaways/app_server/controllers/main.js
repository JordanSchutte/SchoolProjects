const fs = require('fs');
const path = require('path');

const index = (req, res) => {
  const data = JSON.parse(fs.readFileSync(path.join(__dirname, '../../data/index.json'), 'utf8'));
  res.render('index', data);
};

module.exports = { index };