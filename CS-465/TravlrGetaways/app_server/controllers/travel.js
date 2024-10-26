const fetch = (...args) => import('node-fetch').then(({default: fetch}) => fetch(...args));

const tripsList = async (req, res) => {
    try {
        const response = await fetch('http://localhost:3000/api/trips');
        const trips = await response.json();

        if (!Array.isArray(trips)) {
            throw new Error('API response is not an array');
        }

        res.render('travel', { 
            title: 'Travlr Getaways', 
            trips: trips
        });
    } catch (err) {
        console.error(err);
        res.status(500).render('error', {
            message: 'Error fetching trips',
            error: { status: 500, stack: err.stack }
        });
    }
};

const tripInfo = async (req, res) => {
    try {
        const response = await fetch(`http://localhost:3000/api/trips/${req.params.tripCode}`);
        const trip = await response.json();
        res.render('trip-info', { 
            title: trip.name, 
            trip 
        });
    } catch (err) {
        console.error(err);
        res.status(500).render('error', {
            message: 'Error fetching trip info',
            error: { status: 500, stack: err.stack }
        });
    }
};

module.exports = {
    tripsList,
    tripInfo
};