/**
 * @file CommunicationHandler.cpp
 * @author George Okadarov
 * @brief [POC] Communication Handler 
 * @version 1.0.0
 * @date 2022-06-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include<ESP8266WiFi.h>
#include<espnow.h>

#define WIFI_CHANNEL    1

class CommunicationHandler {
    private:

    public:
    CommunicationHandler () {

    }

    /**
     * @brief On Transmition Completed
     * Executed when data has beed transmited 
     * 
     * @param receiver_mac - MAC address of the receiver
     * @param transmissionStatus - Transmition status
     */
    void onTransmitionCompleted ( uint8_t *receiver_mac, uint8_t transmissionStatus ) {
        if(transmissionStatus == 0) {
            // TODO: Handler send data successfully
            Serial.println("Data sent successfully");
        }
        else {
            // TODO: Handle send data error
            Serial.print("Error code: ");
            Serial.println(transmissionStatus);
        }
    }
    
    /**
     * @brief Initialize communication
     * 
     * @return true - Setup was successfull
     * @return false - Something failed
     */
    bool setup () {
        // Setup WiFi mode
        WiFi.mode(WIFI_STA);

        // We do not want to connect to a WiFi network
        WiFi.disconnect();

        // Return false if ESP-NOW initialization failes
        if( esp_now_init() != 0 ) {
            // TODO: Add led error handler
            Serial.println("ESP-NOW initialization failed");
            return false;
        }

        // Set device role
        esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
        
        // Register callback on completed transmition
        esp_now_register_send_cb(this->onTransmitionCompleted);
        
        // Register callback when data is received
        // esp_now_register_recv_cb(dataReceived);   
        
        // Add ESP-NOW peers
        // TODO: add peers from list of peers
        // and check for dinamically changing peers
        // esp_now_add_peer(
        //     receiverAddress,
        //     ESP_NOW_ROLE_COMBO,
        //     WIFI_CHANNEL,
        //     NULL,
        //     0
        // );

        Serial.println("Initialized.");
        return true;
    }    
};
