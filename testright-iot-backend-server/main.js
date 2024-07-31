const express = require('express');
const bodyParser = require('body-parser');
const cors = require('cors');
const app = express();

const devices = {};
const TIMEOUT = 5000; 

app.use(bodyParser.json());
app.use(cors());

app.post('/update_mac', (req, res) => {
    const { mac_address } = req.body;
    const timestamp = Date.now();
    
    devices[mac_address] = { last_update: timestamp };
    
    res.json({ message: 'MAC address updated' });
});

app.get('/devices', (req, res) => {
    res.json(devices);
});

setInterval(() => {
    const now = Date.now();
    for (const [mac_address, info] of Object.entries(devices)) {
        if (now - info.last_update > TIMEOUT) {
            delete devices[mac_address];
        }
    }
}, TIMEOUT);

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`);
});
