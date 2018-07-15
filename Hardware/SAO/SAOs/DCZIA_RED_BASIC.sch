EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:badgelife_shitty_connector
EELAYER 25 0
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
L Badgelife_shitty_connector X1
U 1 1 5B4A8073
P 6850 3250
F 0 "X1" H 6950 3050 60  0000 C CNN
F 1 "Badgelife_shitty_connector" H 6850 3650 60  0000 C CNN
F 2 "" H 6850 3250 60  0001 C CNN
F 3 "" H 6850 3250 60  0001 C CNN
	1    6850 3250
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 5B4A80D2
P 5650 3250
F 0 "D1" H 5650 3350 50  0000 C CNN
F 1 "LED" H 5650 3150 50  0000 C CNN
F 2 "" H 5650 3250 50  0001 C CNN
F 3 "" H 5650 3250 50  0001 C CNN
	1    5650 3250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5650 3100 6500 3100
Wire Wire Line
	6500 3100 6500 3150
Wire Wire Line
	5650 3400 6500 3400
Wire Wire Line
	6500 3400 6500 3350
NoConn ~ 7400 3150
NoConn ~ 7400 3350
$EndSCHEMATC
