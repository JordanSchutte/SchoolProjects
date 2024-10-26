const mongoose = require('mongoose');
const Trip = require('./travlr');
const fs = require('fs');
const path = require('path');

const dbURI = 'mongodb://localhost/travlr';

const seedData = async () => {
  try {
    await mongoose.connect(dbURI);
    console.log(`Mongoose connected to ${dbURI}`);

    // Clear existing data
    await Trip.deleteMany({});

    // Read JSON file
    const jsonPath = path.join(__dirname, '..', '..', 'data', 'travel.json');
    const jsonData = fs.readFileSync(jsonPath, 'utf8');
    const travelData = JSON.parse(jsonData);

    // Insert new data
    await Trip.insertMany(travelData.trips);
    console.log('Database seeded!');
  } catch (err) {
    console.error('Error seeding database:', err);
  } finally {
    await mongoose.connection.close();
    console.log('Mongoose disconnected');
  }
};

seedData();