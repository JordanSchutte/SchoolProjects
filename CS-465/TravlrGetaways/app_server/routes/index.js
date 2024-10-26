const express = require('express');
const router = express.Router();
const ctrlMain = require('../controllers/main');
const ctrlTravel = require('../controllers/travel');

router.get('/', ctrlMain.index);
router.get('/travel', ctrlTravel.tripsList);
router.get('/travel/:tripCode', ctrlTravel.tripInfo);

module.exports = router;