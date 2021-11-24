# environmentalSensor

Estructura:
|
|-- Hardware
|       |--Slave
|       |    Contiene los proyectos kicad de la placa Slave. Contiene Schematic y PCB design + Librerias.
|       |--Master
|       |    Contiene los proyectos kicad de la placa Master. Contiene Schematic y PCB design + Librerias.
|-- Firmware
|       |
|       |--test 
|       |    Contiene los test implementados actualmente en la parte de Hardware.
|       |--Master
|       |    Contiene el proyecto del codigo C/C++ en Arduino+ESP framework para la placa Master, utilizando Visual Studio la |       |    extension PlatformIO
|       |--Slave
|       |    Contiene el proyecto del codigo C/C++ en Arduino+ESP framework para la placa Slave, utilizando Visual Studio la |       |    extension PlatformIO

El proyecto consta de una placa maestra donde se pueden conectar varios sensores predeterminados como temperatura, humedad, sensor de sustrato y ruido. Esta placa (Master) se comunica mediante I2C con otra placa expansión (Slave) que se comunica con un máximo de 5 sensores de cualquier tipo mediante UART (mirar especificaciones de sensores admitidos).

Una vez adquiridas las medidas de los sensores, se procesan y son enviadas mediante LORA o 4G (gsm).

En el caso de LORA: el dispositivo “Master” envía datos a un Gateway de LORA, donde mediante un Bridge realiza el cambio LORA - MQTT y enviamos los datos a la plataforma
En el caso de 4G: se envía directamente a través de MQTT.

Master:
[[https://github.com/danielei9/environmentalSensor_HW/tree/main/doc/Master.png|alt=octocat]]
Slave:
[[https://github.com/danielei9/environmentalSensor_HW/tree/main/doc/Slave.png|alt=octocat]]
