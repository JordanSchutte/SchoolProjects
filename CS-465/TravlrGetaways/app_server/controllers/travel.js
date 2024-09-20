const fs = require('fs');
const path = require('path');

const travel = (req, res) => {
  const data = JSON.parse(fs.readFileSync(path.join(__dirname, '../../data/travel.json'), 'utf8'));
  res.render('travel', data);
};

module.exports = { travel };