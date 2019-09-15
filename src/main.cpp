#include <Arduino.h>
#include "pin_out.h"
#include "config.hpp"
#include "wifi_func.hpp"
#include "firebase.hpp"
#include "ntp_func.hpp"
#include <jsTimer.hpp>

void onReadBarCode(String id);
void writeOutputById(String id);

// ********************** Main Program ***********************
void setup()
{
// put your setup code here, to run once:
#ifdef DEV_MODE
  Serial.begin(9600);
#endif
  // for read barcode comunication
  Serial2.begin(115200);

  // setup pin output
  for (int i = 0; i < sizeof(listPin) / sizeof(listPin[0]); i++)
  {
    pinMode(listPin[i], OUTPUT);
    digitalWrite(listPin[i], LOW);
  }

  // setup other function in use
  setupWiFi();
  setupFirebase();
  setupNTP();
  Serial.println(getDateTime());
}
void loop()
{
  if (Serial2.available() > 0)
  {
    String tmpId = Serial2.readStringUntil('\n');
    tmpId.remove(tmpId.indexOf('\r'));
    printDetial("Serial barcode", tmpId);
    onReadBarCode(tmpId);
  }

  // put your main code here, to run repeatedly:
}

void onReadBarCode(String id)
{
  if (!Firebase.pathExist(firebaseData, String(PATH_ID) + id))
  {
    printDetial("Firebase error", firebaseData.errorReason());
    return;
  }

  if (!Firebase.getJSON(firebaseDataBase, String(PATH_ID) + id))
  {
    printDetial("Firebase error", firebaseDataBase.errorReason());
    return;
  }

  // convert json str to json obj
  printDetial("Firebase data", firebaseDataBase.jsonData());

  StaticJsonDocument<200> buff;
  buff["id"] = id;
  buff["time"] = getDateTime();
  String dataStr = "";
  serializeJson(buff, dataStr);
  if (Firebase.setJSON(firebaseData, String(PATH_SCAN) + id, dataStr))
  {
    // if success
  }

  StaticJsonDocument<128> getId;
  deserializeJson(getId, firebaseDataBase.jsonData());
  writeOutputById(getId["relay_id"]);
}

void writeOutputById(String id)
{
  int idOutput = id.toInt();
  if (idOutput > 10 && idOutput < 1)
  
    return;

  digitalWrite(listPin[idOutput - 1], HIGH);
  delay(1000);
  digitalWrite(listPin[idOutput - 1], LOW);
}
