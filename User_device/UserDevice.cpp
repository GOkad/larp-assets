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

#include "Arduino.h"
#include "CommunicationLibrary.cpp"

/**
 * User Device class definition
 * 
 */
class UserDevice {
  private:
    int test;
    CommunicationHandler comm;

  public:
    UserDevice( int test );

    // Methods
};

UserDevice::UserDevice( int test ) {
    this->test = test;
    comm = CommunicationHandler();
    //   this->var = var;
      
      // Pinmode
    //   pinMode(pinLED, OUTPUT);
}
