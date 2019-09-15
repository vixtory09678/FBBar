#ifndef NTP_FUNC_H
#define NTP_FUNC_H

#include <time.h>
#include <Arduino.h>

/* NTP Constance */
#define NTP_SERVER "th.pool.ntp.org"
#define TIME_ZONE 25200

void setupNTP()
{

  #ifdef DEV_MODE
  printDetial("NTP", "Setup");
  #endif

  configTime(TIME_ZONE, 0, NTP_SERVER);
}

String getDateTime()
{
  char buff[80];
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    return "NTP get datetime error";
  }
  strftime(buff, 80, "%H:%M:%S", &timeinfo);
  return String(buff);
}

#endif