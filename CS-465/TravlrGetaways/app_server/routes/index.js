const express = require('express');
const router = express.Router();
const ctrlMain = require('../controllers/main');
const ctrlTravel = require('../controllers/travel');
const ctrlRooms = require('../controllers/rooms');
const ctrlMeals = require('../controllers/meals');
const ctrlNews = require('../controllers/news');
const ctrlAbout = require('../controllers/about');
const ctrlContact = require('../controllers/contact');

router.get('/', ctrlMain.index);
router.get('/travel', ctrlTravel.travel);
router.get('/rooms', ctrlRooms.list);
router.get('/meals', ctrlMeals.list);
router.get('/news', ctrlNews.list);
router.get('/about', ctrlAbout.about);
router.get('/contact', ctrlContact.contact);

module.exports = router;