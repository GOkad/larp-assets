// /**
//  * @file GPSHandler.cpp
//  * @author Geoger Okadarov
//  * @brief 
//  * @version 0.1
//  * @date 2022-06-24
//  * 
//  * @copyright Copyright (c) 2022
//  * 
//  */
// #include <SoftwareSerial.h>
// #include <TinyGPS.h>

// class GPSHandler
// {
//     private:
//         /* data */
//         SoftwareSerial ss(4, 3);
//     public:
//         GPSHandler(/* args */) {

//         }

//         void init ( ) {
//             Serial.print("Testing TinyGPS library v. "); Serial.println(TinyGPS::library_version());
//             Serial.println("by Mikal Hart");
//             Serial.println();
//             Serial.println("Sats HDOP Latitude  Longitude  Fix  Date       Time     Date Alt    Course Speed Card  Distance Course Card  Chars Sentences Checksum");
//             Serial.println("          (deg)     (deg)      Age                      Age  (m)    --- from GPS ----  ---- to London  ----  RX    RX        Fail");
//             Serial.println("-------------------------------------------------------------------------------------------------------------------------------------");
//             this->ss.begin(4800);
//         }
// };
