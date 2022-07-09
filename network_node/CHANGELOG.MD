# Network Node Changelog
All notable changes to this project will be documented in this file.
The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## Version 1.3.0 [2022-07-xx]
### Added
- Web server base functionality
- `RequestResponseHandler.h` file for all Request/Response handlers
### Fixed
- Typos and errors from PR

## Version 1.2.0 [2022-07-06]
---
> ## [WIP] - Request - Response handlers
> Request - Response handlers are defined in `"CommunicationDefinition.h"` with the definition of the request or response.
```
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
    void handleAuthentication( String data );
```
> And then are ?overwriten? in the `<device>.ino` file based on the ?needs? of the device.
---
### Added
- `Asset` class
- `[REQ] PING - [RESP] AUTH` Handlers
### Removed
- `bool request` parameter from data packet


## Version 1.1.0 [2022-07-04]
### Added
- Base `ESP NOW` communication functionality
- `Definitions` file
- `CommunicationDefinitions` file containing `Request - Response` schema and definitions
- `Network_Node` dev project

## Version 1.0.0 [2022-07-02]
- Initial Setup