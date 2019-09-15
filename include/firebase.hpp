#ifndef FIREBASE_BARCODE_H
#define FIREBASE_BARCODE_H

#include <Arduino.h>
#include <FirebaseESP32.h>

#include "config.hpp"

/* Firebase Constance */
#define FIREBASE_HOST "barcode-ad226.firebaseio.com"
#define FIREBASE_AUTH "bfBpArquzHa9lquSkSuuSQdJi1Pxog8SFSj2TnFp"
#define PATH_ID "tag-id/"
#define PATH_SCAN "scan/"

/* Firebase Variable */
FirebaseData firebaseDataStream;
FirebaseData firebaseData;
FirebaseData firebaseDataBase;

/*  Firebase Function */
void onStream(StreamData data);
void setupFirebase();
void fetchData();

// callback for stream event
void onStream(StreamData data)
{
#ifdef DEV_MODE
  printDetial("Firebase stream", "Data path is " + data.dataPath());
  printDetial("Firebase stream", "Data type is " + data.dataType());
  printDetial("Firebase stream", "Data strm is " + data.streamPath());
  PRINTLN("");
#endif
}

void setupFirebase()
{
#ifdef DEV_MODE
  printDetial("Firebase", "Setup");
#endif

  // setup firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  // initial stream event
  if (!Firebase.beginStream(firebaseDataStream, PATH_ID))
  {
#ifdef DEV_MODE
    printDetial("Firebase err", "error begin stream is " + firebaseDataStream.errorReason());
#endif
    return;
  }

  // set callback for stream event
  Firebase.setStreamCallback(firebaseDataStream, onStream);

  // fetch data for check available data
  // fetchData();
}

void fetchData()
{
  // check path
  if (!Firebase.pathExist(firebaseData, PATH_ID))
  {
#ifdef DEV_MODE
    printDetial("Firebase error", firebaseData.errorReason());
#endif
    return;
  }
  // get list of document and validate
  if (!Firebase.getShallowData(firebaseData, PATH_ID))
  {
#ifdef DEV_MODE
    printDetial("Firebase error", firebaseData.errorReason());
#endif
    return;
  }
  // convert json str to json object

  if (!Firebase.getJSON(firebaseDataBase, PATH_ID))
  {
#ifdef DEV_MODE
    printDetial("Firebase error", firebaseDataBase.errorReason());
#endif
    return;
  }

  StaticJsonDocument<2500> docDataBase;
  deserializeJson(docDataBase, firebaseDataBase.jsonData());

  // for each get list keys from json object
  for (JsonPair keyValue : docDataBase.as<JsonObject>())
  {
#ifdef DEV_MODE
    printDetial("Firebase key", keyValue.key().c_str());
    printDetial("Firebase key", docDataBase.getMember(keyValue.key()).getMember("date"));
#endif
  }
}

#endif