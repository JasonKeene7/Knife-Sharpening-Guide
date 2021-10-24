EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Module:Arduino_UNO_R3 A?
U 1 1 61754E25
P 6400 4000
F 0 "A?" H 6400 5181 50  0000 C CNN
F 1 "Arduino_UNO_R3" H 6400 5090 50  0000 C CNN
F 2 "Module:Arduino_UNO_R3" H 6400 4000 50  0001 C CIN
F 3 "https://www.arduino.cc/en/Main/arduinoBoardUno" H 6400 4000 50  0001 C CNN
	1    6400 4000
	1    0    0    -1  
$EndComp
NoConn ~ 2500 3500
NoConn ~ 2500 3600
NoConn ~ 2500 3700
NoConn ~ 2500 3800
NoConn ~ 2500 3900
$Comp
L Driver_Display:CR2013-MI2120 U?
U 1 1 617575E1
P 3300 3900
F 0 "U?" H 3300 4681 50  0000 C CNN
F 1 "CR2013-MI2120" H 3300 4590 50  0000 C CNN
F 2 "Display:CR2013-MI2120" H 3300 3200 50  0001 C CNN
F 3 "http://pan.baidu.com/s/11Y990" H 2650 4400 50  0001 C CNN
	1    3300 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 4200 5900 4200
Wire Wire Line
	4100 3700 5000 3700
Wire Wire Line
	5000 3700 5000 4300
Wire Wire Line
	5000 4300 5900 4300
Wire Wire Line
	4100 3600 4900 3600
Wire Wire Line
	4900 3600 4900 4400
Wire Wire Line
	4900 4400 5900 4400
Wire Wire Line
	4100 3800 4800 3800
Wire Wire Line
	4800 3800 4800 4500
Wire Wire Line
	4800 4500 5900 4500
Wire Wire Line
	4100 3900 4700 3900
Wire Wire Line
	4700 3900 4700 4600
Wire Wire Line
	4700 4600 5900 4600
Wire Wire Line
	4100 4000 4600 4000
Wire Wire Line
	4600 4000 4600 4700
Wire Wire Line
	4600 4700 5900 4700
Wire Wire Line
	4100 4100 4200 4100
Wire Wire Line
	4200 4100 4200 2800
Wire Wire Line
	4200 2800 6500 2800
Wire Wire Line
	6500 2800 6500 3000
Wire Wire Line
	3300 3300 3300 2700
Wire Wire Line
	3300 2700 6600 2700
Wire Wire Line
	6600 2700 6600 3000
Wire Wire Line
	3300 4500 3300 5200
Wire Wire Line
	3300 5200 6300 5200
Wire Wire Line
	6300 5200 6300 5100
$Comp
L Sensor_Motion:BNO055_Breakout U?
U 1 1 61785B4E
P 8300 3100
F 0 "U?" H 8300 2881 50  0000 C CNN
F 1 "BNO055_Breakout" H 8300 2790 50  0000 C CNN
F 2 "" H 8300 3100 50  0001 C CNN
F 3 "" H 8300 3100 50  0001 C CNN
	1    8300 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8300 4400 8300 5200
Connection ~ 6300 5200
Wire Wire Line
	8300 5200 7800 5200
Wire Wire Line
	7900 4100 7800 4100
Wire Wire Line
	7800 4100 7800 5200
Connection ~ 7800 5200
Wire Wire Line
	7800 5200 6300 5200
Wire Wire Line
	7900 4000 7700 4000
Wire Wire Line
	7700 4000 7700 4800
Wire Wire Line
	6900 4800 7700 4800
Wire Wire Line
	7900 3900 7600 3900
Wire Wire Line
	7600 3900 7600 4700
Wire Wire Line
	6900 4700 7600 4700
Wire Wire Line
	8300 3500 8300 2700
Wire Wire Line
	8300 2700 6600 2700
Connection ~ 6600 2700
NoConn ~ 7900 3800
NoConn ~ 8700 3800
NoConn ~ 8700 3900
NoConn ~ 8700 4000
NoConn ~ 8700 4100
$EndSCHEMATC
