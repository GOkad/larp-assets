/**
 * @file Asset.cpp
 * @author George Okadarov
 * @brief Base Asset class containing main functionality
 * @version 1.0.0
 * @date 2022-06-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<ESP8266WiFi.h>
#include<espnow.h>
#include "AssetDefinitions.h"

/**
 * @brief Main asset class with base functionality:
 * 
 * ESP-NOW communication
 * GPS Handler
 */
class Asset {
    private:
        int type;
        // PingedAsset pingedAssets[10];
    public:
    /**
     * @brief Construct a new Asset object
     * 
     * @param type - asset type [enum TYPES]
     */
    Asset ( int type ) {
        this->type = type;
    }

    /**
     * @brief Initialize asset
     * 
     * @return true - initialization was sucessfull
     * @return false - Something went wrong
     */
    bool initialize ( ) {
        // Setup ESP-NOW
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
        esp_now_register_send_cb(this->onTransmissionCompleted);
        
        // Register callback when data is received
        esp_now_register_recv_cb(this->onDataReceived);   
        
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

        // Setup GPS Handlers
    }

    /**
     * @brief On transmition completed handler
     * Executed when the data has been transmitted
     *  
     * @param receiver_mac - MAC address of the receiver
     * @param transmissionStatus - Status of the transmition
     */
    static void onTransmissionCompleted(uint8_t *receiver_mac, uint8_t transmissionStatus) {
        if(transmissionStatus == 0) {
            // TODO: Handle send data successfully
            Serial.println("Data sent successfully");
        }
        else {
            // TODO: Handle send data error
            Serial.print("Error code: ");
            Serial.println(transmissionStatus);
        }
    }

    /**
     * @brief On Data Receive handler
     * Executed when data was received
     * 
     * @param senderMac - MAC address of the sender
     * @param data - Received data packet
     * @param dataLength - Length of the data packet
     */
    static void onDataReceived(uint8_t *senderMac, uint8_t *data, uint8_t dataLength) {
        // Parse mac address to string
        char macStr[18];  
        snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x", senderMac[0], senderMac[1], senderMac[2], senderMac[3], senderMac[4], senderMac[5]);
        Serial.println();
        Serial.print("Received data from: ");
        Serial.println(macStr);
        
        // Parse data packet
        // dataPacket packet;
        // memcpy(&packet, data, sizeof(packet));
        
        // Serial.print("sensor1: ");
        // Serial.println(packet.sensor1);
        // Serial.print("sensor2: ");
        // Serial.println(packet.sensor2);
        // Serial.print("sensor3: ");
        // Serial.println(packet.sensor3);
    }

};
