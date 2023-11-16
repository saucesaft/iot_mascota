const mysql = require('../database/db')

class MainController {

    async logIntervalo(req , res){

        if(req.params.machineID != null && req.params.calidadAgua != null && req.params.ultrasonicoDist != null ) {
            let machineID = req.params.machineID
            let calidad = req.params.calidadAgua;
            let dist = req.params.ultrasonicoDist;

            console.log("distancia: ", dist);

            var sql = ` INSERT INTO sensor_intervalo
                            ( id_maquina, calidad_agua, nivel_agua, timestamp )
                        VALUES 
                            ( ${machineID}, ${calidad}, ${dist}, NOW() )`

            console.log(sql);

            mysql.query(sql, (error,data,fields) => {
                if(error) {
                    res.status(500)
                    res.send(error.message)
                } else {
                    console.log(data)
                    res.json({
                        status: 200,
                        message: "Log uploaded successfully",
                        affectedRows: data.affectedRows
                    })
                }
            })
        } else {
          res.send('Por favor llena todos los datos!')
        }
    }
    
    async getLogs(req,res){
        console.log("Get Logs")
        console.log(req.params.deviceID)
        if(req.params.deviceID!=null){
            let deviceID = req.params.deviceID;
            var sql = `SELECT * FROM sensor_intervalo where machine_id='${deviceID}'`
            mysql.query(sql, (error, data, fields) => {
                if(error) {
                    res.status(500)
                    res.send(error.message)
                } else {
                    console.log(data)
                    res.json({
                        data
                    })
                }
            })
        }
    }
}

const mascotaController = new MainController()
module.exports = mascotaController;
