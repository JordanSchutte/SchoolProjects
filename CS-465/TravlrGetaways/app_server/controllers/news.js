const fs = require('fs');
const path = require('path');

const list = (req, res) => {
  const data = JSON.parse(fs.readFileSync(path.join(__dirname, '../../data/news.json'), 'utf8'));
  res.render('news', data);
};

module.exports = { list };