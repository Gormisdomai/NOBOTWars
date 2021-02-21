/* 
 * library for the Nobot's wifi interface
*/

#include <ESP8266WiFi.h>

#define CONNECTION_TIMEOUT (500)

WiFiServer server(80); //Initialize the server on Port 80

/*
 * spins up a wifi server
 */
void init_wifi_server() {
  
  // Comment/uncomment this code to run in soft AP mode
  WiFi.mode(WIFI_AP); //Our ESP8266-12E is an AccessPoint
  WiFi.softAP("I AM NOBO", "12345678"); // Provide the (SSID, password); .
  IPAddress HTTPS_ServerIP= WiFi.softAPIP(); // Obtain the IP of the Server

  // Comment/uncomment this code to run in client mode
  /*
  WiFi.begin("<YOUR WIFI NAME>", "<YOUR WIFI PASSWORD>");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  IPAddress HTTPS_ServerIP = WiFi.localIP();
  */
  server.begin(); // Start the HTTP Server
  
  Serial.print("Server IP is: "); // Print the IP to the monitor window
  Serial.println(HTTPS_ServerIP);
}

/*
 * reads serve a webpage and returns 'f' if the path was /ON! and 'c' if it was /OFF!
 * this method should be caled in the main loop of the program
*/
char wifi_server_loop()
{
  WiFiClient client = server.available();
  if (!client) {
    return '_';
  }

  Serial.println("Somebody has connected :)");

  //Close the connection after a timemout to handle if the packet is dropped https://forum.arduino.cc/index.php?topic=480572.0
  long startTime = millis();
  while(!client.available()){
    if (millis() > startTime + CONNECTION_TIMEOUT) return '_';
  }

  Serial.println("Client is available");

  char command; //this will be the value we return
  
  //Read what the browser has sent into a String class and print the request to the monitor
  //Read until an explicit character (!), otherwise it will hang waiting for a null character until timeout, see: https://forum.arduino.cc/index.php?topic=529440.30
  client.flush();
  String request = client.readStringUntil('!');

  
  Serial.println("Printing request");
  Serial.println(request);

  // Handle the Request
  String s = "";

  if (request.indexOf("/OFF") != -1){
    Serial.println("OFF signal recieved"); 
    s = "<h1><a href='/ON!'>click here to turn ON! </a></h1>";
    command = 'c';
  }

  else if (request.indexOf("/ON") != -1){
    Serial.println("ON signal recieved");
    
    s = "<h1><a href='/OFF!'>click here to turn OFF! </a></h1>";
    command = 'f';
  }


  client.flush(); //clear previous info in the stream
  client.print(s); // Send the response to the client
  client.print("\n");
  //TODO you can also print any variables you like, e.g. the battery
  //client.print(battery_percentage);
  Serial.println("Client disonnected");

  return command;
}
