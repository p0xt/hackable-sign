#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>



// LED Matrix Display configuration
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 15



MD_Parola Display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// Default text displayed
String text = "HACK THE PLANET!!!";

// WiFi credentials for accessing the web server
const char* http_username = "admin";
const char* http_password = "31337";



ESP8266WebServer server(80);

// WiFi network settings for the Access Point (AP) mode
IPAddress local_IP(192, 168, 4, 22);
IPAddress gateway(192, 168, 4, 9);
IPAddress subnet(255, 255, 255, 0);


// Track the number of unique connections since last reset
int unique_connections = 0; 
bool new_device_connected = false;

// Track the unique MAC addresses of connected clients
const int max_clients = 10;
String unique_macs[max_clients];
int num_unique_macs = 0;



// Function to check for new device connections and update the unique connections count
void checkForNewConnections() {
  int current_clients = WiFi.softAPgetStationNum();

  // Check if there's a new device connection and update the unique_connections count
  if (current_clients > num_unique_macs) {
    new_device_connected = true;
    unique_connections++;
    num_unique_macs = current_clients;
  }
}



// Setup function runs once on device startup
void setup() {
  const char* ssid = "ESP-CTF"; // WiFi network name (SSID)
  const int max_connections = 2; // Maximum number of simultaneous connections

  // Set the ESP8266 in Access Point (AP) mode
  // WiFi.softAP(ssid, passwd); // If you'd like to include a password for the AP

  // Initialize Serial communication for debugging
  Serial.begin(9600);
  Serial.println();

  // Configure the Access Point settings
  Serial.print("Setting soft-AP configuration ... ");
  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");

  // Start the Access Point
  Serial.print("Setting soft-AP ... ");
  Serial.println(WiFi.softAP(ssid) ? "Ready" : "Failed!");

  // Print the Access Point IP address to the Serial Monitor
  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP());

  // Initialize LED matrix display
  Display.begin();
  Display.setIntensity(0);
  Display.displayClear();
  Display.displayScroll(text.c_str(), PA_RIGHT, PA_SCROLL_LEFT, 50);


  // ROUTES:

  // Route for serving the website homepage
  server.on("/", handleRoot);

  // Route for opening submission form to change text
  server.on("/matrixform", HTTP_GET, handleMatrixForm);

  // Route for displaying the text changed page
  server.on("/changetext", HTTP_POST, handleChangeText);

  // Start the web server
  server.begin();

}



// Loop function runs repeatedly after setup
void loop() {

  // Check for new device connections and update the unique connections count
  checkForNewConnections();

  // Handle incoming client requests
  server.handleClient();

  // If the LED matrix animation is finished, reset it
  if (Display.displayAnimate()) {
    Display.displayReset();
  }
}



// Handler for the root page
void handleRoot() {

  // Get the current number of connected clients
  int current_clients = WiFi.softAPgetStationNum();

  // Check if there's a new device connection and update the unique_connections count
  if (new_device_connected) {
    new_device_connected = false;
    unique_connections++;
  }

  String webpage = "<html><body>";
  webpage += "<h1>Welcome, friend :)</h1>";
  webpage += "<p>Click <a href='/matrixform'>here</a> to submit newtext to the matrix display.</p>";
  webpage += "<p>Number of unique connections since last reset: " + String(unique_connections) + "</p>";
  webpage += "<p>Current number of connections: " + String(current_clients) + "</p>";
  webpage += "<!-- routes: /matrixform /changetext -->";
  webpage += "</body></html>";

  // Send the HTML page as the response
  server.send(200, "text/html", webpage);
}



// Handler for the matrix submission form page
void handleMatrixForm() {
  // Check for authentication, and send an authentication request if user hasn't authenticated
  if (!server.authenticate(http_username, http_password)) {
    return server.requestAuthentication();
  }

  String webpage = "<html><body>";
  webpage += "<h1>Submit your text below to show it on the matrix display:</h1>";
  webpage += "<form action='/changetext' method='post'>"; 
  webpage += "New Text: <input type='text' name='newtext'>";
  webpage += "<input type='submit' value='Change'>";
  webpage += "</form></body></html>";

  // Send the HTML page as the response
  server.send(200, "text/html", webpage);
}



// Handler for changing the text on the LED matrix
void handleChangeText() {
  String webpage;
  
  // Check if the 'newtext' parameter is present in the POST request
  if (server.hasArg("newtext")) {
    text = server.arg("newtext"); // Get the new text from the POST request
    Display.displayClear(); // Clear the display
    Display.displayScroll(text.c_str(), PA_RIGHT, PA_SCROLL_LEFT, 50); // Scroll the new text
    webpage = "<html><body>";
    webpage += "<h1>Text Changed Successfully!</h1>";
    webpage += "<p>Click <a href='/matrixform'>here</a> to submit another text.</p>";
    webpage += "</body></html>";
  } else {
    // If 'newtext' parameter is missing, show an error message
    webpage = "<html><body>";
    webpage += "<h1>Error: No text provided.</h1>";
    webpage += "<p>Click <a href='/matrixform'>here</a> to go back and submit a text.</p>";
    webpage += "</body></html>";
  }

  // Send the HTML page as the response
  server.send(200, "text/html", webpage);
}

