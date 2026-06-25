#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials
const char* ssid = "Galaxy M214BA4";
const char* password = "123412346790";

// Define the LED pin (GPIO 2 is usually the onboard LED on most ESP32 boards)
const int ledPin = 2; 

// Create a web server object that listens for HTTP requests on port 80
WebServer server(80);

// HTML page to serve to the phone's browser
String getHTML() {
  String html = "<!DOCTYPE html><html>";
  html += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  html += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}";
  html += ".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;";
  html += "text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}";
  html += ".button2 {background-color: #f44336;}</style></head>";
  
  html += "<body><h1>ESP32 LED Controller</h1>";
  
  // Display current state of the LED and the corresponding button
  if (digitalRead(ledPin) == HIGH) {
    html += "<p>LED State: <strong>ON</strong></p>";
    html += "<p><a href=\"/led/off\"><button class=\"button button2\">Turn OFF</button></a></p>";
  } else {
    html += "<p>LED State: <strong>OFF</strong></p>";
    html += "<p><a href=\"/led/on\"><button class=\"button\">Turn ON</button></a></p>";
  }
  
  html += "</body></html>";
  return html;
}

// Handle root URL (/)
void handleRoot() {
  server.send(200, "text/html", getHTML());
}

// Handle turning LED ON
void handleLEDOn() {
  digitalWrite(ledPin, HIGH);
  server.send(200, "text/html", getHTML());
}

// Handle turning LED OFF
void handleLEDOff() {
  digitalWrite(ledPin, LOW);
  server.send(200, "text/html", getHTML());
}

void setup() {
  Serial.begin(115200);
  
  // Initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Start with LED off

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  // Print local IP address
  Serial.println("");
  Serial.println("Wi-Fi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Define routing
  server.on("/", handleRoot);
  server.on("/led/on", handleLEDOn);
  server.on("/led/off", handleLEDOff);

  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}