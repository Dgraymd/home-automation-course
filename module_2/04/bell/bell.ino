// Import required libraries
#include "ESP8266WiFi.h"
#include <aREST.h>

// Create aREST instance
aREST rest = aREST();

// WiFi parameters
const char* ssid = "your-wifi-name";
const char* password = "your-wifi-pass";

// The port to listen for incoming TCP connections 
#define LISTEN_PORT           80

// Create an instance of the server
WiFiServer server(LISTEN_PORT);

// Function
int bellControl(String message);

void setup(void)
{  
  // Start Serial
  Serial.begin(115200);
 
  // Give name and ID to device
  rest.set_id("1");
  rest.set_name("bell");

  // Bell
  rest.function("bell",bellControl);
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
  
  // Print the IP address
  Serial.println(WiFi.localIP());

  // Set pin as output
  pinMode(5, OUTPUT);
  
}

void loop() {
  
  // Handle REST calls
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while(!client.available()){
    delay(1);
  }
  rest.handle(client);
 
}

int bellControl(String command) {
 
  tone(14, 660);
  delay(700);
  tone(14, 550);
  delay(700);
  tone(14, 440);
  delay(700);
  noTone(14);
  
  return 1;
}
