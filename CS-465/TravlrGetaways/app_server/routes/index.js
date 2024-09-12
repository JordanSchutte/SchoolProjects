const express = require('express');
const router = express.Router();
const ctrlMain = require('../controllers/main');
const ctrlTraveler = require('../controllers/traveler');

router.get('/travel', ctrlTraveler.travel);
router.get('/', ctrlMain.index);

module.exports = router;