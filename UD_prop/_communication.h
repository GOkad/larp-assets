/**
 * ESP-NOW Communication handlers
 */
   
  /**
   * @brief ESP-NOW definitions and variables
   */
  // Device role: CONTROLLER, SLAVE, COMBO
  #define MY_ROLE         ESP_NOW_ROLE_COMBO
  // Receiver role
  #define RECEIVER_ROLE   ESP_NOW_ROLE_COMBO
  #define WIFI_CHANNEL    1
  #define MY_NAME         "UD_ASSET"
  // TODO: Add list of receivers or dynamically change peers 
  uint8_t receiverAddress[] = {0xBC, 0xDD, 0xC2, 0xBA, 0xFC, 0x76};   // SENSOR MAC
  // Main data packet model
  struct __attribute__((packed)) dataPacket {
    int sensor1;
    int sensor2;
    float sensor3;
  };

  /**
   * @brief Transmition Complete handler
   * Executed when the data transmition is completed
   * 
   * @param receiver_mac - MAC address of the receiver
   * @param transmissionStatus - Transmition status
   */
  void transmissionComplete(uint8_t *receiver_mac, uint8_t transmissionStatus) {
    
    if(transmissionStatus == 0) {
      // TODO: Handler send data successfully
      Serial.println("Data sent successfully");
    }
    else {
      // TODO: Handle send data error
      Serial.print("Error code: ");
      Serial.println(transmissionStatus);
    }

  }

  /**
   * @brief Data received handler
   * Executed when data was received
   * 
   * @param senderMac - MAC address of the sender
   * @param data - Received data packet
   * @param dataLength - Length of the data packet
   */
  void dataReceived(uint8_t *senderMac, uint8_t *data, uint8_t dataLength) {
    // Parse mac address to string
    char macStr[18];  
    snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x", senderMac[0], senderMac[1], senderMac[2], senderMac[3], senderMac[4], senderMac[5]);
    Serial.println();
    Serial.print("Received data from: ");
    Serial.println(macStr);
    
    // Parse data packet
    dataPacket packet;
    memcpy(&packet, data, sizeof(packet));
    
    Serial.print("sensor1: ");
    Serial.println(packet.sensor1);
    Serial.print("sensor2: ");
    Serial.println(packet.sensor2);
    Serial.print("sensor3: ");
    Serial.println(packet.sensor3);
  }

  /**
   * @brief ESP-NOW communication setup
   * 
   * @return true - Setup is successful
   * @return false - There was an error
   */
  bool comm_setup ( ) {
    // Setup WiFi mode
    WiFi.mode(WIFI_STA);

    // We do not want to connect to a WiFi network
    WiFi.disconnect();

    // Return false if ESP-NOW initialization failes
    if( esp_now_init() != 0 ) {
      // TODO: Add led error handler
      Serial.println("ESP-NOW initialization failed");
      return false;
    }

    // Set device role
    esp_now_set_self_role(MY_ROLE);
    
    // Register callback on completed transmition
    esp_now_register_send_cb(transmissionComplete);
    
    // Register callback when data is received
    esp_now_register_recv_cb(dataReceived);   
    
    // Add ESP-NOW peers
    // TODO: add peers from list of peers
    // and check for dinamically changing peers
    esp_now_add_peer(
      receiverAddress,
      RECEIVER_ROLE,
      WIFI_CHANNEL,
      NULL,
      0
    );

    Serial.println("Initialized.");
    return true;
  }
