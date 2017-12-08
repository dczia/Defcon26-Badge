# dczia2018

```
 ___   ___ _____        ___ __  _ ___
|   \ / __|_  (_)__ _  |_  )  \/ ( _ )
| |) | (__ / /| / _` |  / / () | / _ \
|___/ \___/___|_\__,_| /___\__/|_\___/
```

Everything is awesome!

Defcon2018 Style Guide: https://defcon.org/html/defcon-26/dc-26-theme.html

Microcontroller:
ESP32

Dev Board So Far: [Wemos Lolin ESP32 OLED Module For Arduino ESP32 OLED WiFi + Bluetooth](https://forum.arduino.cc/index.php?topic=495555.0)

Cost Breakdown: 
* ESP32
* PCB
* Keyswitches - RGB Type Needed (They have clear casings allowing for SMD leds to shine through. Some have specific cutouts for flat rgb led’s to peek through.
	* Gateron Blues / Whatevers - Clear top, white bottom. Supposedly the white bottom ones have the smd cutout $0.25ea[Gateron Blue (60G) Tactile Click Switches (Pack of 10) by Mechanical Keyboards Inc](https://mechanicalkeyboards.com/shop/index.php?l=product_detail&p=1272)

* Keycaps
	* DIY Casting - [Capcraft Hub - Updates & Tom Foolery Herein](https://geekhack.org/index.php?topic=46284.0)
	* Reddit DIY Keycap Wiki [key_modifications - MechanicalKeyboards](https://www.reddit.com/r/MechanicalKeyboards/wiki/key_modifications)
* Lipo // AA’s?

OLED Notes:
WeMos OLED 
I2C Data 5, Clock 4
[u8g2setupcpp · olikraus/u8g2 Wiki · GitHub](https://github.com/olikraus/u8g2/wiki/u8g2setupcpp#ssd1306-128x64_noname)

Constructor:  U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, 4, 5, U8X8_PIN_NONE);

Old Notes:
Microcontroller for new complex badge. Note, this part is not out yet. The Dev Board listed below is the closest thing to the new part.
Rigado BMD-340
https://www.rigado.com/products/modules/bmd-340/

Dev Board:
https://www.digikey.com/product-detail/en/nordic-semiconductor-asa/NRF52840-PDK/1490-1059-ND/6566109

#dczia
