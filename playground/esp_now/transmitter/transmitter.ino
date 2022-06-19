/****************************************************************************************************************************************************
 *  TITLE: ESP-NOW Getting Started Examples
 *
 *  By Frenoy Osburn
 *  YouTube Video: https://youtu.be/_cNAsTB5JpM
 ****************************************************************************************************************************************************/

 /********************************************************************************************************************
  * Please make sure that you install the board support package for the ESP8266 boards.
  * You will need to add the following URL to your Arduino preferences.
  * Boards Manager URL: http://arduino.esp8266.com/stable/package_esp8266com_index.json
 ********************************************************************************************************************/
 
 /********************************************************************************************************************
 *  Board Settings:
 *  Board: "WeMos D1 R1 or Mini"
 *  Upload Speed: "921600"
 *  CPU Frequency: "80MHz"
 *  Flash Size: "4MB (FS:@MB OTA:~1019KB)"
 *  Debug Port: "Disabled"
 *  Debug Level: "None"
 *  VTables: "Flash"
 *  IwIP Variant: "v2 Lower Memory"
 *  Exception: "Legacy (new can return nullptr)"
 *  Erase Flash: "Only Sketch"
 *  SSL Support: "All SSL ciphers (most compatible)"
 *  COM Port: Depends *On Your System*
 *********************************************************************************************************************/
#include <ESP8266WiFi.h>
#include <espnow.h>
#include "dataPacket.h"

#define MY_NAME         "CONTROLLER_NODE"
#define MY_ROLE         ESP_NOW_ROLE_CONTROLLER         // set the role of this device: CONTROLLER, SLAVE, COMBO
#define RECEIVER_ROLE   ESP_NOW_ROLE_SLAVE              // set the role of the receiver
#define WIFI_CHANNEL    1


uint8_t receiverAddress[] = {0x40, 0x91, 0x51, 0x46, 0x27, 0x56};
uint8_t receiverAddress2[] =  {0xC4, 0x5B, 0xBE, 0x54, 0x74, 0x32};

int PROP_TYPE;

void setup() {
  Serial.begin(115200);     // initialize serial port

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();        // we do not want to connect to a WiFi network

  if(esp_now_init() != 0) {
    Serial.println("ESP-NOW initialization failed");
    return;
  }

  esp_now_set_self_role(MY_ROLE);   
  esp_now_register_send_cb(transmissionComplete);   // this function will get called once all data is sent
  
  esp_now_add_peer(receiverAddress, RECEIVER_ROLE, WIFI_CHANNEL, NULL, 0);
  esp_now_add_peer(receiverAddress2, RECEIVER_ROLE, WIFI_CHANNEL, NULL, 0);

  PROP_TYPE = DANGER;

  Serial.println("Initialized.");
}

void loop() {
  dataPacket packet;


  packet.type = PROP_TYPE;

  switch ( PROP_TYPE ) {
    case PROP:
      packet.activeDistance = MAX_DISTANCE;
      packet.threatLevel = MIN_THREAT;
      break;
    case DANGER:
      packet.activeDistance = MIN_DISTANCE;
      packet.threatLevel = MAX_THREAT;
      break;
    default:
      packet.activeDistance = MIN_DISTANCE;
      packet.threatLevel = MIN_THREAT;
      break;
  }

  
  esp_now_send(receiverAddress, (uint8_t *) &packet, sizeof(packet));
  delay(10);
  esp_now_send(receiverAddress2, (uint8_t *) &packet, sizeof(packet));

  delay(5000);
}

void transmissionComplete(uint8_t *receiver_mac, uint8_t transmissionStatus) {
  if(transmissionStatus == 0) {
    Serial.println("Data sent successfully");
  } else {
    Serial.print("Error code: ");
    Serial.println(transmissionStatus);
  }
}