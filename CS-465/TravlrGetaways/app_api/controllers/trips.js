const mongoose = require('mongoose');
const Trip = mongoose.model('Trip');
const User = mongoose.model('User');

const getUser = (req, res, callback) => {
    if (req.payload && req.payload.email) {
      User
        .findOne({ email : req.payload.email })
        .exec((err, user) => {
          if (!user) {
            return res
              .status(404)
              .json({"message": "User not found"});
          } else if (err) {
            console.log(err);
            return res
              .status(404)
              .json(err);
          }
          callback(req, res, user.name);
        });
    } else {
      return res
        .status(404)
        .json({"message": "User not found"});
    }
};

const tripsList = async (req, res) => {
    try {
        const trips = await Trip.find().exec();
        res.status(200).json(trips);
    } catch (err) {
        res.status(500).json({"error": err});
    }
};

const tripsFindCode = async (req, res) => {
    try {
        const trip = await Trip.findOne({'code': req.params.tripCode}).exec();
        if (!trip) {
            return res.status(404).json({"message": "trip not found"});
        }
        res.status(200).json(trip);
    } catch (err) {
        res.status(500).json({"error": err});
    }
};

const tripsAddTrip = (req, res) => {
    getUser(req, res, (req, res) => {
        Trip.create({
            code: req.body.code,
            name: req.body.name,
            length: req.body.length,
            start: req.body.start,
            resort: req.body.resort,
            perPerson: req.body.perPerson,
            image: req.body.image,
            description: req.body.description
        }, (err, trip) => {
            if (err) {
                return res.status(400).json(err);
            } else {
                return res.status(201).json(trip);
            }
        });
    });
};

const tripsUpdateTrip = (req, res) => {
    getUser(req, res, (req, res) => {
        Trip.findOneAndUpdate({'code': req.params.tripCode}, {
            code: req.body.code,
            name: req.body.name,
            length: req.body.length,
            start: req.body.start,
            resort: req.body.resort,
            perPerson: req.body.perPerson,
            image: req.body.image,
            description: req.body.description
        }, { new: true })
        .then(trip => {
            if (!trip) {
                return res.status(404).json({"message": "Trip not found"});
            }
            res.status(200).json(trip);
        })
        .catch(err => {
            res.status(400).json(err);
        });
    });
};

const tripsDeleteTrip = (req, res) => {
    getUser(req, res, (req, res) => {
        Trip.findOneAndDelete({'code': req.params.tripCode})
        .then(trip => {
            if (!trip) {
                return res.status(404).json({"message": "Trip not found"});
            }
            res.status(204).json(null);
        })
        .catch(err => {
            res.status(400).json(err);
        });
    });
};

module.exports = {
    tripsList,
    tripsFindCode,
    tripsAddTrip,
    tripsUpdateTrip,
    tripsDeleteTrip
};