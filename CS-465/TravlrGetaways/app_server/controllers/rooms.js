const fs = require('fs');
const path = require('path');

const list = (req, res) => {
  const data = JSON.parse(fs.readFileSync(path.join(__dirname, '../../data/rooms.json'), 'utf8'));
  res.render('rooms', data);
};

module.exports = { list };