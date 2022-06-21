/**
 * @file CommunicationHandler.cpp
 * @author your name (you@domain.com)
 * @brief ESP NOW communication handler
 * @version 1.0.0
 * @date 2022-06-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include<ESP8266WiFi.h>
#include<espnow.h>

#define MY_NAME         "CONTROLLER_NODE"
// set the role of this device: CONTROLLER, SLAVE, COMBO
#define MY_ROLE         ESP_NOW_ROLE_CONTROLLER
// set the role of the receiver
#define RECEIVER_ROLE   ESP_NOW_ROLE_SLAVE
#define WIFI_CHANNEL    1

/**
 * Message types
 */
#define PING    0   // Basic ping request
#define AUTH    1   // Authorize request
//#define NAME    x // Description


// Add a list of receivers
uint8_t receiverAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};   // please update this with the MAC address of the receiver

// Data packet model
struct __attribute__((packed)) dataPacket {
    int propType
    int messageType;
    String macAddress;
    String data;
    bool respond;
    bool broadcastResponse;
};

class CommunicationHandler {
    private:
        
    public:
    CommunicationHandler ( ) {

    }

    bool initialize() {
        
        // Set wifi mode to station
        WiFi.mode(WIFI_STA);

        // we do not want to connect to a WiFi network
        // TODO: add conditional logic?
        WiFi.disconnect();

        // Return false if the initialization fails
        if(esp_now_init() != 0) {
            Serial.println("ESP-NOW initialization failed");
            return false;
        }

        // Setup role
        esp_now_set_self_role(MY_ROLE);
        // Register callback for when the data is send
        esp_now_register_send_cb(transmissionComplete);

        // Add peers
        esp_now_add_peer(receiverAddress, RECEIVER_ROLE, WIFI_CHANNEL, NULL, 0);

        Serial.println("Initialized.");
        
        return true;
    }


    static void transmissionComplete( uint8_t *receiver_mac, uint8_t transmissionStatus ) {
        if(transmissionStatus == 0) {
           // Transmition is successful
            Serial.println("Data sent successfully");
        } else {
            // There was an error
            Serial.print("Error code: ");
            Serial.println(transmissionStatus);
        }
    }
};