# dczia2018

```
 ___   ___ _____        ___ __  _ ___
|   \ / __|_  (_)__ _  |_  )  \/ ( _ )
| |) | (__ / /| / _` |  / / () | / _ \
|___/ \___/___|_\__,_| /___\__/|_\___/

 _________
| DCZ ■■ ⧻|
| □ □ □ □ |
| □ □ □ □ |
| □ □ □ □ |
|_□_□_□_□_|

```

March 2018 Update --

	Proto Dos boards are in, working, and off to Lithochasm for redistribution with the keys

Feb 8th 2018 Update --
	Dev boards have been made by Hamster. He identified an issue with the footprint of the leds, and is working on a fix.
	Clear keycaps have begun printing by Litho. Switches and LED's for a dev board test have been ordered as well.
	Software developemt has not begun. 
	Goals for Feb, get dev boards up and in the hands of folks. 
	Ideas for software features
	Laynard Design

Defcon2018 Style Guide: https://defcon.org/html/defcon-26/dc-26-theme.html


Parts Breakdown: 
* ESP32 - [Wemos Lolin ESP32 OLED Module For Arduino ESP32 OLED WiFi + Bluetooth](https://forum.arduino.cc/index.php?topic=495555.0)
* PCB
* Keyswitches - SMD RGB Type Needed (They have clear casings allowing for SMD leds to shine through.
	* Gateron Blues / Whatevers - Clear top, white bottom. Supposedly the white bottom ones have the smd cutout $0.25ea[Gateron Blue (60G) Tactile Click Switches (Pack of 10) by Mechanical Keyboards Inc](https://mechanicalkeyboards.com/shop/index.php?l=product_detail&p=1272)

* Keycaps
	* DIY 3D Printed. STL File is now in repo.
	
* Power - Lipo // AA’s? - Thinking AA's for ease of sourcing, and no need to fuss with lipo packs.

OLED Notes:
WeMos OLED 
I2C Data 5, Clock 4
[u8g2setupcpp · olikraus/u8g2 Wiki · GitHub](https://github.com/olikraus/u8g2/wiki/u8g2setupcpp#ssd1306-128x64_noname)

Constructor:  U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, 4, 5, U8X8_PIN_NONE);

#dczia
