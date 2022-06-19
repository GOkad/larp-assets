// Load Wi-Fi library
#include <ESP8266WiFi.h>

// .env variables
const bool DEBUG = true; // Is the module in DEBUG mode
const bool ROUTE_ONLT = true; // Get only the route and parameters from the request header
const String PROJECT_NAME = "ESP8266_PROJECT_NAME"; // Project name

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

const String HTML_DATA_REPLACE = "[BODY_CONTENT]";

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

void initialize ( ) {
  // Initialize the output variables as outputs
  pinMode(GPIO2, OUTPUT);
  pinMode(GPIO0, OUTPUT);
  // Set outputs to LOW
  digitalWrite(GPIO2, LOW);
  digitalWrite(GPIO0, LOW);

}
/*
* Setup function to configure
* - Module WiFi connections
* - I/O Pins
*/
void setup() {
  // Set Baud Rate for Serial communication
  Serial.begin(115200);

  // Initialize ports and registers
  initialize( );

  // Initialize soft access point if the credentials are not empty
  if ( strlen(AP_SSID) > 0 && strlen(AP_PASSWORD) > 0 ) {
    // Begin Access Point
    WiFi.softAP(AP_SSID, AP_PASSWORD);

    // Print soft Access Point data
    _log("Access Point data :");
    _log( AP_SSID );
    _log( AP_PASSWORD );
    Serial.println( WiFi.softAPIP() );
  } 
  

  //Initialize Wi-Fi network connection if the credentials are not empty
  if ( strlen(NC_SSID) > 0 && strlen(NC_PASSWORD) > 0 ) {
    // Connect to Wi-Fi network with SSID and password
    WiFi.begin(NC_SSID, NC_PASSWORD);
    _log("Connecting to:");
    _log( NC_SSID );
    // Wait for the network connection
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      if (DEBUG) { Serial.print("."); }
    }
    
    _log( "Wifi network data :" );
    _log( NC_SSID );
    _log( NC_PASSWORD );
    Serial.print( WiFi.localIP() );
  }

  // Start the server
  server.begin();
}

/*
* Loop function
* Executes main functionality endlessly
*/
void loop() {
  // Listen for incoming clients
  WiFiClient client = server.available();

  // When a client is connected
  if (client) {
    // String to hold incoming data from the client
    String currentLine = "";
    currentTime = millis();
    previousTime = currentTime;
    // Loop while the client's connected and the connection has not timed out
    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();
      if (client.available()) {
        // if there's bytes to read from the client,
        // read a byte, then
        char clientByte = client.read();
        header += clientByte;
        if (clientByte == '\n') {
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0 ) {
            // TODO: parse header to get URL
              // TODO: validate route
              // TODO: get params from URL
              // Example:
              
              // GET / HTTP/1.1
              // GET /test/123 HTTP/1.1
              // GET /?value=123 HTTP/1.1
              // GET /api/test HTTP/1.1
              
              // Host: 192.168.0.103
              // Connection: keep-alive
              // Cache-Control: no-cache
              // User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/100.0.4896.75 Safari/537.36
              // Postman-Token: c7fad9ba-35fc-2ac8-b7b8-dc068ab0e104
              // Accept: */*
              // Accept-Encoding: gzip, deflate
              // Accept-Language: en-US,en;q=0.9,bg;q=0.8,la;q=0.7

              String response = "";
              String ContentType = "";
              // Serial.println( header );
              // Serial.println( header.indexOf('GET /api/') >= 0 );
              // if ( header.indexOf('GET /api/') >= 0 ) {
              //   ContentType = TYPE_JSON;
              //   response = buildJSONResponse( 1, "test" );
              // }
              // else {
                ContentType = TYPE_HTML;
                response = buildWebPage( );
                response.replace(HTML_DATA_REPLACE,header);
              // }
              
              respond( client, HTTP_OK, ContentType );            
              client.println(response);
              break;
          } else {
            // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (clientByte != '\r') {
          // if you got anything else but a carriage return character,
          // add it to the end of the currentLine
          currentLine += clientByte;
        }
      }
    }
    
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    _log( "Client disconnected.");
  }
}

/*
* Parse 
*/

/*
* HTTP Status response
* @param WiFiClient client - currently connected client
* @param String STATUS - HTTP response status code
* @param String CONTENT_TYPE - response content type
*/
void respond ( WiFiClient client, String STATUS, String CONTENT_TYPE ) {
  client.println(STATUS);
  client.println("Content-type:"+CONTENT_TYPE);
  client.println("Connection: close");
  client.println();
}

/*
* Generate JSON response for API calls
* @return String jsonString - Stringified JSON object
*/
String buildJSONResponse ( int customInt, String customString ) {
  String jsonString = "{";
  jsonString += "\"int\":";
  jsonString += customInt;
  jsonString += ",";
  jsonString += "\"string\":\"";
  jsonString += customString;
  jsonString += "\",";
  jsonString += "\"rand\":";
  jsonString += random(300);
  jsonString += "}";
  return jsonString;
}

/*
* Generate web page function
* @return String webPage - generated webpage to be displayed
*/
String buildWebPage ( ) {
  // Begin webpage
  String webPage = "";
  webPage += "<!DOCTYPE html><html>";
  webPage += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  webPage += "<title>"+PROJECT_NAME+"</title>";
  webPage += "<link rel=\"icon\" href=\"data:,\">";

  // Add CSS styingls
  webPage += getCSS( );
  
  // Add JavaScript functionality
  webPage += getJavaScript( );
  
  // Close head tag
  webPage += "</head>";

  // Get main web page content
  webPage += getHTMLBody( );

  // Close HTML tag
  webPage += "</html>"; 

  return webPage;
}

/*
* Get webpage CSS
* @return String styles - webpage CSS styling
*/
String getCSS ( ) {
  String styles = "<style type='text/css'>";
  styles += "* { font-falimy:'Arial'; color:#0f0; background-color:#000; }";
  styles += "</style>";
  return styles;
}

/*
* Get webpage JavaScript
* @return String javaScript - webpage JS functionality
*/
String getJavaScript ( ) {
  String javaScript = "<script type='text/javascript'>";
  // Set IPs as const
  javaScript += "const AP_IP='";
  javaScript += WiFi.softAPIP().toString();
  javaScript += "';";
  javaScript += "const NC_IP='";
  javaScript += WiFi.localIP().toString();
  javaScript += "';";
  javaScript += "function fetchData ( endpoint, data ) { ";
  javaScript += "console.log(`ap_ip: ${AP_IP} | nc_ip: ${NC_IP} | ${endpoint} | ${data}`); ";
  javaScript += " }";
  javaScript += "console.log('"+PROJECT_NAME+"')";

  javaScript += "</script>";
  return javaScript;
}

/*
* Get webpage html body content
* @return String body - webpage body content
*/
String getHTMLBody ( ) {
  String body = "";
  body += "<body>";
  body += "<h1>"+PROJECT_NAME+"</h1>";
  body += "<button onclick='fetchData( `/api`, `movement=forward` )'> Fetch data </button> <br>";
  body += HTML_DATA_REPLACE;
  body += "</body>";
  return body;
}

/*
* Pring log function
* Will print line in the serial monitor if module DEBUG mode
* @param message - String message to be displayed
*/
void _log ( String message ) {
  if ( DEBUG ) {
    Serial.println( message );
  }
}
