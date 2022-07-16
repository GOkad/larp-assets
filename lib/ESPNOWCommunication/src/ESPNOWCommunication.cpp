/**
 * @file ESPNOWCommunication.cpp
 * @author George Okadarov
 * @brief ESP NOW Communication library class implementation
 * @date 2022-07-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <ESPNOWCommunication.h>

ESPNOWCommunication::ESPNOWCommunication()
{
}

ESPNOWCommunication::~ESPNOWCommunication() = default;

/**
 * @brief Initialize ESP NOW Communication
 * 
 * @return true - initialization was successful
 * @return false - initialization has failed
 */
bool ESPNOWCommunication::initialize()
{
    // Put ESP32 into Station mode
    WiFi.mode(WIFI_MODE_STA);

    // Initialize ESP NOW or return false
    if (esp_now_init() != ESP_OK) {
        return false;
    }

    // Register the send callback
    // esp_now_register_send_cb(this->onDataSent);
    // Register callback function
    esp_now_register_recv_cb(this->onDataReceived);
    
    // TODO: Add peers
    // TODO: Setup wifi channed, etc.
    // Initialize ESP 32
    // Initialize ESP 8266

    return true;
}


void ESPNOWCommunication::onDataSent()
{

}

/**
 * @brief Callback executed when data is received via ESP-NOW
 * 
 * @param senderMac - MAC address of the sender device
 * @param incomingData - Data that has been sent
 * @param dataLength - Length of the sent data
 */
void ESPNOWCommunication::onDataReceived(const uint8_t * senderMac, const uint8_t *incomingData, int dataLength)
{
    Seria.print("Data Length:" );
    Serial.println( dataLength );
}