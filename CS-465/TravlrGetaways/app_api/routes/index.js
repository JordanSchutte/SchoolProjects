const express = require('express');
const router = express.Router();
const { expressjwt: jwt } = require('express-jwt');
const auth = jwt({
  secret: process.env.JWT_SECRET,
  algorithms: ['HS256'],
  userProperty: 'payload'
});

const authController = require('../controllers/authentication');
const tripsController = require('../controllers/trips');

// Authentication routes
router.post('/register', authController.register);
router.post('/login', authController.login);

// Trip routes
router.route('/trips')
  .get(tripsController.tripsList)
  .post(auth, tripsController.tripsAddTrip);

router.route('/trips/:tripCode')
  .get(tripsController.tripsFindCode)
  .put(auth, tripsController.tripsUpdateTrip)
  .delete(auth, tripsController.tripsDeleteTrip);

module.exports = router;