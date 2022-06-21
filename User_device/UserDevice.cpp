/**
 * @file UserDevice.cpp
 * @author George Okadarov
 * @brief 
 * @version 1.0.0
 * @date 2022-06-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// #include "Arduino.h"
#include "CommunicationHandler.cpp"

/**
 * User Device class definition
 * 
 */
class UserDevice {
  private:
    int test;
    CommunicationHandler comm;

  public:
    UserDevice( );

    // Methods
};

UserDevice::UserDevice( ) {
    comm = CommunicationHandler(
        ESP_NOW_ROLE_COMBO // Device role,
        ESP_NOW_ROLE_COMBO // Receiver role
    );
    //   this->var = var;
      
      // Pinmode
    //   pinMode(pinLED, OUTPUT);
}
