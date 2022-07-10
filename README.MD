# L.A.R.P. Assets, programs & schematics

## ESP Developement Setup
- ### Download and install [Arduino IDE v.2.0](https://www.arduino.cc/en/software)
> - `Recomended` download [VS Code](https://code.visualstudio.com/download) for actual developement and use `Arduino IDE` only for verifying and uploading
> - `TODO:` Check `Platform IO` as an alternative

- ### Add `ESP` boards to `Arduino IDE`
>- In your Arduino IDE, go to `File> Preferences`
>- Enter <br> 
https://dl.espressif.com/dl/package_esp32_index.json,http://arduino.esp8266.com/stable/package_esp8266com_index.json
<br> into the `Additional Boards Manager URLs` 
>- Click the `OK` button
>- Open the Boards Manager. `Go to Tools > Board > Boards Manager`
>- Search for `ESP8266` and press install button for the `ESP8266 by ESP8266 Community`
>- Also install `ESP32` Boards

- ### Installing the libraries
>- Open `Library Manager` from the sidebar
>- Search and install:
>- `Adafruit st7735 and ST7789` [TFT Screen]
>- `TinyGPS` [GPS Module]
---
>- Open `Sketch> Include Library> Add .ZIP Library...`
>- Install `.zip` libraries from `_lib/` folder:
>- `AsyncTCP-master`
>- `ESPAsyncWebServer-master`

- ### Install the `COM` Port driver
>- Go to `_lib/drivers` and install:
>- `CH34x_Install_Windows_v3_4.zip`
>- `CH343CDC.ZIP`
>- `CP210x_Windows_Drivers.zip`


## JAVA Developement Setup
- ### `TODO:`Add steps and init project

## Android Developement Setup
- ### `TODO:`Add steps and init project