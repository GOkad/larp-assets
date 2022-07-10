/**
 * @file WiFiConnection.h
 * @brief WiFi Connection handlers
 * @version 0.1
 * @date 2022-07-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#define JSON        "application/json"

// Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'
ESP8266WiFiMulti wifiMulti;

// Create a webserver object that listens for HTTP request on port 80
ESP8266WebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(Network Node Access Point)rawliteral";

// TODO: Add Device statuses in Asset.h
// TODO: Add JSON stringifier
// TODO: Add endpoints

/**
 * @brief Handle Root
 * Returns the status of the device
 * 
 */
void handleRoot() {
    // TODO: Add actual Device data
    server.send(200, JSON,
    "{\"device\": \"DEVICE_NAME\",\"status\": \"OK\"}"
    );
}

/**
 * @brief Handle Not Found
 * Returns a 404 Error
 * 
 */
void handleNotFound() {
    server.send(404, JSON,
    "{\"errors\" : [\"Invalid Endpoint\"]}"
    );
}

/**
 * @brief Initialize WiFi
 * 
 * @param String ssid - Access Point Name
 * @param String password - Access Point Password
 * 
 * @return true - WiFi was initialized successfully
 * @return false - Something went wrong
 */
bool initializeWiFi( String ssid, String password  ) {

    WiFi.softAP(ssid, password);

    // Start the mDNS responder for esp8266.local
    if (!MDNS.begin("esp8266")) {
        return false;
    }
    
    // Add root handler
    server.on("/", HTTP_GET, handleRoot);
    
    // Add 404 handler
    server.onNotFound(handleNotFound);
    
    // Add <functionality> endpoint
    // server.on("/url", HTTP_POST/HTTP_GET, handleCallback);
    
    // Start the server
    server.begin();

    return true;
}
