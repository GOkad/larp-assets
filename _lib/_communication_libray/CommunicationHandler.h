/**
 * @brief Data packet model
 * 
 * int type - request/response type
 * long timestamp - sent on timestamp 
 * String data - data sent from asset to be parsed and used
 */
struct __attribute__((packed)) dataPacket {
    int type;
    long timestamp;
    String data;
};

class CommunicationHandler {
    private:
    public:
        CommunicationHandler( );
        bool initialize( );
}