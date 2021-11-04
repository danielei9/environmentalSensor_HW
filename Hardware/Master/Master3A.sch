EESchema Schematic File Version 4
LIBS:Master3A-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Daniel Burruchaga Sola"
Date "2021-11-04"
Rev "1.0"
Comp "Gesinen "
Comment1 "UPV Tecnologias Interactivas "
Comment2 "Sensor Ambiental"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L TTGO:TTGOv3SimGps U?
U 1 1 61823C34
P 5500 2600
F 0 "U?" H 5525 3515 50  0000 C CNN
F 1 "TTGOv3SimGps" H 5525 3424 50  0000 C CNN
F 2 "" H 5450 2950 50  0001 C CNN
F 3 "" H 5450 2950 50  0001 C CNN
	1    5500 2600
	1    0    0    -1  
$EndComp
Text Notes 3600 1050 0    79   ~ 0
sENSORES que vayan a esta placa + conexion siguiente expansión 
$Comp
L Connector_Generic:Conn_01x04 J?
U 1 1 618509C9
P 7250 1800
F 0 "J?" H 7329 1792 50  0000 L CNN
F 1 "MasterSlaves" H 7329 1701 50  0000 L CNN
F 2 "" H 7250 1800 50  0001 C CNN
F 3 "~" H 7250 1800 50  0001 C CNN
	1    7250 1800
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J?
U 1 1 61850AF5
P 7250 2650
F 0 "J?" H 7329 2692 50  0000 L CNN
F 1 "Sensor Suelo" H 7329 2601 50  0000 L CNN
F 2 "" H 7250 2650 50  0001 C CNN
F 3 "~" H 7250 2650 50  0001 C CNN
	1    7250 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 1700 6750 1700
Wire Wire Line
	7050 1800 6750 1800
Wire Wire Line
	7050 1900 6750 1900
Wire Wire Line
	7050 2000 6750 2000
Wire Wire Line
	7050 2550 6750 2550
Wire Wire Line
	7050 2650 6750 2650
Wire Wire Line
	7050 2750 6750 2750
Text Label 6850 1700 0    50   ~ 0
5V
Text Label 6850 1800 0    50   ~ 0
GND
Text Label 6750 1900 0    50   ~ 0
I2C_SDA
Text Label 6750 2000 0    50   ~ 0
I2C_SCL
Text Label 6850 2550 0    50   ~ 0
VCC
Text Label 6850 2650 0    50   ~ 0
GND
Text Label 6850 2750 0    50   ~ 0
A0
$Comp
L Connector_Generic:Conn_01x03 J?
U 1 1 61850C8A
P 7250 3100
F 0 "J?" H 7330 3142 50  0000 L CNN
F 1 "Sensor TEMP HUM" H 7330 3051 50  0000 L CNN
F 2 "" H 7250 3100 50  0001 C CNN
F 3 "~" H 7250 3100 50  0001 C CNN
	1    7250 3100
	1    0    0    -1  
$EndComp
Text Label 6850 3000 0    50   ~ 0
VCC
Text Label 6850 3100 0    50   ~ 0
GND
Text Label 6850 3200 0    50   ~ 0
A1
$Comp
L power:+5V #PWR?
U 1 1 61850D67
P 6750 1700
F 0 "#PWR?" H 6750 1550 50  0001 C CNN
F 1 "+5V" H 6765 1873 50  0000 C CNN
F 2 "" H 6750 1700 50  0001 C CNN
F 3 "" H 6750 1700 50  0001 C CNN
	1    6750 1700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61850D9F
P 6750 1800
F 0 "#PWR?" H 6750 1550 50  0001 C CNN
F 1 "GND" V 6755 1672 50  0000 R CNN
F 2 "" H 6750 1800 50  0001 C CNN
F 3 "" H 6750 1800 50  0001 C CNN
	1    6750 1800
	0    1    1    0   
$EndComp
Text Notes 4850 3800 0    50   ~ 0
VIN 5V pero funciona con 3v3\n
$Comp
L power:GND #PWR?
U 1 1 61850E89
P 5900 2100
F 0 "#PWR?" H 5900 1850 50  0001 C CNN
F 1 "GND" V 5905 1972 50  0000 R CNN
F 2 "" H 5900 2100 50  0001 C CNN
F 3 "" H 5900 2100 50  0001 C CNN
	1    5900 2100
	0    -1   -1   0   
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 61850EF7
P 5900 2000
F 0 "#PWR?" H 5900 1850 50  0001 C CNN
F 1 "+3V3" V 5915 2128 50  0000 L CNN
F 2 "" H 5900 2000 50  0001 C CNN
F 3 "" H 5900 2000 50  0001 C CNN
	1    5900 2000
	0    1    1    0   
$EndComp
Text Notes 1900 3550 0    50   ~ 0
Falta modulo lora necesito especificaciones\n del modulo ya que ibamos a usar uno pero da \nfallos de comunicacion y vamos a usar otro\nTODO: REVISAR\n
Wire Wire Line
	5150 3500 4700 3500
Text Label 4900 3500 0    50   ~ 0
VIN
$Comp
L RF95_LORA:RF95 U?
U 1 1 618517F8
P 3700 2250
F 0 "U?" H 3675 2625 50  0000 C CNN
F 1 "RF95" H 3675 2534 50  0000 C CNN
F 2 "" H 3700 2250 50  0001 C CNN
F 3 "" H 3700 2250 50  0001 C CNN
	1    3700 2250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61851911
P 4000 2100
F 0 "#PWR?" H 4000 1850 50  0001 C CNN
F 1 "GND" V 4005 1972 50  0000 R CNN
F 2 "" H 4000 2100 50  0001 C CNN
F 3 "" H 4000 2100 50  0001 C CNN
	1    4000 2100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4000 2200 4550 2200
Wire Wire Line
	4000 2300 4550 2300
Wire Wire Line
	4000 2400 4550 2400
Wire Wire Line
	4000 2500 4550 2500
Wire Wire Line
	2800 2500 3350 2500
$Comp
L power:GND #PWR?
U 1 1 61853070
P 4000 2800
F 0 "#PWR?" H 4000 2550 50  0001 C CNN
F 1 "GND" H 4005 2627 50  0000 C CNN
F 2 "" H 4000 2800 50  0001 C CNN
F 3 "" H 4000 2800 50  0001 C CNN
	1    4000 2800
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 61853076
P 2800 2500
F 0 "#PWR?" H 2800 2350 50  0001 C CNN
F 1 "+3V3" V 2815 2628 50  0000 L CNN
F 2 "" H 2800 2500 50  0001 C CNN
F 3 "" H 2800 2500 50  0001 C CNN
	1    2800 2500
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 61858485
P 3350 2200
F 0 "#PWR?" H 3350 1950 50  0001 C CNN
F 1 "GND" V 3355 2072 50  0000 R CNN
F 2 "" H 3350 2200 50  0001 C CNN
F 3 "" H 3350 2200 50  0001 C CNN
	1    3350 2200
	0    1    1    0   
$EndComp
Text Label 4100 2200 0    50   ~ 0
MISO
Text Label 4100 2300 0    50   ~ 0
MOSI
Text Label 4100 2400 0    50   ~ 0
SCK
Text Label 4100 2500 0    50   ~ 0
NSS
Wire Wire Line
	5150 2800 4700 2800
Text Label 4900 2900 0    50   ~ 0
NSS
Wire Wire Line
	5150 2900 4700 2900
Text Label 4900 2800 0    50   ~ 0
SCK
Wire Wire Line
	5150 2600 4700 2600
Text Label 4900 2700 0    50   ~ 0
MISO
Wire Wire Line
	5150 2700 4700 2700
Text Label 4900 2600 0    50   ~ 0
MOSI
NoConn ~ 3350 2100
NoConn ~ 3350 2300
NoConn ~ 3350 2400
NoConn ~ 3350 2600
NoConn ~ 3350 2700
NoConn ~ 3350 2800
NoConn ~ 4000 2600
NoConn ~ 4000 2700
$Comp
L Connector_Generic:Conn_01x02 J?
U 1 1 6185E21B
P 2600 1450
F 0 "J?" H 2520 1125 50  0000 C CNN
F 1 "FA" H 2520 1216 50  0000 C CNN
F 2 "" H 2600 1450 50  0001 C CNN
F 3 "~" H 2600 1450 50  0001 C CNN
	1    2600 1450
	-1   0    0    1   
$EndComp
Wire Wire Line
	2800 1350 3050 1350
Wire Wire Line
	2800 1450 3000 1450
$Comp
L power:GND #PWR?
U 1 1 6185EB4B
P 3000 1450
F 0 "#PWR?" H 3000 1200 50  0001 C CNN
F 1 "GND" H 3005 1277 50  0000 C CNN
F 2 "" H 3000 1450 50  0001 C CNN
F 3 "" H 3000 1450 50  0001 C CNN
	1    3000 1450
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 6185FDE6
P 3650 1350
F 0 "#PWR?" H 3650 1200 50  0001 C CNN
F 1 "+5V" V 3665 1478 50  0000 L CNN
F 2 "" H 3650 1350 50  0001 C CNN
F 3 "" H 3650 1350 50  0001 C CNN
	1    3650 1350
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_DIP_x01 SW?
U 1 1 6186047C
P 3350 1350
F 0 "SW?" H 3350 1617 50  0000 C CNN
F 1 "SW_DIP_x01" H 3350 1526 50  0000 C CNN
F 2 "" H 3350 1350 50  0001 C CNN
F 3 "" H 3350 1350 50  0001 C CNN
	1    3350 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 3200 6750 3200
Wire Wire Line
	7050 3100 6750 3100
Wire Wire Line
	7050 3000 6750 3000
$Comp
L Connector_Generic:Conn_01x03 J?
U 1 1 61861A7F
P 7250 3500
F 0 "J?" H 7329 3542 50  0000 L CNN
F 1 "Sensor Ruido" H 7329 3451 50  0000 L CNN
F 2 "" H 7250 3500 50  0001 C CNN
F 3 "~" H 7250 3500 50  0001 C CNN
	1    7250 3500
	1    0    0    -1  
$EndComp
Text Label 6850 3400 0    50   ~ 0
VCC
Text Label 6850 3500 0    50   ~ 0
GND
Text Label 6850 3600 0    50   ~ 0
A2
Wire Wire Line
	7050 3600 6750 3600
Wire Wire Line
	7050 3500 6750 3500
Wire Wire Line
	7050 3400 6750 3400
Text Notes 6450 3800 0    50   ~ 0
Aun no esta claro que sensores usar pero aprox... esta por confirmar 
$Comp
L power:+5V #PWR?
U 1 1 61862133
P 4700 3500
F 0 "#PWR?" H 4700 3350 50  0001 C CNN
F 1 "+5V" V 4715 3628 50  0000 L CNN
F 2 "" H 4700 3500 50  0001 C CNN
F 3 "" H 4700 3500 50  0001 C CNN
	1    4700 3500
	0    -1   -1   0   
$EndComp
$EndSCHEMATC
