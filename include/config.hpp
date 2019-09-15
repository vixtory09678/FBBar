#ifndef CONFIG_BARCODE_H
#define CONFIG_BARCODE_H

#define DEV_MODE

#include "ArduinoJson.h"
#include <Arduino.h>

#ifdef DEV_MODE
#define PRINT(str) Serial.print(str)
#define PRINTLN(str) Serial.println(str)

void printDetial(String prefix, String detail)
{
  Serial.printf("[%s] %s\n", prefix.c_str(), detail.c_str());
}
#endif

#endif