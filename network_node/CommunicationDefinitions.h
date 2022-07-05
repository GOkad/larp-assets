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
 * [type] handle<RESPONSE_NAME>()
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
    int type;
    unsigned long timestamp;
    String data;
};

/**
 * PING - AUTH [G]
 */
    /**
     * [REQ] PING - Ping device for information
     *  - EMPTY REQUEST -
     */
    #define PING 0
    /**
     * [RESP] AUTH - Return information about device 
     *  - int deviceType - Type of the device <Definitions.h> [Device Types]
     *  - [TYPE] lon - Device Longitude
     *  - [TYPE] lat - Device latitute
     * 
     */
    #define AUTH 1

    /**
     * @brief Authuentication handler
     * Called when a device send authentication data
     * 
     * @param String data - Data sent from device
     */
    void handleAuthentication( String data ) {
        // TODO: Parse string data
        // TODO: Handle Authentication based on Device sender type and this Device type
        if ( DEVICE_TYPE == NETWORK_NODE  ) {
            // TODO: Create a new Asset()
        }
    }    


/**
 * @brief String data separator
 */
#define SEPARATOR   "|"