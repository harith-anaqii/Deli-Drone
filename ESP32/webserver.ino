#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

WebServer server(80);

void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  // Set up route for serving HTML file
  server.on("/", HTTP_GET, handleRoot);
  
  // Start server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  // Read the HTML file
  File file = SPIFFS.open("delidronefcb.html", "r");
  
  // Check if the file opened successfully
  if (!file) {
    Serial.println("Failed to open file");
    return;
  }
  
  // Read the file contents
  String htmlContent = "";
  while (file.available()) {
    htmlContent += file.readStringUntil('\n');
  }
  
  // Close the file
  file.close();
  
  // Send the HTML content as the response
  server.send(200, "text/html", htmlContent);
}