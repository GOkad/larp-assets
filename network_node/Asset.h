/**
 * @file Asset.h
 * @brief Base asset class 
 */

// Max time since last ping 
unsigned long PING_LIMIT = 5000;

class Asset {
    private:
        int type;
        unsigned long lastPinged;

    public:
        Asset( int type, unsigned long lastPing );
        bool isActive();
};

/**
 * @brief Construct a new Asset:: Asset object
 * 
 * @param int type - Device type <Definitions.h> 
 * @param unsigned long lastPing - Lastly Pinged at ms 
 */
Asset::Asset( int type, unsigned long lastPing ) {
    this->type = type;
    this->lastPinged = lastPing; 
}

/**
 * @brief Is the Asset still active
 * 
 * @return true 
 * @return false 
 */
bool Asset::isActive ( ) {
    return millis() - this->lastPinged < PING_LIMIT; 
}