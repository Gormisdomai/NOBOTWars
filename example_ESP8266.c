#include <ESP8266WiFi.h>

// see https://www.instructables.com/Programming-a-HTTP-Server-on-ESP-8266-12E/


WiFiServer server(80); //Initialize the server on Port 80

void setup() {

  WiFi.mode(WIFI_AP); //Our ESP8266-12E is an AccessPoint
  WiFi.softAP("Hello_IoT", "12345678"); // Provide the (SSID, password); .
  server.begin(); // Start the HTTP Server
  
  //Looking under the hood
  Serial.begin(115200); //Start communication between the ESP8266-12E and the monitor window
  IPAddress HTTPS_ServerIP= WiFi.softAPIP(); // Obtain the IP of the Server
  Serial.print("Server IP is: "); // Print the IP to the monitor window
  Serial.println(HTTPS_ServerIP);

}

void loop() {

  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  //Looking under the hood
  Serial.println("Somebody has connected :)");
  //Read what the browser has sent into a String class and print the request to the monitor
  String request = client.readString();
  //Looking under the hood
  Serial.println(request);

  // Handle the Request

  if (request.indexOf("/OFF") != -1){
    Serial.println("OFF signal recieved");
  }

  else if (request.indexOf("/ON") != -1){
    Serial.println("ON signal recieved");
  }

  s = "HTML page goes here"

  client.flush(); //clear previous info in the stream
  client.print(s); // Send the response to the client
  delay(1);
  Serial.println("Client disonnected"); //Looking under the hood
}
