# NOBOTWars

Once you've checked this repo out you'll need to change the following lines in credentials.c

```
#ifndef WIFI_SSID
#define WIFI_SSID "<Your SSID>"
#define WIFI_PASS "<Your Password>"
#endif
```

To contain your wifi credentials.

credentials.c is marked to be ignored by git in .gitignore, so you can safely dev without them getting checked in to git.
