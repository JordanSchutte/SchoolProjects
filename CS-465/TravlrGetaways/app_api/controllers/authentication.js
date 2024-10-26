const passport = require('passport');
const mongoose = require('mongoose');
const User = mongoose.model('User');

const register = async (req, res) => {
  console.log('Register function called');
  if (!req.body.name || !req.body.email || !req.body.password) {
    return res.status(400).json({"message": "All fields required"});
  }

  try {
    const user = new User();
    user.name = req.body.name;
    user.email = req.body.email;
    user.setPassword(req.body.password);
    
    await user.save();
    const token = user.generateJwt();
    res.status(200).json({token});
  } catch (err) {
    console.error('Error in register function:', err);
    res.status(400).json(err);
  }

  const user = new User();
  user.name = req.body.name;
  user.email = req.body.email;
  user.setPassword(req.body.password);
  
  user.save((err) => {
    if (err) {
      res.status(400).json(err);
    } else {
      const token = user.generateJwt();
      res.status(200).json({token});
    }
  });
};

const login = (req, res) => {
  if (!req.body.email || !req.body.password) {
    return res.status(400).json({"message": "All fields required"});
  }
  passport.authenticate('local', (err, user, info) => {
    if (err) {
      return res.status(404).json(err);
    }
    if (user) {
      const token = user.generateJwt();
      res.status(200).json({token});
    } else {
      res.status(401).json(info);
    }
  })(req, res);
};

module.exports = {
  register,
  login
};