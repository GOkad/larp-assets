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
    int type;
    int message_type; 
};

// TODO: Add list of receivers or dynamically change peers 
// uint8_t receiverAddress[] = {0xBC, 0xDD, 0xC2, 0xBA, 0xFC, 0x76};   // SENSOR MAC

// void transmissionComplete(uint8_t *receiver_mac, uint8_t transmissionStatus);
// void dataReceived(uint8_t *senderMac, uint8_t *data, uint8_t dataLength);

class PingedAsset {
    public:
        // Index in Asset array
        int id;
        // Type of Asset [enum TYPES]
        int type;
        // Mac address
        // uint8_t macAddress[];
        // Last ping
        unsigned long lsatPing;
    
        PingedAsset( int id, int type ) {
            this->id = id;
            this->type = type;
            this->lsatPing = millis( );
        }

        bool isActive ( ) {
            return (millis() - this->lsatPing) < 5000;
        }
};