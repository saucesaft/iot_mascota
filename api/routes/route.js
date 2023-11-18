const express = require('express');
const mascotaController = require('../controllers/temp_controller');
const router = express.Router();

// sensores de intervalo
router.post('/api/:machineID/sensor/intervalo/:calidadAgua/:ultrasonicoDist', mascotaController.logIntervalo);

// sensores de cambio
router.post('/api/:machineID/sensor/cambio/:sensor/:lectura', mascotaController.logCambio);

module.exports = router;
