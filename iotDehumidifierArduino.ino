#include <WiFiS3.h>
#include <ArduinoHttpClient.h>
#include <Arduino_JSON.h>
#include "settings.h"
#include "button.h"
#include "light.h"

char ssid[] = SECRET_SSID;
char password[] = SECRET_PASSWORD;
char serverAddress[] = "192.168.1.103";
int port = 8080;
String action = "READING";
boolean dehumidifierStatus = false;
long previousMillis = 0; 
long interval = 60000;
// char* fingerprint = "93:2B:7B:C8:C2:25:D2:BC:EE:FC:C8:DA:98:C5:4C:1A:A8:59:BE:39";
// char elPriceServerAddress[] = "https://www.elprisetjustnu.se/api/v1/prices";
// char hueServerAddress[] = "192.168.1.26";

WiFiClient wifi;
HttpClient client = HttpClient(wifi, serverAddress, port);

// WiFiSSLClient wifiHTTPS;
// HttpClient clientHTTPS = HttpClient(wifiHTTPS, hueServerAddress, 443);

WiFiServer server(80);
int DHpin = 2;
byte dat[5];

byte read_data() {
  byte data;
  for(int i = 0; i < 8; i++) {
    if(digitalRead(DHpin) == LOW) {
      while(digitalRead(DHpin) == LOW);
      delayMicroseconds(30); 
      if(digitalRead(DHpin) == HIGH)
        data |= (1<<(7 - i));
      while(digitalRead(DHpin) == HIGH);
    }
  }
  return data;
}

void startReading() {
  digitalWrite(DHpin, LOW);
  delay(30);
  digitalWrite(DHpin, HIGH);
  delayMicroseconds(40);
  pinMode(DHpin, INPUT);
  while(digitalRead(DHpin) == HIGH);
  delayMicroseconds(80); 
  if(digitalRead(DHpin) == LOW);
  delayMicroseconds(80); 
  for(int i = 0; i < 4; i++) {
    dat[i] = read_data();
  }
  pinMode(DHpin, OUTPUT);
  digitalWrite(DHpin, HIGH);
}

// void actionCommand(boolean command) {
//   String postData = "{\"on\":{\"on\":" + String(command) + "\"}}";

//     Serial.println("action!");
//     clientHTTPS.beginRequest();
//     clientHTTPS.post("https://192.168.1.26/clip/v2/resource/light/c5acd120-bd09-4dee-8763-150a7321a698");
//     clientHTTPS.sendHeader("Content-Type", "application/json");
//     clientHTTPS.sendHeader("Content-Length", postData.length());
//     clientHTTPS.sendHeader("hue-application-key", HUE_API_KEY);
//     clientHTTPS.beginBody();
//     clientHTTPS.print(postData);
//     clientHTTPS.endRequest();

//     int statusCode = clientHTTPS.responseStatusCode();
//     String response = clientHTTPS.responseBody();

//     Serial.print("Status Code: ");
//     Serial.println(statusCode);
//     Serial.print("Response: ");
//     Serial.println(response);
    
//     Serial.println("Request sent, waiting for response...");

//     if (statusCode == -1) {
//       Serial.println("No response.");
//     } else {
//       String response = clientHTTPS.responseBody();
//       Serial.print("Status Code: ");
//       Serial.println(statusCode);
//       Serial.print("Response: ");
//       Serial.println(response);
//     }
// }

void setup() {
  Serial.begin(9600);
  buttonSetup();
  lightSetup();
  pinMode(DHpin, OUTPUT);

  Serial.println("Connecting to WiFi...");

  while (WiFi.begin(ssid, password) != WL_CONNECTED) {
    Serial.println("...");
    delay(1000);
  }

  Serial.println("Connected to WiFi!");
  server.begin();
  Serial.println("Server started.");
}


void loop() {

    buttonAction(dat);

    long rssi = WiFi.RSSI();
    Serial.print("Signal strength (RSSI): ");
    Serial.print(rssi);
    Serial.println(" dBm");

    long currentMillis = millis();

    Serial.print("currentMillis: ");
    Serial.println(currentMillis);
    Serial.print("previousMillis: ");
    Serial.println(previousMillis + 60000);

    if (currentMillis - previousMillis >= interval || previousMillis == 0) {
        previousMillis = currentMillis;

        if (action == "READING") {
            Serial.println("Starting sensor read...");
            startReading();
            Serial.println("Sensor read complete.");

            if (dat[0] >= 55 && dehumidifierStatus == false) {
                dehumidifierStatus = true;
            } else if (dat[0] < 45 && dehumidifierStatus == true) {
                dehumidifierStatus = false;
            }

            setLight(dat, dehumidifierStatus); 
            action = "SENDING";
        } else if (action == "SENDING") {
            String postData = "{\"temperature\":\"" + String(dat[2]) + "." + String(dat[3]) + "\",\"humidity\":\"" + String(dat[0]) + "." + String(dat[1]) + "\",\"dehumidifierStatus\":" + (dehumidifierStatus ? "true" : "false") + "}";

            client.beginRequest();
            client.post("/send-data");
            client.sendHeader("Content-Type", "application/json");
            client.sendHeader("Content-Length", postData.length());
            client.beginBody();
            client.print(postData);
            client.endRequest();

            int statusCode = client.responseStatusCode();
            if (statusCode != 200) {
                Serial.print("Error: ");
                Serial.println(statusCode);
            } else {
                String response = client.responseBody();
                JSONVar myObject = JSON.parse(response);
                if (JSON.typeof(myObject) != "undefined" && myObject.hasOwnProperty("temperature") && myObject.hasOwnProperty("humidity")) {
                    Serial.print("Response: ");
                    Serial.print((String)myObject["temperature"]);
                    Serial.print(", ");
                    Serial.println((String)myObject["humidity"]);
                } else {
                    Serial.println("Parsing input failed!");
                }
            }
            action = "READING";
        }
    }

    Serial.print("End of loop, next action: ");
    Serial.println(action);
}

