#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>

ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'

ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <style type="text/css">
            * {
                padding: 0;
                margin:0;
                background:#000;
                color:#0f0;
            }
            #response {
                float:left;
                width:100%;
                height:100px;
                font-size: 1.5em;
                text-align: center;
                padding: 50px 0;
            }
            #controller {
                float: left;
                width: 100%;
                height: 50%;
                font-size: 1.5em;
            }
                .row {
                    float: left;
                    width: 100%;
                    height: 100px;
                }
                button, .spacer {
                    float: left;
                    width:33%;
                    height:100%;
                    font-size: 2em;
                }
                button {
                    border:1px solid #0f0
                }
        </style>
        <script type="text/javascript">
            function execute ( event, url ) {
                event.preventDefault( );
                document.getElementById("response").innerHTML = "Request sent";
                fetch(url)
                .then(response => response.json())
                .then(data =>
                    document.getElementById("response").innerHTML = `${data.response}`
                ).catch( error => 
                    document.getElementById("response").innerHTML = "Request failed"
                );
            }
        </script>
    </head>
    <body>
        <div id="response"> Initial response message </div>
        <div id="controller">
            <div class="row">
                <span class="spacer"></span>
                <button
                    onmousedown="execute( event, 'api/forward')" 
                    onmouseup="execute( event, 'api/stop')" 
                    ontouchstart="execute( event, 'api/forward')" 
                    ontouchend="execute( event, 'api/stop')"
                >
                    &#11165;
                </button>
                <span class="spacer"></span>
            </div>
            <div class="row">
                <button
                    onmousedown="execute( event, 'api/left')"
                    onmouseup="execute( event, 'api/stop')" 
                    ontouchstart="execute( event, 'api/left')"
                    ontouchend="execute( event, 'api/stop')"
                >
                    &#11164;
                </button>
                <span class="spacer"></span>
                <button
                    onmousedown="execute( event, 'api/right')"
                    onmouseup="execute( event, 'api/stop')" 
                    ontouchstart="execute( event, 'api/right')"
                    ontouchend="execute( event, 'api/stop')"
                >
                    &#11166;
                </button>
            </div>
            <div class="row">
                <span class="spacer"></span>
                <button
                    onmousedown="execute( event, 'api/back')"
                    onmouseup="execute( event, 'api/stop')" 
                    ontouchstart="execute( event, 'api/back')"
                    ontouchend="execute( event, 'api/stop')"
                >
                    &#11167;
                </button>
                <span class="spacer"></span>
            </div>
        </div>
    </body>
</html>
)rawliteral";


// Motor pins
const int LeftMotorPOS = 16;
const int LeftMotorNEG = 14;
const int RightMotorPOS = 12;
const int RightMotorNEG = 13;
const int GPIO2 = 2;

// function prototypes for HTTP handlers
void handleRoot();
void handleNotFound();
void handleMoveForward();
void handleMoveLeft();
void handleMoveRight();
void handleMoveBack();
void handleStop();

void setup(void){
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');

  pinMode(LeftMotorPOS,OUTPUT);
  pinMode(LeftMotorNEG,OUTPUT);
  pinMode(RightMotorPOS,OUTPUT);
  pinMode(RightMotorNEG,OUTPUT);
  pinMode(GPIO2, OUTPUT);

  // Soft access point
  WiFi.softAP("Katyuska", "");
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  // Standart connection
  // wifiMulti.addAP("Marasha crew ", "P@r+!bo!69/ke+");   // add Wi-Fi networks you want to connect to
  // Serial.println("Connecting ...");
  // int i = 0;
  // while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
  //   delay(250);
  //   Serial.print('.');
  // }
  // Serial.println('\n');
  // Serial.print("Connected to ");
  // Serial.println(WiFi.SSID());              // Tell us what network we're connected to
  // Serial.print("IP address:\t");
  // Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer

  if (MDNS.begin("esp8266")) {              // Start the mDNS responder for esp8266.local
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }

  server.on("/", HTTP_GET, handleRoot);     // Call the 'handleRoot' function when a client requests URI "/"
  server.onNotFound(handleNotFound);        // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"
  server.on("/api/forward", HTTP_GET, handleMoveForward);
  server.on("/api/left", HTTP_GET, handleMoveLeft);
  server.on("/api/right", HTTP_GET, handleMoveRight);
  server.on("/api/back", HTTP_GET, handleMoveBack);
  server.on("/api/stop", HTTP_GET, handleStop);
  server.begin();                           // Actually start the server
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();                    // Listen for HTTP requests from clients
}

void handleRoot() {                         // When URI / is requested, send a web page with a button to toggle the LED
  server.send(200, "text/html", index_html);
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}

void move ( bool leftMotorDefault, bool RightMotorDefault, bool Stop ) {
  if ( Stop ) {    
    digitalWrite(LeftMotorPOS,LOW);
    digitalWrite(LeftMotorNEG,LOW);
    digitalWrite(RightMotorPOS,LOW);
    digitalWrite(RightMotorNEG,LOW);
    return;
  }
  if ( leftMotorDefault ) {
    digitalWrite(LeftMotorPOS,HIGH);
    digitalWrite(LeftMotorNEG,LOW);
  } else if ( !leftMotorDefault ) {
    digitalWrite(LeftMotorPOS,LOW);
    digitalWrite(LeftMotorNEG,HIGH);
  }

  if ( RightMotorDefault ) {
    digitalWrite(RightMotorPOS,HIGH);
    digitalWrite(RightMotorNEG,LOW);
  } else if ( !RightMotorDefault ) {
    digitalWrite(RightMotorPOS,LOW);
    digitalWrite(RightMotorNEG,HIGH);
  }

}

void handleMoveForward ( ) {
  move(false, true, false);
  server.send(200, "application/json", toJSON("Move: Forward"));
}
void handleMoveLeft ( ) {
  move(false, true, false);
  server.send(200, "application/json", toJSON("Move: Left"));
}
void handleMoveRight ( ) {
  move(true, false, false);
}
void handleMoveBack ( ) {
  move(false, false, false);
  server.send(200, "application/json", toJSON("Move: Back"));
}
void handleStop ( ) {
  move(true, true, true);
  server.send(200, "application/json", toJSON("Stopped"));
}

String toJSON ( String response ) {
  return "{\"response\":\""+response+"\"}";
}