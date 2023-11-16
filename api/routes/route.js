const express = require('express');
const mascotaController = require('../controllers/temp_controller');
const router = express.Router();

// sensores de intervalo
router.post('/api/:machineID/sensor/intervalo/:calidadAgua/:ultrasonicoDist', mascotaController.logIntervalo);

module.exports = router;
