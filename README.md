# NOBOTWars

## Setup

Once you've checked this repo out with git you'll need to change the following lines in credentials.c

```
#ifndef WIFI_SSID
#define WIFI_SSID "<Your SSID>"
#define WIFI_PASS "<Your Password>"
#endif
```

To contain your wifi credentials.

credentials.c is marked to be ignored by git in .gitignore, so you can safely dev without them getting checked in to git.

## Over-The-Air (OTA) Upgrades

After you load this project for the first time you'll be able to push future upgrades over the network. Assuming you have python3 and the ESPWiFi Arduino SDK installed, you should see a "network" COM port appear in your Arduino IDE.

Sometimes it can take a couple of tries or reboots to load a program over WiFi. Make sure the web server isn't hanging waiting for input as this blocks OTA upgrades from shipping.
