#ifndef WIFI_FUNC_H
#define WIFI_FUNC_H
#include <Arduino.h>
#include <WiFi.h>
#include "config.hpp"

/* WiFi Constance */
#define WIFI_SSID "PrinceBot"
#define WIFI_PASSWORD "aaaaaaaa"

/*  WiFi Function */
void onWiFiEvent(WiFiEvent_t event)
{

  #ifdef DEV_MODE
  PRINT(F("[WiFi] mode is "));
  PRINTLN(event);
  #endif

  switch (event)
  {
  case SYSTEM_EVENT_STA_CONNECTED:

    #ifdef DEV_MODE
    printDetial("WiFi", "Connected");
    #endif

    break;
  case SYSTEM_EVENT_STA_GOT_IP:

    #ifdef DEV_MODE
    printDetial("WiFi", "Connect WiFi" + WiFi.SSID());
    printDetial("WiFi", "IP" + WiFi.localIP().toString());
    #endif

    break;
  case SYSTEM_EVENT_STA_DISCONNECTED:

    #ifdef DEV_MODE
    printDetial("WiFi", "Disconnected");
    #endif

    break;
  }
}

void setupWiFi()
{

  #ifdef DEV_MODE
  printDetial("WiFi", "Setup");
  #endif

  WiFi.disconnect(true);
  delay(1000);
  WiFi.onEvent(onWiFiEvent);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
}

#endif