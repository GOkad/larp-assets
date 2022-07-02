/**
 * @file Asset.cpp
 * @author George Okadarov
 * @brief Base Asset class containing main functionality
 * @version 1.0.0
 * @date 2022-06-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "AssetDefinitions.h"
#include "CommunicationHandler.cpp"

/**
 * @brief Main asset class with base functionality:
 * 
 * ESP-NOW communication
 * GPS Handler
 */
class Asset {
    private:
        int type;
        CommunicationHandler comm;

        // TODO: handle pinged assets 

    public:
    /**
     * @brief Construct a new Asset object
     * 
     * @param type - asset type [enum TYPES]
     */
    Asset ( int type ) {
        this->type = type;
        this->comm = CommunicationHandler();
    }

    bool initialize ( ) {
        return ( this->comm.initialize() );

    }

    
};
