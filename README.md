# ESP32-MQTT-DOORBELL

A simple doorbell that plays an mp3 when MQTT message is received.
Please change the mklittlefs binary to yours on your plaform (usually found in ~/.platformio/packages/tool-mklittlefs/)

1. Get an ESP32 and a MAX98357A I2S DAC module with integrated amplifier
1. Solder a 100k resistor between GND and gain for maximum gain (omit if your speaker is too weak)
1. Wire them up:

```
ESP32 25  -->  DAC DOUT
ESP32 26  -->  DAC LRC
ESP32 27  -->  DAC BCLK
ESP32 5v  -->  DAC VIN
ESP32 GND -->  DAC GND

```

1. Connect your speaker to the output of the DAC module
1. Check src/settings.h and change as needed
1. Compile, upload with plaformio. Don't forget to do uploadfs to upload the mp3s as well!
1. If you publish "1" yo your topic the bell will sound. Make sure you publish without a retain flag :)

Please let me know if you find this interesting, pull requests always welcome!

