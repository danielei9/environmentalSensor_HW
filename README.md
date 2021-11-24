# environmentalSensor

# EnvironmentalSensor

El proyecto consta de una placa maestra donde se pueden conectar varios sensores predeterminados como temperatura, humedad, sensor de sustrato y ruido. Esta placa (Master) se comunica mediante I2C con otra placa expansión (Slave) que se comunica con un máximo de 5 sensores de cualquier tipo mediante UART (mirar especificaciones de sensores admitidos).

Una vez adquiridas las medidas de los sensores, se procesan y son enviadas mediante LORA o 4G (gsm).
En el caso de LORA: el dispositivo “Master” envía datos a un Gateway de LORA, donde mediante un Bridge realiza el cambio LORA - MQTT y enviamos los datos a la plataforma
En el caso de 4G: se envía directamente a través de MQTT.
### Master:
![Master](https://github.com/danielei9/environmentalSensor_HW/blob/main/doc/Master.png)

### Slave:

![This is an image](https://github.com/danielei9/environmentalSensor_HW/blob/main/doc/Slave.png)

### Pre-requisitos 📋

Será necesario tener instalado Visual studio code con Platformio.

### Instalación 🔧
Una vez descargado el repositorio podrás abrir desde platformio o visual studio el proyecto indivualmente el Master o el Slave para subir a una placa el código.

## Versionado 📌
        Version 1.0
## Autores ✒️

* **Yeray** 
* **Daniel Burruchaga Sola** 
