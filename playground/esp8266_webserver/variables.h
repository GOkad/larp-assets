// .env variables
const bool DEBUG = true; // Is the module in DEBUG mode
const bool ROUTE_ONLT = true; // Get only the route and parameters from the request header
const String PROJECT_NAME = "ESP8266_PROJECT_NAME"; // Project name
const bool AP_MODE = false;
const bool NC_MODE = false;
const bool COMBINED_MODE = false;

// Connection variables
unsigned long currentTime = millis(); // Current time
unsigned long previousTime = 0; // Previous time
const long timeoutTime = 20000; // Define timeout time in milliseconds

// Network credentials
const char* NC_SSID = "Marasha crew "; // "Marasha crew "
const char* NC_PASSWORD = "P@r+!bo!69/ke+"; // "P@r+!bo!69/ke+"

// Access Point credentials
const char* AP_SSID = "ESP8266_SSID";
const char* AP_PASSWORD = "12345678";

// Set web server port number to 80
WiFiServer server(80);

// HTTP status response codes
const String HTTP_OK = "HTTP/1.1 200 OK";

// Content types
const String TYPE_HTML = "text/html";
const String TYPE_JSON = "application/json";

// Variable to store the HTTP request
String header;

/*
* Init function
* Initialize I/O pins and set registers
* and define output pins
*/
// Assign output variables to GPIO pins
const int GPIO2 = 2;  //GPIO 2 in ESP-01
const int GPIO0 = 0;  //GPIO 0 in ESP-01