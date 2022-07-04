/**
 * @file CommunicationDefinitions.h
 * @brief Communication definitions and variables
 */

/**
 * @brief Request - Response schemas and definitions
 * 
 * Request - Response Schema [TYPE]
 * - G - general request - response
 * - <DEVICE> - Device specific request - response
 *  
 * [REQ] int REQUEST_NAME - description
 * - Data sent as string -
 * 
 * [RESP] int RESPONSE_NAME - description
 * - Data sent as string -
 * 
 * TODO: Check for struct -> String | String -> struct conversion
 */

/**
 * @brief Data packet structure
 * 
 * bool request - Is this a request[true] or response[false]
 * int type - type selected from REQUEST/RESPONSE definitions
 * unsigned long timestamp - timestamp in ms [millis]
 * String data - Data sent from the asset as a String
 */
struct __attribute__((packed)) dataPacket {
    int request;
    int type;
    unsigned long timestamp;
    String data;
};

/**
 * Request and Response definitions
 */
#define REQUEST     0
#define RESPONSE    1

/**
 * PING - AUTH [G]
 * 
 * [REQ] PING - Ping device for information
 *  - EMPTY REQUEST -
 *
 * [RESP] AUTH - Return information about device 
 *  int deviceType - Type of the device <Definitions.h> [Device Types]
 *  [TYPE] lon - Device Longitude
 *  [TYPE] lat - Device latitute
 * 
 */
#define PING 0
#define AUTH 0