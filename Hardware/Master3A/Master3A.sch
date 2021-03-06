EESchema Schematic File Version 4
EELAYER 30 0
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
L Master3A-rescue:Master3A-rescue_TTGOv3SimGps-TTGO U3
U 1 1 61823C34
P 6300 3800
F 0 "U3" H 6325 4715 50  0000 C CNN
F 1 "TTGOv3SimGps" H 6325 4624 50  0000 C CNN
F 2 "TTGO:TTGo_sinGuia" H 6250 4150 50  0001 C CNN
F 3 "" H 6250 4150 50  0001 C CNN
	1    6300 3800
	1    0    0    -1  
$EndComp
Text Notes 5650 5000 0    50   ~ 0
VIN 5V pero funciona con 3v3\n
$Comp
L Master3A-rescue:power_GND #PWR01
U 1 1 61850E89
P 6700 3300
F 0 "#PWR01" H 6700 3050 50  0001 C CNN
F 1 "GND" V 6705 3172 50  0000 R CNN
F 2 "" H 6700 3300 50  0001 C CNN
F 3 "" H 6700 3300 50  0001 C CNN
	1    6700 3300
	0    -1   -1   0   
$EndComp
$Comp
L Master3A-rescue:power_+3V3 #PWR02
U 1 1 61850EF7
P 6700 3200
F 0 "#PWR02" H 6700 3050 50  0001 C CNN
F 1 "+3V3" V 6715 3328 50  0000 L CNN
F 2 "" H 6700 3200 50  0001 C CNN
F 3 "" H 6700 3200 50  0001 C CNN
	1    6700 3200
	0    1    1    0   
$EndComp
Wire Wire Line
	5950 4700 5500 4700
Text Label 5700 4700 0    50   ~ 0
VIN
Wire Wire Line
	5950 4000 5500 4000
Text Label 5700 4100 0    50   ~ 0
NSS
Wire Wire Line
	5950 4100 5500 4100
Text Label 5700 4000 0    50   ~ 0
SCK
Wire Wire Line
	5950 3800 5500 3800
Text Label 5700 3900 0    50   ~ 0
MISO
Wire Wire Line
	5950 3900 5500 3900
Text Label 5700 3800 0    50   ~ 0
MOSI
Wire Wire Line
	1200 1250 1450 1250
Wire Wire Line
	1200 1450 1400 1450
$Comp
L Master3A-rescue:power_GND #PWR03
U 1 1 6185EB4B
P 1400 1450
F 0 "#PWR03" H 1400 1200 50  0001 C CNN
F 1 "GND" H 1405 1277 50  0000 C CNN
F 2 "" H 1400 1450 50  0001 C CNN
F 3 "" H 1400 1450 50  0001 C CNN
	1    1400 1450
	1    0    0    -1  
$EndComp
$Comp
L Master3A-rescue:power_+5V #PWR04
U 1 1 6185FDE6
P 2050 1250
F 0 "#PWR04" H 2050 1100 50  0001 C CNN
F 1 "+5V" V 2065 1378 50  0000 L CNN
F 2 "" H 2050 1250 50  0001 C CNN
F 3 "" H 2050 1250 50  0001 C CNN
	1    2050 1250
	0    1    1    0   
$EndComp
$Comp
L Master3A-rescue:Switch_SW_DIP_x01 SW1
U 1 1 6186047C
P 1750 1250
F 0 "SW1" H 1750 1517 50  0000 C CNN
F 1 "SW_DIP_x01" H 1750 1426 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 1750 1250 50  0001 C CNN
F 3 "" H 1750 1250 50  0001 C CNN
	1    1750 1250
	1    0    0    -1  
$EndComp
Text Notes 6900 6350 0    50   ~ 0
Aun no esta claro que sensores usar pero aprox... esta por confirmar 
$Comp
L Master3A-rescue:power_+5V #PWR05
U 1 1 61862133
P 5500 4700
F 0 "#PWR05" H 5500 4550 50  0001 C CNN
F 1 "+5V" V 5515 4828 50  0000 L CNN
F 2 "" H 5500 4700 50  0001 C CNN
F 3 "" H 5500 4700 50  0001 C CNN
	1    5500 4700
	0    -1   -1   0   
$EndComp
$Comp
L Master3A-rescue:Interface_UART_MAX485E U2
U 1 1 6189674B
P 3750 6650
F 0 "U2" H 3750 7550 50  0000 C CNN
F 1 "MAX485E" H 3750 7450 50  0000 C CNN
F 2 "Package_SO:SOP-8_5.28x5.23mm_P1.27mm" H 3750 5950 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/MAX1487E-MAX491E.pdf" H 3750 6700 50  0001 C CNN
	1    3750 6650
	1    0    0    -1  
$EndComp
$Comp
L Master3A-rescue:Device_R R4
U 1 1 61896E94
P 2850 6100
F 0 "R4" H 2920 6146 50  0000 L CNN
F 1 "10k" H 2920 6055 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2780 6100 50  0001 C CNN
F 3 "~" H 2850 6100 50  0001 C CNN
	1    2850 6100
	1    0    0    -1  
$EndComp
$Comp
L Master3A-rescue:Device_R R3
U 1 1 61897974
P 2600 6100
F 0 "R3" H 2670 6146 50  0000 L CNN
F 1 "10k" H 2670 6055 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2530 6100 50  0001 C CNN
F 3 "~" H 2600 6100 50  0001 C CNN
	1    2600 6100
	1    0    0    -1  
$EndComp
$Comp
L Master3A-rescue:Device_R R2
U 1 1 618983D7
P 2350 6100
F 0 "R2" H 2420 6146 50  0000 L CNN
F 1 "10k" H 2420 6055 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2280 6100 50  0001 C CNN
F 3 "~" H 2350 6100 50  0001 C CNN
	1    2350 6100
	1    0    0    -1  
$EndComp
$Comp
L Master3A-rescue:Device_R R1
U 1 1 618983DD
P 2100 6100
F 0 "R1" H 2170 6146 50  0000 L CNN
F 1 "10k" H 2170 6055 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2030 6100 50  0001 C CNN
F 3 "~" H 2100 6100 50  0001 C CNN
	1    2100 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 6550 2100 6550
Wire Wire Line
	2100 6750 2600 6750
Wire Wire Line
	2100 6250 2100 6550
Connection ~ 2100 6550
Wire Wire Line
	2350 6250 2350 6650
Connection ~ 2350 6650
Wire Wire Line
	2100 6650 2350 6650
Wire Wire Line
	2600 6250 2600 6750
Connection ~ 2600 6750
Wire Wire Line
	2850 6250 2850 6850
Connection ~ 2850 6850
Wire Wire Line
	1700 6850 2850 6850
Wire Wire Line
	2100 5950 2350 5950
Connection ~ 2350 5950
Connection ~ 2600 5950
$Comp
L Master3A-rescue:power_+5V #PWR06
U 1 1 6189DA2E
P 2500 5850
F 0 "#PWR06" H 2500 5700 50  0001 C CNN
F 1 "+5V" H 2515 6023 50  0000 C CNN
F 2 "" H 2500 5850 50  0001 C CNN
F 3 "" H 2500 5850 50  0001 C CNN
	1    2500 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 5850 2500 5950
Connection ~ 2500 5950
$Comp
L Master3A-rescue:power_GND #PWR07
U 1 1 6189E42C
P 3750 7250
F 0 "#PWR07" H 3750 7000 50  0001 C CNN
F 1 "GND" H 3755 7077 50  0000 C CNN
F 2 "" H 3750 7250 50  0001 C CNN
F 3 "" H 3750 7250 50  0001 C CNN
	1    3750 7250
	1    0    0    -1  
$EndComp
$Comp
L Master3A-rescue:power_+5V #PWR08
U 1 1 6189E45A
P 3750 6150
F 0 "#PWR08" H 3750 6000 50  0001 C CNN
F 1 "+5V" H 3765 6323 50  0000 C CNN
F 2 "" H 3750 6150 50  0001 C CNN
F 3 "" H 3750 6150 50  0001 C CNN
	1    3750 6150
	1    0    0    -1  
$EndComp
$Comp
L Master3A-rescue:Device_R R7
U 1 1 6189EF19
P 4450 7000
F 0 "R7" H 4520 7046 50  0000 L CNN
F 1 "20k" H 4520 6955 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4380 7000 50  0001 C CNN
F 3 "~" H 4450 7000 50  0001 C CNN
	1    4450 7000
	1    0    0    -1  
$EndComp
$Comp
L Master3A-rescue:Device_R R6
U 1 1 6189EF1F
P 4450 6400
F 0 "R6" H 4520 6446 50  0000 L CNN
F 1 "20k" H 4520 6355 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4380 6400 50  0001 C CNN
F 3 "~" H 4450 6400 50  0001 C CNN
	1    4450 6400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 6550 4450 6550
Connection ~ 4450 6550
Wire Wire Line
	4150 6850 4450 6850
$Comp
L Master3A-rescue:Connector_Generic_Conn_01x02 J4
U 1 1 618A2CDF
P 5050 6650
F 0 "J4" H 5130 6642 50  0000 L CNN
F 1 "Conn_01x02" H 4850 6900 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 5050 6650 50  0001 C CNN
F 3 "~" H 5050 6650 50  0001 C CNN
	1    5050 6650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 6550 4850 6650
Wire Wire Line
	4850 6850 4850 6750
Connection ~ 4450 6850
Wire Wire Line
	4450 6200 4450 6250
$Comp
L Master3A-rescue:power_+5V #PWR09
U 1 1 618A752A
P 4450 7250
F 0 "#PWR09" H 4450 7100 50  0001 C CNN
F 1 "+5V" H 4465 7423 50  0000 C CNN
F 2 "" H 4450 7250 50  0001 C CNN
F 3 "" H 4450 7250 50  0001 C CNN
	1    4450 7250
	-1   0    0    1   
$EndComp
Wire Wire Line
	4450 7150 4450 7250
$Comp
L Master3A-rescue:power_GND #PWR010
U 1 1 618AC87A
P 4450 6200
F 0 "#PWR010" H 4450 5950 50  0001 C CNN
F 1 "GND" H 4455 6027 50  0000 C CNN
F 2 "" H 4450 6200 50  0001 C CNN
F 3 "" H 4450 6200 50  0001 C CNN
	1    4450 6200
	-1   0    0    1   
$EndComp
$Comp
L Master3A-rescue:Device_R R8
U 1 1 618AF8DF
P 5300 6700
F 0 "R8" H 5230 6654 50  0000 R CNN
F 1 "120" H 5230 6745 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5230 6700 50  0001 C CNN
F 3 "~" H 5300 6700 50  0001 C CNN
	1    5300 6700
	-1   0    0    1   
$EndComp
Connection ~ 4850 6550
Connection ~ 4850 6850
$Comp
L Master3A-rescue:Device_R R5
U 1 1 618B51B7
P 4100 1100
F 0 "R5" V 3893 1100 50  0000 C CNN
F 1 "1k" V 3984 1100 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4030 1100 50  0001 C CNN
F 3 "~" H 4100 1100 50  0001 C CNN
	1    4100 1100
	0    1    1    0   
$EndComp
$Comp
L Master3A-rescue:Device_LED D1
U 1 1 618B5246
P 4500 1100
F 0 "D1" H 4492 845 50  0000 C CNN
F 1 "LED" H 4492 936 50  0000 C CNN
F 2 "Diode_SMD:D_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4500 1100 50  0001 C CNN
F 3 "~" H 4500 1100 50  0001 C CNN
	1    4500 1100
	-1   0    0    1   
$EndComp
$Comp
L Master3A-rescue:Device_C C3
U 1 1 618B52D3
P 4300 1850
F 0 "C3" V 4048 1850 50  0000 C CNN
F 1 "10uF" V 4139 1850 50  0000 C CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 4338 1700 50  0001 C CNN
F 3 "~" H 4300 1850 50  0001 C CNN
	1    4300 1850
	0    1    1    0   
$EndComp
$Comp
L Master3A-rescue:Device_C C2
U 1 1 618B6DA3
P 4300 1450
F 0 "C2" V 4048 1450 50  0000 C CNN
F 1 "0.1uF" V 4139 1450 50  0000 C CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 4338 1300 50  0001 C CNN
F 3 "~" H 4300 1450 50  0001 C CNN
	1    4300 1450
	0    1    1    0   
$EndComp
Wire Wire Line
	4650 1100 4650 1450
Wire Wire Line
	4450 1450 4650 1450
Wire Wire Line
	4650 1850 4450 1850
Connection ~ 4650 1450
Wire Wire Line
	3950 1100 3950 1450
Wire Wire Line
	3650 1450 3950 1450
Wire Wire Line
	3950 1850 4150 1850
Connection ~ 3950 1450
$Comp
L Master3A-rescue:power_GND #PWR011
U 1 1 618C2886
P 5100 1450
F 0 "#PWR011" H 5100 1200 50  0001 C CNN
F 1 "GND" V 5105 1322 50  0000 R CNN
F 2 "" H 5100 1450 50  0001 C CNN
F 3 "" H 5100 1450 50  0001 C CNN
	1    5100 1450
	0    -1   -1   0   
$EndComp
$Comp
L Master3A-rescue:Connector_Generic_Conn_01x02 J3
U 1 1 618C9F29
P 4250 800
F 0 "J3" H 4330 792 50  0000 L CNN
F 1 "Conn_01x02" H 4050 1050 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4250 800 50  0001 C CNN
F 3 "~" H 4250 800 50  0001 C CNN
	1    4250 800 
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4250 1100 4250 1000
Wire Wire Line
	4350 1100 4350 1000
Text Notes 2900 5500 0    50   ~ 0
MODBUS COMMUNICATION
Wire Wire Line
	10200 5900 9900 5900
Wire Wire Line
	10200 6000 9900 6000
Wire Wire Line
	10200 6100 9900 6100
Wire Wire Line
	10200 6200 9900 6200
Text Label 10000 5900 0    50   ~ 0
5V
Text Label 10000 6000 0    50   ~ 0
GND
$Comp
L Master3A-rescue:power_+5V #PWR012
U 1 1 618DCE93
P 9900 5900
F 0 "#PWR012" H 9900 5750 50  0001 C CNN
F 1 "+5V" H 9915 6073 50  0000 C CNN
F 2 "" H 9900 5900 50  0001 C CNN
F 3 "" H 9900 5900 50  0001 C CNN
	1    9900 5900
	0    -1   -1   0   
$EndComp
$Comp
L Master3A-rescue:power_GND #PWR013
U 1 1 618DCE99
P 9900 6000
F 0 "#PWR013" H 9900 5750 50  0001 C CNN
F 1 "GND" V 9905 5872 50  0000 R CNN
F 2 "" H 9900 6000 50  0001 C CNN
F 3 "" H 9900 6000 50  0001 C CNN
	1    9900 6000
	0    1    1    0   
$EndComp
$Comp
L Master3A-rescue:Connector_Generic_Conn_01x05 J8
U 1 1 618DEC0E
P 10400 6000
F 0 "J8" H 10479 6042 50  0000 L CNN
F 1 "SENSOR TEMP HUM" H 10479 5951 50  0000 L CNN
F 2 "Connector_JST:JST_PH_B5B-PH-K_1x05_P2.00mm_Vertical" H 10400 6000 50  0001 C CNN
F 3 "~" H 10400 6000 50  0001 C CNN
	1    10400 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	10200 5800 9900 5800
Text Label 10000 5800 0    50   ~ 0
3V3
$Comp
L Master3A-rescue:power_+3V3 #PWR014
U 1 1 618E647E
P 9900 5800
F 0 "#PWR014" H 9900 5650 50  0001 C CNN
F 1 "+3V3" H 9915 5973 50  0000 C CNN
F 2 "" H 9900 5800 50  0001 C CNN
F 3 "" H 9900 5800 50  0001 C CNN
	1    9900 5800
	1    0    0    -1  
$EndComp
$Comp
L Master3A-rescue:power_+5V #PWR015
U 1 1 618BCC12
P 3650 1450
F 0 "#PWR015" H 3650 1300 50  0001 C CNN
F 1 "+5V" V 3665 1578 50  0000 L CNN
F 2 "" H 3650 1450 50  0001 C CNN
F 3 "" H 3650 1450 50  0001 C CNN
	1    3650 1450
	0    -1   -1   0   
$EndComp
Text Notes 10600 6300 0    50   ~ 0
CONFIRMAR???\n
Text Label 5150 6550 0    50   ~ 0
B
Text Label 5150 6850 0    50   ~ 0
A
Wire Wire Line
	2100 6650 2100 6700
Text Label 1700 6550 0    50   ~ 0
RX_MODBUS
Text Label 1700 6850 0    50   ~ 0
TX_MODBUS
Connection ~ 2100 6700
Wire Wire Line
	1700 6700 2100 6700
Text Label 1700 6700 0    50   ~ 0
GPIOXX
Text Notes 500  6700 0    50   ~ 0
TODO:CONCRETAR PIN Y PINES\n
$Comp
L Master3A-rescue:Connector_Generic_Conn_01x03 J1
U 1 1 61917DCB
P 1000 1350
F 0 "J1" H 920 1025 50  0000 C CNN
F 1 "Conn_01x03" H 920 1116 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 1000 1350 50  0001 C CNN
F 3 "~" H 1000 1350 50  0001 C CNN
	1    1000 1350
	-1   0    0    1   
$EndComp
Wire Wire Line
	1200 1350 1500 1350
Text Notes 750  1950 0    50   ~ 0
TODO: PINBATT TIENE QUE SER ANALOGICO\nESTE PIN MEDIR?? EL ESTADO DE LA BATERIA\n\n
Wire Wire Line
	6700 4400 7250 4400
Text Label 6800 4400 0    50   ~ 0
GPIO14
Wire Wire Line
	6700 4200 7250 4200
Text Label 6800 4200 0    50   ~ 0
GPIO2
Text Notes 350  8350 0    50   ~ 0
https://es.aliexpress.com/item/1005001359657779.html?src=google%2Chttps%3A%2F%2Fwww.aliexpress.com%2Fitem%2F1005001359657779.html%3F_randl_currency%3DEUR&src=google&src=google&albch=shopping&acnt=439-079-4345&slnk=&plac=&mtctp=&albbt=Google_7_shopping&gclsrc=aw.ds&albagn=888888&ds_e_adid=438858099979&ds_e_matchtype=&ds_e_device=c&ds_e_network=u&ds_e_product_group_id=883147840299&ds_e_product_id=es1005001359657779&ds_e_product_merchant_id=101171402&ds_e_product_country=ES&ds_e_product_language=es&ds_e_product_channel=online&ds_e_product_store_id=&ds_url_v=2&ds_dest_url=https%3A%2F%2Fs.click.aliexpress.com%2Fdeep_link.htm%3Faff_short_key%3DUneMJZVf&albcp=10191226958&albag=102259630456&isSmbAutoCall=false&needSmbHouyi=false&gclid=Cj0KCQiAsqOMBhDFARIsAFBTN3f0AL_SVhrWTl9d-SthGvmfuoq4bwtWtjJmG87wOl-F1FKmeiQRbW8aAmVfEALw_wcB&aff_fcid=f5d504764dfc419191d0ab642615e400-1636397437392-02716-UneMJZVf&aff_fsk=UneMJZVf&aff_platform=aaf&sk=UneMJZVf&aff_trace_key=f5d504764dfc419191d0ab642615e400-1636397437392-02716-UneMJZVf&terminal_id=947cb51e9fbf47ec9faaf93292b05dc2
$Comp
L Master3A-rescue:Connector_Generic_Conn_01x04 J2
U 1 1 618E447C
P 3200 7500
F 0 "J2" V 3073 7680 50  0000 L CNN
F 1 "Conn_01x04" V 3164 7680 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 3200 7500 50  0001 C CNN
F 3 "~" H 3200 7500 50  0001 C CNN
	1    3200 7500
	0    1    1    0   
$EndComp
Wire Wire Line
	3300 6850 3300 7300
Connection ~ 3300 6850
Wire Wire Line
	3200 6750 3200 7300
Connection ~ 3200 6750
Wire Wire Line
	3100 6650 3100 7300
Connection ~ 3100 6650
Wire Wire Line
	3000 6550 3000 7300
Connection ~ 3000 6550
Text Notes 7800 3600 0    50   ~ 0
RST Lora\n
Text Notes 7600 3400 0    50   ~ 0
DID0 Lora\n
Wire Wire Line
	5500 3700 5950 3700
Wire Wire Line
	5950 3600 5500 3600
$Comp
L Master3A-rescue:Transistor_FET_BSS138 Q2
U 1 1 6190AC29
P 10450 1400
F 0 "Q2" H 10655 1446 50  0000 L CNN
F 1 "BSS138" V 10100 1300 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 10650 1325 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/BS/BSS138.pdf" H 10450 1400 50  0001 L CNN
	1    10450 1400
	0    1    1    0   
$EndComp
$Comp
L Master3A-rescue:Device_R R12
U 1 1 6190E164
P 10800 1150
F 0 "R12" H 10870 1196 50  0000 L CNN
F 1 "10k" H 10870 1105 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 10730 1150 50  0001 C CNN
F 3 "~" H 10800 1150 50  0001 C CNN
	1    10800 1150
	1    0    0    -1  
$EndComp
$Comp
L Master3A-rescue:Device_R R11
U 1 1 6190E1DE
P 10150 1150
F 0 "R11" H 10220 1196 50  0000 L CNN
F 1 "10k" H 10220 1105 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 10080 1150 50  0001 C CNN
F 3 "~" H 10150 1150 50  0001 C CNN
	1    10150 1150
	1    0    0    -1  
$EndComp
$Comp
L Master3A-rescue:Jumper_SolderJumper_2_Bridged JP2
U 1 1 619111F3
P 10450 1750
F 0 "JP2" H 11000 1650 50  0000 C CNN
F 1 "SolderJumper_2_Bridged" H 10450 1650 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 10450 1750 50  0001 C CNN
F 3 "~" H 10450 1750 50  0001 C CNN
	1    10450 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	10800 1000 10800 850 
Wire Wire Line
	10150 850  10150 950 
Wire Wire Line
	10150 1300 10150 1500
Wire Wire Line
	9900 1500 10150 1500
Wire Wire Line
	10650 1500 10800 1500
Wire Wire Line
	10800 1300 10800 1500
Wire Wire Line
	10450 1200 10450 950 
Wire Wire Line
	10450 950  10150 950 
Connection ~ 10150 950 
Connection ~ 10800 1500
Connection ~ 10150 1500
Wire Wire Line
	10150 1750 10300 1750
Wire Wire Line
	10800 1750 10600 1750
Text Label 10850 1500 0    50   ~ 0
SCL_5V
Text Label 9900 1500 0    50   ~ 0
SCL_3V3
$Comp
L Master3A-rescue:power_+3V3 #PWR016
U 1 1 6192EAA1
P 10150 850
F 0 "#PWR016" H 10150 700 50  0001 C CNN
F 1 "+3V3" V 10165 978 50  0000 L CNN
F 2 "" H 10150 850 50  0001 C CNN
F 3 "" H 10150 850 50  0001 C CNN
	1    10150 850 
	1    0    0    -1  
$EndComp
$Comp
L Master3A-rescue:power_+5V #PWR017
U 1 1 619325BA
P 10800 850
F 0 "#PWR017" H 10800 700 50  0001 C CNN
F 1 "+5V" V 10815 978 50  0000 L CNN
F 2 "" H 10800 850 50  0001 C CNN
F 3 "" H 10800 850 50  0001 C CNN
	1    10800 850 
	1    0    0    -1  
$EndComp
$Comp
L Master3A-rescue:Transistor_FET_BSS138 Q1
U 1 1 61939A1B
P 9100 1400
F 0 "Q1" H 9305 1446 50  0000 L CNN
F 1 "BSS138" V 8750 1300 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 9300 1325 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/BS/BSS138.pdf" H 9100 1400 50  0001 L CNN
	1    9100 1400
	0    1    1    0   
$EndComp
$Comp
L Master3A-rescue:Device_R R10
U 1 1 61939A21
P 9450 1150
F 0 "R10" H 9520 1196 50  0000 L CNN
F 1 "10k" H 9520 1105 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 9380 1150 50  0001 C CNN
F 3 "~" H 9450 1150 50  0001 C CNN
	1    9450 1150
	1    0    0    -1  
$EndComp
$Comp
L Master3A-rescue:Device_R R9
U 1 1 61939A27
P 8800 1150
F 0 "R9" H 8870 1196 50  0000 L CNN
F 1 "10k" H 8870 1105 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 8730 1150 50  0001 C CNN
F 3 "~" H 8800 1150 50  0001 C CNN
	1    8800 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9450 1000 9450 850 
Wire Wire Line
	8800 850  8800 950 
Wire Wire Line
	8800 1300 8800 1500
Wire Wire Line
	8550 1500 8800 1500
Wire Wire Line
	9300 1500 9450 1500
Wire Wire Line
	9450 1300 9450 1500
Wire Wire Line
	9100 1200 9100 950 
Wire Wire Line
	9100 950  8800 950 
Connection ~ 8800 950 
Connection ~ 9450 1500
Connection ~ 8800 1500
Wire Wire Line
	8800 1750 8950 1750
Wire Wire Line
	9450 1750 9250 1750
Text Label 9500 1500 0    50   ~ 0
SDA_5V
Text Label 8550 1500 0    50   ~ 0
SDA_3V3
$Comp
L Master3A-rescue:power_+3V3 #PWR018
U 1 1 61939A47
P 8800 850
F 0 "#PWR018" H 8800 700 50  0001 C CNN
F 1 "+3V3" V 8815 978 50  0000 L CNN
F 2 "" H 8800 850 50  0001 C CNN
F 3 "" H 8800 850 50  0001 C CNN
	1    8800 850 
	1    0    0    -1  
$EndComp
$Comp
L Master3A-rescue:power_+5V #PWR019
U 1 1 61939A4D
P 9450 850
F 0 "#PWR019" H 9450 700 50  0001 C CNN
F 1 "+5V" V 9465 978 50  0000 L CNN
F 2 "" H 9450 850 50  0001 C CNN
F 3 "" H 9450 850 50  0001 C CNN
	1    9450 850 
	1    0    0    -1  
$EndComp
Wire Notes Line
	6350 5150 6350 7850
Wire Notes Line
	450  2100 2900 2100
Wire Notes Line
	2900 2100 2900 2750
Wire Notes Line
	2900 2750 4000 2750
Wire Notes Line
	4000 2750 4000 5150
Wire Notes Line
	450  5150 11250 5150
Wire Notes Line
	8250 450  8250 2350
Wire Notes Line
	8250 2350 11200 2350
Text Label 2650 3600 0    50   ~ 0
GPIO2
Wire Wire Line
	2550 3600 3100 3600
Wire Wire Line
	1800 4450 1900 4450
Connection ~ 2000 4450
Connection ~ 1900 4450
$Comp
L Master3A-rescue:power_GND #PWR020
U 1 1 61927547
P 1350 3050
F 0 "#PWR020" H 1350 2800 50  0001 C CNN
F 1 "GND" V 1355 2922 50  0000 R CNN
F 2 "" H 1350 3050 50  0001 C CNN
F 3 "" H 1350 3050 50  0001 C CNN
	1    1350 3050
	1    0    0    -1  
$EndComp
Text Label 1000 4150 0    50   ~ 0
GPIO14
Wire Wire Line
	900  4150 1450 4150
Text Label 1000 3650 0    50   ~ 0
NSS
Text Label 1000 3950 0    50   ~ 0
SCK
Text Label 1000 3750 0    50   ~ 0
MOSI
Text Label 1000 3850 0    50   ~ 0
MISO
Wire Wire Line
	900  3650 1450 3650
Wire Wire Line
	900  3950 1450 3950
Wire Wire Line
	900  3750 1450 3750
Wire Wire Line
	900  3850 1450 3850
$Comp
L Master3A-rescue:Master3A-rescue_RFM95HW-RFMLIBGIT U1
U 1 1 61902C65
P 2000 3600
F 0 "U1" H 2000 4214 40  0000 C CNN
F 1 "RFM95HW" H 2000 4138 40  0000 C CNN
F 2 "RF_Module:HOPERF_RFM9XW_SMD" H 2000 3600 30  0001 C CIN
F 3 "https://cdn-learn.adafruit.com/assets/assets/000/031/659/original/RFM95_96_97_98W.pdf?1460518717" H 1950 4600 60  0000 C CNN
	1    2000 3600
	1    0    0    -1  
$EndComp
$Comp
L Master3A-rescue:Device_Antenna_Chip AE1
U 1 1 61937A14
P 1250 2950
F 0 "AE1" H 1429 3078 50  0000 L CNN
F 1 "Antenna_Chip" H 1429 2987 50  0000 L CNN
F 2 "Connector_Coaxial:U.FL_Hirose_U.FL-R-SMT-1_Vertical" H 1150 3125 50  0001 C CNN
F 3 "~" H 1150 3125 50  0001 C CNN
	1    1250 2950
	1    0    0    -1  
$EndComp
$Comp
L Master3A-rescue:Device_C C1
U 1 1 6193299A
P 1900 4600
F 0 "C1" H 2015 4646 50  0000 L CNN
F 1 "100nf" H 2015 4555 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 1938 4450 50  0001 C CNN
F 3 "~" H 1900 4600 50  0001 C CNN
	1    1900 4600
	1    0    0    -1  
$EndComp
$Comp
L Master3A-rescue:power_GND #PWR021
U 1 1 6192C9A5
P 1800 4450
F 0 "#PWR021" H 1800 4200 50  0001 C CNN
F 1 "GND" V 1805 4322 50  0000 R CNN
F 2 "" H 1800 4450 50  0001 C CNN
F 3 "" H 1800 4450 50  0001 C CNN
	1    1800 4450
	0    1    1    0   
$EndComp
$Comp
L Master3A-rescue:power_+3V3 #PWR022
U 1 1 61853076
P 2000 3250
F 0 "#PWR022" H 2000 3100 50  0001 C CNN
F 1 "+3V3" V 2015 3378 50  0000 L CNN
F 2 "" H 2000 3250 50  0001 C CNN
F 3 "" H 2000 3250 50  0001 C CNN
	1    2000 3250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2000 3250 3200 3250
Wire Wire Line
	3200 3250 3200 4750
Wire Wire Line
	3200 4750 1900 4750
Connection ~ 2000 3250
Wire Wire Line
	7250 5700 6950 5700
Wire Wire Line
	7250 5800 6950 5800
Wire Wire Line
	7250 5900 6950 5900
Wire Wire Line
	7250 6000 6950 6000
Text Label 7050 5700 0    50   ~ 0
5V
Text Label 7050 5800 0    50   ~ 0
GND
Text Label 6950 5900 0    50   ~ 0
B
Text Label 6950 6000 0    50   ~ 0
A
$Comp
L Master3A-rescue:power_+5V #PWR023
U 1 1 6196BDDD
P 6950 5700
F 0 "#PWR023" H 6950 5550 50  0001 C CNN
F 1 "+5V" H 6965 5873 50  0000 C CNN
F 2 "" H 6950 5700 50  0001 C CNN
F 3 "" H 6950 5700 50  0001 C CNN
	1    6950 5700
	0    -1   -1   0   
$EndComp
$Comp
L Master3A-rescue:power_GND #PWR024
U 1 1 6196BDE3
P 6950 5800
F 0 "#PWR024" H 6950 5550 50  0001 C CNN
F 1 "GND" V 6955 5672 50  0000 R CNN
F 2 "" H 6950 5800 50  0001 C CNN
F 3 "" H 6950 5800 50  0001 C CNN
	1    6950 5800
	0    1    1    0   
$EndComp
$Comp
L Master3A-rescue:Connector_Generic_Conn_01x05 J6
U 1 1 6198D799
P 9050 5900
F 0 "J6" H 9130 5942 50  0000 L CNN
F 1 "sensorRuido" H 9130 5851 50  0000 L CNN
F 2 "Connector_JST:JST_PH_B5B-PH-K_1x05_P2.00mm_Vertical" H 9050 5900 50  0001 C CNN
F 3 "~" H 9050 5900 50  0001 C CNN
	1    9050 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	8850 5700 8550 5700
Text Label 8650 5700 0    50   ~ 0
3V3
$Comp
L Master3A-rescue:power_+3V3 #PWR025
U 1 1 6198D7A1
P 8550 5700
F 0 "#PWR025" H 8550 5550 50  0001 C CNN
F 1 "+3V3" H 8565 5873 50  0000 C CNN
F 2 "" H 8550 5700 50  0001 C CNN
F 3 "" H 8550 5700 50  0001 C CNN
	1    8550 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	8850 5800 8550 5800
Wire Wire Line
	8850 5900 8550 5900
Wire Wire Line
	8850 6000 8550 6000
Wire Wire Line
	8850 6100 8550 6100
Text Label 8650 5800 0    50   ~ 0
5V
Text Label 8650 5900 0    50   ~ 0
GND
Text Label 8550 6000 0    50   ~ 0
B
Text Label 8550 6100 0    50   ~ 0
A
$Comp
L Master3A-rescue:power_+5V #PWR026
U 1 1 6198D7AF
P 8550 5800
F 0 "#PWR026" H 8550 5650 50  0001 C CNN
F 1 "+5V" H 8565 5973 50  0000 C CNN
F 2 "" H 8550 5800 50  0001 C CNN
F 3 "" H 8550 5800 50  0001 C CNN
	1    8550 5800
	0    -1   -1   0   
$EndComp
$Comp
L Master3A-rescue:power_GND #PWR027
U 1 1 6198D7B5
P 8550 5900
F 0 "#PWR027" H 8550 5650 50  0001 C CNN
F 1 "GND" V 8555 5772 50  0000 R CNN
F 2 "" H 8550 5900 50  0001 C CNN
F 3 "" H 8550 5900 50  0001 C CNN
	1    8550 5900
	0    1    1    0   
$EndComp
Text Notes 8600 3450 0    50   ~ 0
FALTA DEFINIR RX Y TX MODBUS\nTAMBIEN ver un pinpara pin bat
Wire Wire Line
	1500 1350 1500 1500
Wire Wire Line
	1500 1500 2150 1500
$Comp
L Master3A-rescue:Device_R R13
U 1 1 619A0C5E
P 2300 1500
F 0 "R13" V 2093 1500 50  0000 C CNN
F 1 "1k" V 2184 1500 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2230 1500 50  0001 C CNN
F 3 "~" H 2300 1500 50  0001 C CNN
	1    2300 1500
	0    1    1    0   
$EndComp
$Comp
L Master3A-rescue:Device_R R14
U 1 1 619A0D59
P 2650 1500
F 0 "R14" V 2443 1500 50  0000 C CNN
F 1 "1k7" V 2534 1500 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2580 1500 50  0001 C CNN
F 3 "~" H 2650 1500 50  0001 C CNN
	1    2650 1500
	0    1    1    0   
$EndComp
Wire Wire Line
	2450 1500 2500 1500
$Comp
L Master3A-rescue:power_GND #PWR028
U 1 1 619AAB62
P 3000 1500
F 0 "#PWR028" H 3000 1250 50  0001 C CNN
F 1 "GND" V 3005 1372 50  0000 R CNN
F 2 "" H 3000 1500 50  0001 C CNN
F 3 "" H 3000 1500 50  0001 C CNN
	1    3000 1500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2800 1500 3000 1500
Text Label 2450 1750 0    50   ~ 0
PIN_BATT
Wire Wire Line
	2450 1500 2450 1750
Connection ~ 2450 1500
Text Label 9900 6100 0    50   ~ 0
SDA_5V
Text Label 9900 6200 0    50   ~ 0
SCL_5V
Text Label 5500 3700 0    50   ~ 0
SDA_3V3
Text Label 5500 3600 0    50   ~ 0
SCL_3V3
NoConn ~ 6700 3900
NoConn ~ 6700 4000
Wire Wire Line
	6700 4300 7250 4300
Wire Wire Line
	6700 4500 7250 4500
Text Label 6800 4300 0    50   ~ 0
RX_MODBUS
Text Label 6800 4500 0    50   ~ 0
TX_MODBUS
$Comp
L Master3A-rescue:Connector_Generic_Conn_01x05 J10
U 1 1 619A8591
P 7000 3600
F 0 "J10" H 7080 3642 50  0000 L CNN
F 1 "Conn_01x05" H 7080 3551 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x05_P2.54mm_Vertical" H 7000 3600 50  0001 C CNN
F 3 "~" H 7000 3600 50  0001 C CNN
	1    7000 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 3400 6800 3400
Wire Wire Line
	6700 3500 6800 3500
Wire Wire Line
	6700 3600 6800 3600
Wire Wire Line
	6700 3700 6800 3700
Wire Wire Line
	6800 3800 6700 3800
$Comp
L Master3A-rescue:Connector_Generic_Conn_01x05 J9
U 1 1 619C63D3
P 5600 4400
F 0 "J9" H 5518 3975 50  0000 C CNN
F 1 "Conn_01x05" H 5518 4066 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x05_P2.54mm_Vertical" H 5600 4400 50  0001 C CNN
F 3 "~" H 5600 4400 50  0001 C CNN
	1    5600 4400
	-1   0    0    1   
$EndComp
Wire Wire Line
	5950 4200 5800 4200
Wire Wire Line
	5950 4300 5800 4300
Wire Wire Line
	5950 4400 5800 4400
Wire Wire Line
	5950 4500 5800 4500
Wire Wire Line
	5800 4600 5950 4600
$Comp
L Master3A-rescue:Connector_Generic_Conn_01x04 J11
U 1 1 6199AA12
P 5150 7450
F 0 "J11" V 5023 7630 50  0000 L CNN
F 1 "Conn_01x04" V 5114 7630 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 5150 7450 50  0001 C CNN
F 3 "~" H 5150 7450 50  0001 C CNN
	1    5150 7450
	0    1    1    0   
$EndComp
Wire Wire Line
	5050 6850 5050 7250
Connection ~ 5050 6850
Wire Wire Line
	5250 7250 5250 7150
$Comp
L Master3A-rescue:power_+5V #PWR029
U 1 1 619B5FF2
P 5250 7150
F 0 "#PWR029" H 5250 7000 50  0001 C CNN
F 1 "+5V" H 5265 7323 50  0000 C CNN
F 2 "" H 5250 7150 50  0001 C CNN
F 3 "" H 5250 7150 50  0001 C CNN
	1    5250 7150
	1    0    0    -1  
$EndComp
$Comp
L Master3A-rescue:power_GND #PWR030
U 1 1 619CA355
P 4950 7250
F 0 "#PWR030" H 4950 7000 50  0001 C CNN
F 1 "GND" H 4955 7077 50  0000 C CNN
F 2 "" H 4950 7250 50  0001 C CNN
F 3 "" H 4950 7250 50  0001 C CNN
	1    4950 7250
	-1   0    0    1   
$EndComp
Wire Wire Line
	1150 3050 1150 3450
Wire Wire Line
	1150 3450 1450 3450
Wire Wire Line
	5150 7250 5150 7000
Text Label 5150 7000 0    50   ~ 0
B
$Comp
L Master3A-rescue:Jumper_SolderJumper_2_Bridged JP1
U 1 1 61939A2D
P 9100 1750
F 0 "JP1" H 9650 1650 50  0000 C CNN
F 1 "SolderJumper_2_Bridged" H 9100 1650 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 9100 1750 50  0001 C CNN
F 3 "~" H 9100 1750 50  0001 C CNN
	1    9100 1750
	1    0    0    -1  
$EndComp
$Comp
L Master3A-rescue:Mechanical_MountingHole H1
U 1 1 61A7445F
P 10500 4250
F 0 "H1" H 10600 4296 50  0000 L CNN
F 1 "MountingHole" H 10600 4205 50  0000 L CNN
F 2 "Logo:GesinenLogo" H 10500 4250 50  0001 C CNN
F 3 "~" H 10500 4250 50  0001 C CNN
	1    10500 4250
	1    0    0    -1  
$EndComp
$Comp
L Master3A-rescue:Mechanical_MountingHole H3
U 1 1 61996CBA
P 10550 3300
F 0 "H3" H 10650 3346 50  0000 L CNN
F 1 "MountingHole" H 10650 3255 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 10550 3300 50  0001 C CNN
F 3 "~" H 10550 3300 50  0001 C CNN
	1    10550 3300
	1    0    0    -1  
$EndComp
$Comp
L Master3A-rescue:Mechanical_MountingHole H4
U 1 1 619B7B95
P 10550 3650
F 0 "H4" H 10650 3696 50  0000 L CNN
F 1 "MountingHole" H 10650 3605 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 10550 3650 50  0001 C CNN
F 3 "~" H 10550 3650 50  0001 C CNN
	1    10550 3650
	1    0    0    -1  
$EndComp
$Comp
L Master3A-rescue:Mechanical_MountingHole H2
U 1 1 619BE45A
P 10500 3950
F 0 "H2" H 10600 3996 50  0000 L CNN
F 1 "MountingHole" H 10600 3905 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 10500 3950 50  0001 C CNN
F 3 "~" H 10500 3950 50  0001 C CNN
	1    10500 3950
	1    0    0    -1  
$EndComp
$Comp
L Master3A-rescue:Connector_Generic_Conn_01x04 J5
U 1 1 619914BD
P 7450 5800
F 0 "J5" H 7529 5792 50  0000 L CNN
F 1 "SensorSuelo" H 7529 5701 50  0000 L CNN
F 2 "TTGo:TerminalBlock_bornier-4_P5.08mm" H 7450 5800 50  0001 C CNN
F 3 "~" H 7450 5800 50  0001 C CNN
	1    7450 5800
	1    0    0    -1  
$EndComp
$Comp
L Master3A-rescue:Connector_Generic_Conn_01x05 J7
U 1 1 619B93F8
P 8800 4700
F 0 "J7" H 8880 4742 50  0000 L CNN
F 1 "MasterSlaves" H 8880 4651 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x05_P2.54mm_Vertical" H 8800 4700 50  0001 C CNN
F 3 "~" H 8800 4700 50  0001 C CNN
	1    8800 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	8600 4800 8300 4800
Wire Wire Line
	8600 4900 8300 4900
Text Label 8450 4900 0    50   ~ 0
5V
Text Label 8450 4800 0    50   ~ 0
GND
$Comp
L Master3A-rescue:power_GND #PWR031
U 1 1 619B9460
P 8300 4800
F 0 "#PWR031" H 8300 4550 50  0001 C CNN
F 1 "GND" V 8305 4672 50  0000 R CNN
F 2 "" H 8300 4800 50  0001 C CNN
F 3 "" H 8300 4800 50  0001 C CNN
	1    8300 4800
	0    1    1    0   
$EndComp
Text Notes 7850 4600 0    50   ~ 0
RST Lora\n
Wire Wire Line
	8600 4600 8300 4600
Wire Wire Line
	8600 4700 8300 4700
Text Label 8300 4600 0    50   ~ 0
SDA_5V
Text Label 8300 4700 0    50   ~ 0
SCL_5V
$Comp
L Master3A-rescue:power_+5V #PWR032
U 1 1 619B9556
P 8300 4900
F 0 "#PWR032" H 8300 4750 50  0001 C CNN
F 1 "+5V" H 8315 5073 50  0000 C CNN
F 2 "" H 8300 4900 50  0001 C CNN
F 3 "" H 8300 4900 50  0001 C CNN
	1    8300 4900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2100 6550 3000 6550
Wire Wire Line
	2350 6650 3100 6650
Wire Wire Line
	2600 6750 3200 6750
Wire Wire Line
	2850 6850 3300 6850
Wire Wire Line
	2350 5950 2500 5950
Wire Wire Line
	2600 5950 2850 5950
Wire Wire Line
	2500 5950 2600 5950
Wire Wire Line
	4450 6550 4850 6550
Wire Wire Line
	4450 6850 4850 6850
Wire Wire Line
	4850 6550 5300 6550
Wire Wire Line
	4850 6850 5050 6850
Wire Wire Line
	4650 1450 4650 1850
Wire Wire Line
	4650 1450 5100 1450
Wire Wire Line
	3950 1450 3950 1850
Wire Wire Line
	3950 1450 4150 1450
Wire Wire Line
	2100 6700 2100 6750
Wire Wire Line
	3300 6850 3350 6850
Wire Wire Line
	3200 6750 3350 6750
Wire Wire Line
	3100 6650 3350 6650
Wire Wire Line
	3000 6550 3350 6550
Wire Wire Line
	10150 950  10150 1000
Wire Wire Line
	10800 1500 11050 1500
Wire Wire Line
	10800 1500 10800 1750
Wire Wire Line
	10150 1500 10150 1750
Wire Wire Line
	10150 1500 10250 1500
Wire Wire Line
	8800 950  8800 1000
Wire Wire Line
	9450 1500 9700 1500
Wire Wire Line
	9450 1500 9450 1750
Wire Wire Line
	8800 1500 8800 1750
Wire Wire Line
	8800 1500 8900 1500
Wire Wire Line
	2000 4450 2100 4450
Wire Wire Line
	1900 4450 2000 4450
Wire Wire Line
	5050 6850 5300 6850
Text Label 8450 4500 0    50   ~ 0
3V3
Wire Wire Line
	8600 4500 8300 4500
$EndSCHEMATC
