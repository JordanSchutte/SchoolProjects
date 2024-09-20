const fs = require('fs');
const path = require('path');

const about = (req, res) => {
  const data = JSON.parse(fs.readFileSync(path.join(__dirname, '../../data/about.json'), 'utf8'));
  res.render('about', data);
};

module.exports = { about };