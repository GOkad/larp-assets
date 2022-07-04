/**
 * @file Definitions.h
 * @brief Aseet definitions and shared variables
 * @version 1.0
 * @date 2022-07-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// TFT Screen libraries
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
// ESP Now libraries
#include<ESP8266WiFi.h>
#include<espnow.h>
// Webserver libraries
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>


/**
 * D1 Mini pinout
 */
#define GP_16    16
#define GP_5     5
#define GP_4     4
#define GP_0     0
#define GP_2     2
#define GP_14    14
#define GP_12    12
#define GP_13    13
#define GP_15    15

/**
 * ESP 12-F pinout
 */
#define D0  16
#define D1  5
#define D2  4
#define D3  0
#define D4  2
#define D5  14
#define D6  12
#define D7  13
#define D8  15

/**
 * Device types
 */
#define NETWORK_NODE    0
#define USER_DEVICE     1
#define SUPPLY          2
#define SENSOR          3