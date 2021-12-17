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

# **Contents**
- [**Project**](#firmware-hardware-module)
- [**Contents**](#contents)
- [**Pre requirements**](#pre-requirements)
- [**Getting started**](#getting-started)
- [**Project structure**](#project-structure)
- [**Firmware**](#firmware)
  - [**Master Code**](#master-code)
  - [**Slave Code**](#slave-code)
  - [**Measures**](#measures)
- [**Deployment**](#deployment)

# **Pre requirements**
This Project is being developed using `Platformio` in Visual Studio Code so you need to have being installed it and dependences. 

- Install Platformio in Visual Studio Code
# **Getting started**
1. Clone the repository
```
git clone https://github.com/ycansam/environmentalSensor_HW
```
Now you can start with the implementation of new features to comunicate with the ttgo and arduino nano

# **Project structure**
```
environmentalSensor_HW/
    ├──  doc/
    ├── Firmware/
        ├── Master/
        ├── PruebaLora/
        ├── Slave_FW_1_0
    ├── Hardware/
        ├── Master/
        ├── Slave
    ├── tests/
```

## **Enviromental devices**
Enviromental devices are the core of the application. These devices are a modular sensor hub that can contain multiple sensors according to user requirements. Multiple devices are grouped on the same gateway.
<br>
# **Firmware**
### **MASTER CODE**
#### **DEFINING CONEXION `4G` or `LORA`**
In file `Firmware/Master/main.cpp`.
* Use **#define PROTOCOL_4G** to use 4G comunication
* Use **#define PROTOCOL_LORA** to use Lora comunication
``` c++
#define PROTOCOL_4G
//#define PROTOCOL_LORA
unsigned long mill = 0;
#include <../lib/PublishersClient.h> // After defining the comunication include this libraries
#include <Wire.h>
```
##### **DEFINING 4G VARIABLES**
Change this variable acording to your SIM
In file `Firmware/Master/lib/PublishersClient.h`.
* GPRS: "orangeworld"
* GPRSUser: "orange"
* GPRSPass: "orange"
* SIMPin: null 

``` c++
#include <../lib/Protocol4G.h>
Protocol4G protocol4G(GPRS, GPRSUser, GPRSPass, SIMPin); // constructor normal
Publisher *publisher = &protocol4G;            
```

### **Setting Up the Conexion `TLS MQTT`**
##### **Configure if using `4G COMUNICATION`**
If is it needed to change the broker, username or etc on the MQTT connection you need to change this parameters in class Protocol4G in Firmware/Master/lib
``` c++
const char broker[] = "broker";
int port = port(int);
const char *username = "userBroker";
const char *password = "passBroker";
// example
// codigoPostal/ambiental/idDispositivo/
char topic[] = "46701/ambiental/1/";
const char topicSubscribed[] = "gesinen/#";
```
### **Send** `MQTT` **via 4G**
```
TOPIC /46701/ambiental/1/#
```
``` c++
// JSON MESSAGE EXAMPLE
function sendData(uint8_t *arrayData){
 ..
 String message = "{\"deviceEui\":1,\"value\": 25.222,\"type\": \"co2\", \"unit\": \"ppm\"}"
 ..
 }
```
Body:
| Name          |    Type    | Required | Description |
| ------------- |:----------:|:--------:|:-----------|
| deviceEui         | `string`   |  ✓       | DeviceEui  |
| value          | `float`   |  ✓       | Measure's value |
| unit          | `string`  |  ✓       | Measure's unit |
| type          | `string`  |  ✓       | Measure's type |
### **Request data from Slaves**
Using comunication I2C, pins using TTGO
* SDA: 21
* SCL: 22
``` c++
// Defining
SlaveController slaveController(21, 22);
```
``` c++
// Setup
// Initialize the I2C Master Comunication
slaveController.initMaster();
```
### SlaveController Fcuntions
#### Request data to a specific slave
``` c++
      byte* requestMeasuresToSlave(uint8_t, uint8_t){...}
      @param slaveAddress -> Slave address in Hexadecimal
      @param bytesToRequest -> number of Bytes
      @returns *byte -> byte array
```

``` c++
    // Example
      byte *arrayData = slaveController.requestMeasuresToSlave(0x20, bytesToRequest);
      printBytesArray(arrayData, bytesToRequest);
```

#### Scan Slaves
Scans the I2C conexion looking for slaves
``` c++
    void scanSlaves(){..}
    // prints the Slaves addresses
    // prints "Not Found" if didnt found any slave connected
```

## **SLAVE CODE**
#### Receiving commands from master
``` c++
   void receiveEvent(int bytes)
	// Se reciben eventos del maestro mediante comandos especificados en la cabezera del archivo main
```
Se inicializan los sensores y se duermen cuando se inicializa el esclavo.
El esclavo se inicializa con via I2C con una direccion
#### Inicializando el esclavo
``` c++
setup(){...

   Wire.begin(I2C_SLAVE_ADDR);
	// Se ha de definir #I2C_SLAVE_ADDR 0x20 
	// En hexadecimal
...	}
```
#### Leer comandos del maestro
``` c++
loop(){

	if (data != 0) // comprueba que el maestro ha enviado algun comando
	if (data == REQUEST_COMMAND) // dependiendo del comando ejecuta una accion u otra para posteriormente pedir un request de datos.
}
```
####Recoger las medidas de los sensores mediante semaforos
``` c++
// Recoger los datos 
void requestDataSensors();

// Ejemplo por separado
Sensor sensor1 = Sensor();
sensor1.getMeasure();
sensor1.getGasConcentration()

```

####Dormir & Despertar los sensores	
Despues de despertar y dormir cada sensor se ha de esperar 5 segundos para que vuelvan a tomar medidas y se estabilizen
``` c++
void wakeUpSensors(); // despierta los sensores
void sleepSensors(); // duerme los sensores

// Ejemplos por separado
Sensor sensor1 = Sensor();
sensor1.wakeUp();
sensor1.sleep()
```
####Recoger Informacion de Los Sensores

``` c++
void requestSensorsInformation() // recoge informacion de todos los sensores
// Ejemplo por separado
Sensor sensor1 = Sensor();
sensor1.getSensorInformation();
sensor1.getSensorType()
```

#### Envio de datos al master
Se han de enviar el array de datos con un maximo de 8 de length en cada envio para evitar errores en la lectura, Tambien se ha de hacer un flush para limpiar la Wire()
``` c++
void requestEvent()
{..}
```
# **License**
All the code in this repository is owned by [Daniel Burruchaga & Yeray Candel](https://ycansam.upv.edu.es/ & http://buchspro.com/).
Copyright © 2021, Yeray Candel. Daniel Burruchaga.
0 comments on commit cb6e9bf
Please sign in to comment.
© 2021 GitHub, Inc.
Terms
Privacy
Security
Status
Docs
Contact GitHub
Pricing
API
Training
Blog
About
Loading complete
