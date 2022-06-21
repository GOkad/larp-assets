/**
 * @file CommunicationHandler.cpp
 * @author your name (you@domain.com)
 * @brief Main Communication Handler
 * TODO: Make general library
 * @version 1.0.0
 * @date 2022-06-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "Arduino.h"

// Device role: CONTROLLER, SLAVE, COMBO
#define ROLE            ESP_NOW_ROLE_COMBO
// Receiver role
#define RECEIVER_ROLE   ESP_NOW_ROLE_COMBO
// WiFi channel
#define WIFI_CHANNEL    1

class CommunicationHandler {
    private:
        int role;
        int receiverRole;

    public:
        // Constructor
        CommunicationHandler( int role, int receiverRole );
        
        // Initialize ESP NOW connection
        bool initialize( );
        
        // Return the mac address of the device
        void getMacAddress();
};

/**
 * @brief Construct a new Communication Handler:: Communication Handler object
 * 
 */
CommunicationHandler::CommunicationHandler(
    int role, int receiverRole
) {
    this->role = role;
    this->receiverRole = receiverRole;
}

/**
 * Initialize ESP now connection
 * 
 */
bool initialize ( ) {

}


/**
 * Get Mac the Address of the device 
 * 
 * @return 
 */
void CommunicationHandler::getMacAddress() {
    Serial.print("Device mac address:" );
    Serial.println(WiFi.macAddress());

    // TODO: add return mac address
}
