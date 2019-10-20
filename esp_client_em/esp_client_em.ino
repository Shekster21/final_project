/**
   BasicHTTPSClient.ino

    Created on: 20.08.2018

*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClientSecureBearSSL.h>
// Fingerprint for demo URL, expires on June 2, 2019, needs to be updated well before this date
const uint8_t fingerprint[20] = {0x95,0x23,0xc7,0x60,0x12,0xd0,0x3d,0x96,0x18,0x98,0xcf,0xbe,0x1a,0xfd,0x87,0xf6,0x55,0x8f,0x29,0x3d};

ESP8266WiFiMulti WiFiMulti;

void setup() {

  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("Gooner21", "aaronramsey");
}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);

    client->setFingerprint(fingerprint);

    HTTPClient https;
    
    back_https: if (https.begin(*client, "https://us-central1-espexperiment-bc1a4.cloudfunctions.net/addUser")) {  // HTTPS

      
      https.addHeader("Content-Type", "application/json");
      String postData = "{\"first\":\"Hector\",\"last\":\"Bellerin\",\"born\":\"October 17,1998\" }";
      Serial.println(postData);
      back: int httpCode = https.POST(postData); 

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = https.getString();
          Serial.println(payload);
        }
      } else {
          
      }

      https.end();
    } else {
      
    }
    
    
  }
  delay(10000);
}
