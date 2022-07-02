/**
 * @file AssetDefinitions.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-06-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/**
 * @brief ESP 12-F / D1 Mini pinout
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

#define D0  16
#define D1  5
#define D2  4
#define D3  0
#define D4  2
#define D5  14
#define D6  12
#define D7  13
#define D8  15

#define WIFI_CHANNEL    1

// All Asset types
enum TYPES {
    BASE = 0,
    USER_DEVICE,
    NETWORK_NODE,
    SENSOR,
    SUPPLY
};

// All message types
enum MESSAGE_REQUEST {
    /**
     * @brief Basic asset ping
     * @ref Coresponding response - AUTH
     */
    PING = 0,
    /**
     * @brief Request data from sensor
     * @ref Coresponding response - SEND_REQUEST_DATA
     */
    REQUEST_DATA
};

enum MESSAGE_RESPONSE {
    /**
     * @brief Authorize asset
     * @ref Coresponding request - PING
     */
    AUTHORIZE = 0,
    /**
     * @brief Send requested data
     * @ref Coresponding request - REQUEST_DATA
     */
    SEND_REQUESTED_DATA
};

/**
 * Data packet model
 * 
 * int type - Asset type
 * int message_type - Message type  
 * 
 */
struct __attribute__((packed)) dataPacket {
    int message_type;
    long timestamp;
    String data;
};

// TODO: Add list of receivers or dynamically change peers 
// uint8_t receiverAddress[] = {0xBC, 0xDD, 0xC2, 0xBA, 0xFC, 0x76};   // SENSOR MAC
