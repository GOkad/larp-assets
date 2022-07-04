/**
 * @file Communication.h
 * @brief Main Communication Handler
 * @version 1.1.0
 * @date 2022-07-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "CommunicationDefinitions.h"

// set the role of this device: CONTROLLER, SLAVE, COMBO
#define MY_ROLE         ESP_NOW_ROLE_COMBO
// set the role of the receiver
#define RECEIVER_ROLE   ESP_NOW_ROLE_COMBO
// WiFi Channel
#define WIFI_CHANNEL    1

// TODO: See how this can be a list of MAC addresses
// and also switch it to #define if possible [pointers?]
uint8_t receiverAddress[] = {0xBC, 0xDD, 0xC2, 0xBA, 0xFC, 0x76};

/**
 * @brief Send data via ESP NOW
 *
 * @param uint8_t receiverAddress[] - Mac address of the receiver device 
 * @param int request - Is this a request or response <CommunicationDefinitions.h>
 * @param int type - Request/Response type <CommunicationDefinitions.h> 
 * @param data - Stringified data from device <CommunicationDefinitions.h>
 */
void sendData ( uint8_t receiverAddress[], int request, int type, String data ) {
  dataPacket packet;
  packet.request = request;
  packet.type = type;
  packet.data = data;

  esp_now_send( receiverAddress, (uint8_t *) &packet, sizeof(packet) );

}

/**
 * @brief Callback for when the transmition was completed
 * 
 * @param receiverMac - Mac address of the receiver
 * @param transmissionStatus - Trasmition status
 */
void onTransmissionCompleted(uint8_t *receiverMac, uint8_t transmissionStatus) {
  if(transmissionStatus == 0) {
    Serial.println("Data sent successfully");
  } else {
    // TODO: Add error handling
    Serial.print("Error code: ");
    Serial.println(transmissionStatus);
  }
}

/**
 * @brief Callback for when data is received
 * 
 * @param senderMac - Mac address of the sender
 * @param data - Data that has been sent
 * @param dataLength - Length of the sent data
 */
void onDataReceived(uint8_t *senderMac, uint8_t *data, uint8_t dataLength) {
  // Parse the mac address
  char macAddressString[18];
  snprintf(macAddressString, sizeof(macAddressString), "%02x:%02x:%02x:%02x:%02x:%02x", senderMac[0], senderMac[1], senderMac[2], senderMac[3], senderMac[4], senderMac[5]);

    
  Serial.println();
  Serial.print("Received data from: ");
  Serial.println(macAddressString);
  // Parse send data packet
  dataPacket packet;
  memcpy(&packet, data, sizeof(packet));
  
  Serial.print("Request or Response: ");
  Serial.println(packet.request == REQUEST ? "Request" : "Response");
  Serial.print("Response/Request type: ");
  Serial.println(packet.type);
  Serial.print("timestamp: ");
  Serial.println(packet.timestamp);
  Serial.print("Data as string: ");
  Serial.println(packet.data);

  // TODO: Parse string data
}

/**
 * @brief  Initialize ESP NOW Communication
 * 
 * @return true - ESP NOW was successfuly initialized
 * @return false - Something went wrong
 */
bool initializeESPNOW (  ) {
    // Set WiFi mode to STA
    WiFi.mode(WIFI_STA);

    if(esp_now_init() != 0) {
        Serial.println("ESP-NOW initialization failed");
        return false;
    }

    esp_now_set_self_role(MY_ROLE);   
    // Register on transmittion completed callback
    esp_now_register_send_cb(onTransmissionCompleted);
    // Register on data received callback
    esp_now_register_recv_cb(onDataReceived);
    
    // Add ESP NOW peers
    // esp_now_add_peer(receiverAddress, RECEIVER_ROLE, WIFI_CHANNEL, NULL, 0);

    return true;
}

/**
 * @brief Get the Mac Address object
 * 
 */
void getMacAddress ( ) {
    Serial.println(WiFi.macAddress());
    // TODO: Return the mac address
}

