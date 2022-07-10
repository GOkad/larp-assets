/**
 * ESP 32 DEV Board testing
 * ESP - NOW
 * WiFi Server
 * TODO: GPS Module
 */

// Include WiFi Library
#include "WiFi.h"
#include <esp_now.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>


// Variables for test data
int int_value;
float float_value;
bool bool_value = true;

// MAC Address of responder - edit as required
// D1 Mini - Pins
uint8_t pinsMini[] = {0x40, 0x91, 0x51, 0x46, 0x27, 0x56};

uint8_t broadcastAddress[] = {0x40, 0x91, 0x51, 0x46, 0x27, 0x56};

// Define a data structure
typedef struct struct_message {
  int type;
  unsigned long timestamp;
  String data;
} struct_message;

struct __attribute__((packed)) dataPacket {
    int type;
    unsigned long timestamp;
    String data;
};

// Create a structured object
struct_message myData;

// Peer info
esp_now_peer_info_t peerInfo;

// Callback function called when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
 
// Callback function executed when data is received
void OnDataRecv(const uint8_t * senderMac, const uint8_t *incomingData, int len) {
  // Parse the mac address
  char macAddressString[18];
  snprintf(macAddressString, sizeof(macAddressString), "%02x:%02x:%02x:%02x:%02x:%02x", senderMac[0], senderMac[1], senderMac[2], senderMac[3], senderMac[4], senderMac[5]);

  Serial.println();
  Serial.print("Received data from: ");
  Serial.println(macAddressString);
  
  // Parse send data packet
  dataPacket packet;
  memcpy(&packet, incomingData, sizeof(packet));
  
  Serial.print("Response/Request type: ");
  Serial.println(myData.type);
  Serial.print("timestamp: ");
  Serial.println(myData.timestamp);
  Serial.print("data: ");
  // Serial.println(myData.data);
  // Send data back

  // Send message via ESP-NOW
  dataPacket newPacket;
  newPacket.type = 2;
  newPacket.timestamp = millis();
  newPacket.data = "ESP32";

  // TODO: check ESP32 result = esp_now_send
  // esp_now_send(broadcastAddress, (uint8_t *) &newPacket, sizeof(newPacket));
}

const char index_html[] PROGMEM = R"rawliteral(ESP 32 status = OK)rawliteral";

String processor(const String& var){
  //Serial.println(var);
  
  return String();
}


// Replace with your network credentials
const char* ssid = "esp32";
const char* password = "";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

void setup() {

  // Setup Serial Monitor
  Serial.begin(115200);

  // Put ESP32 into Station mode
  WiFi.mode(WIFI_MODE_STA);

  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register the send callback
  esp_now_register_send_cb(OnDataSent);
  // Register callback function
  esp_now_register_recv_cb(OnDataRecv);

  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  // Print MAC Address to Serial monitor
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());

  // Init wifi
  WiFi.softAP(ssid, password);
  // Start the mDNS responder for esp8266.local
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(200, "text/plain", "ESP 32 STATUS: OK");
  });
  // Start server
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

}
