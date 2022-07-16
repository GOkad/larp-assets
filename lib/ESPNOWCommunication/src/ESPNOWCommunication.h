/**
 * @file ESPNOWCommunication.h
 * @author George Okadarov
 * @brief ESP NOW Communication library definitions
 * @date 2022-07-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifdef E32
  #include <esp_now.h>
  #include <WiFi.h>
#else
  #include<ESP8266WiFi.h>
  #include<espnow.h>

  #define MY_ROLE         ESP_NOW_ROLE_COMBO              // set the role of this device: CONTROLLER, SLAVE, COMBO
  #define RECEIVER_ROLE   ESP_NOW_ROLE_COMBO              // set the role of the receiver
  #define WIFI_CHANNEL    1
#endif

// Data structure to be sent
typedef struct struct_message {
  int type;
  unsigned long timestamp;
  char[20] data;
} struct_message;

class ESPNOWCommunication
{
  private:

  public:
    ESPNOWCommunication();
    ~ESPNOWCommunication();
    bool initialize();
    void onDataSent();
    void onDataReceived( const uint8_t * senderMac, const uint8_t *incomingData, int dataLength );
};

// // ESP 32
// void OnDataSent(
//   const uint8_t *mac_addr,
//   esp_now_send_status_t status
// );

// void OnDataRecv(
//   const uint8_t * senderMac,
//   const uint8_t *incomingData,
//   int len
// );

// // ESP 8266
// void transmissionComplete(
//   uint8_t *receiver_mac,
//   uint8_t transmissionStatus
// );

// void dataReceived(
//   uint8_t *senderMac,
//   uint8_t *data,
//   uint8_t dataLength
// );

// void esp_now_setup_32() {
//   WiFi.mode(WIFI_MODE_STA);

//   if (esp_now_init() != ESP_OK) {
//     Serial.println("Error initializing ESP-NOW");
//     return;
//   }

//   // Register the send callback
//   esp_now_register_send_cb(OnDataSent);
//   // Register callback function
//   esp_now_register_recv_cb(OnDataRecv);

//   // Register peer
//   memcpy(peerInfo.peer_addr, broadcastAddress, 6);
//   peerInfo.channel = 0;  
//   peerInfo.encrypt = false;
  
//   // Add peer        
//   if (esp_now_add_peer(&peerInfo) != ESP_OK){
//     Serial.println("Failed to add peer");
//     return;
//   }
// }

// void esp_now_setup_82() {
//   WiFi.mode(WIFI_STA);

//   if(esp_now_init() != 0) {
//     Serial.println("ESP-NOW initialization failed");
//     return;
//   }

//   esp_now_set_self_role(MY_ROLE);   
//   esp_now_register_send_cb(transmissionComplete);         // this function will get called once all data is sent
//   esp_now_register_recv_cb(dataReceived);               // this function will get called whenever we receive data
//   esp_now_add_peer(receiverAddress, RECEIVER_ROLE, WIFI_CHANNEL, NULL, 0);
// }