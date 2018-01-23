# irpost
An Arduino project to transform Infrared Remote Control events to REST calls

Inspired from https://damow.net/ir-over-ip/

Remote Control codes are for [Yamaha AV Receiver RX-V461](https://www.cnet.com/products/yamaha-rx-v461-series/specs/). The API calls control [castagnet](https://github.com/lbovet/castagnet), a [ChromeCast client](https://en.wikipedia.org/wiki/Chromecast).

<h2>
<img height="160" src="https://user-images.githubusercontent.com/692124/35281379-12ccc780-0053-11e8-9e2c-8e874854ef80.jpg"> + <img height="160" src="https://user-images.githubusercontent.com/692124/35281510-6361f6a2-0053-11e8-9144-8a7a87ee1207.jpg"> + <img height="160" src="https://user-images.githubusercontent.com/692124/35281403-1f41dcb2-0053-11e8-964a-c864b01dcd58.jpg"> = <img height="160" src="https://user-images.githubusercontent.com/692124/35281537-743108ba-0053-11e8-818c-ec013096e10a.jpg">
</h2>

Hardware:
- [Arduino UNO](https://store.arduino.cc/arduino-uno-rev3)
- [Wiznet W5500 Ethernet Shield](http://www.wiznet.io/product-item/w5500-ethernet-shield/)
- [TOSP38238](https://www.adafruit.com/product/157)

Software:
- [PlatformIO](http://platformio.org/)
- [IRRemote](http://platformio.org/lib/show/4/IRremote)
- [Ethernet3](http://platformio.org/lib/show/1588/Ethernet3)
