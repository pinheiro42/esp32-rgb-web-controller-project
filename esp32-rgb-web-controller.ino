//Libraries
#include <WiFi.h>
#include <WebServer.h>
#include <driver/ledc.h>

const char* ssid = "your-wifi-name";
const char* password = "your-wifi-password";

WebServer server(80);

const int redPin = 23;
const int greenPin = 22;
const int bluePin = 21;

const int redChannel = 0;
const int greenChannel = 1;
const int blueChannel = 2;

const int pwmFreq = 5000;
const int pwmResolution = 8; 

String htmlPage = R"rawliteral(<!DOCTYPE html>
<html>
  <head>
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 Led Control</title>
    <link href="https://fonts.googleapis.com/css2?family=Bebas+Neue&display=swap" rel="stylesheet">
    <style>
    	.title{text-align:center; font-family: 'Bebas Neue', sans-serif; margin-bottom:1px; border-style: solid; margin-right: 20%; margin-left: 20%; border-radius: 4vw; font-size: 5vw} 
    	.container{display: grid; justify-items: center;}
    	button{margin-top: 3%; font-size: 5vw; width: 50%; border-radius: 4vw; font-family: 'Bebas Neue', sans-serif;}
        .off{background-color: black; color: white;}
        .blue{background-color: blue; color: white;}
        .red{background-color: red; color: white;}
        .green{background-color: green; color: white;}
        .yellow{background-color: yellow; color: black;}
        .cyan{background-color: cyan; color: white;}
        .purple{background-color: purple; color: white;}
        .white{background-color: white; color: black;}
        body{background-color: #363636}
    </style>
  </head>
  <body>
    <h1 class="title" >ESP32 LED Control</h1>
    <div class="container">
      <button class="blue" onclick="toggleLED('blue')">BLUE</button>
      <button class="red" onclick="toggleLED('red')">RED</button>
      <button class="green" onclick="toggleLED('green')">GREEN</button>
      <button class="yellow" onclick="toggleLED('yellow')">YELLOW</button>
      <button class="cyan" onclick="toggleLED('cyan')">CYAN</button>
      <button class="purple" onclick="toggleLED('purple')">PURPLE</button>
      <button class="white" onclick="toggleLED('white')">WHITE</button>
      <button class="off" onclick="toggleLED('off')">Turn OFF</button>
    </div>
    <script>
      function toggleLED(state)
      {
        fetch('/led/'+ state)
          .then(response =>response.text())
          .then(data => console.log(data))
          .catch(err => console.error(err));
      }
    </script>
  </body>
</html>
)rawliteral";

void handleRoot(){
  server.send(200, "text/html", htmlPage);
}

void handleLEDOn(){
  ledcWrite(redChannel, 255);
  ledcWrite(greenChannel, 255);
  ledcWrite(blueChannel, 255);
  server.send(200, "text/plain", "LED is ON");
}

void handleLEDWhite(){
  ledcWrite(redChannel, 255);
  ledcWrite(greenChannel, 255);
  ledcWrite(blueChannel, 255);
  server.send(200, "text/plain", "LED is WHITE");
}

void handleLEDRed(){
  ledcWrite(redChannel, 255);
  ledcWrite(greenChannel, 0);
  ledcWrite(blueChannel, 0);
  server.send(200, "text/plain", "LED is RED");
}

void handleLEDGreen(){
  ledcWrite(redChannel, 0);
  ledcWrite(greenChannel, 255);
  ledcWrite(blueChannel, 0);
  server.send(200, "text/plain", "LED is GREEN");
}

void handleLEDBlue(){
  ledcWrite(redChannel, 0);
  ledcWrite(greenChannel, 0);
  ledcWrite(blueChannel, 255);
  server.send(200, "text/plain", "LED is BLUE");
}

void handleLEDYellow(){
  ledcWrite(redChannel, 255);
  ledcWrite(greenChannel, 255);
  ledcWrite(blueChannel, 0);
  server.send(200, "text/plain", "LED is YELLOW");
}

void handleLEDPurple(){
  ledcWrite(redChannel, 255);
  ledcWrite(greenChannel, 0);
  ledcWrite(blueChannel, 240);
  server.send(200, "text/plain", "LED is PURPLE");
}

void handleLEDCyan(){
  ledcWrite(redChannel, 0);
  ledcWrite(greenChannel, 255);
  ledcWrite(blueChannel, 180);
  server.send(200, "text/plain", "LED is CYAN");
}

void handleLEDOff(){
  ledcWrite(redChannel, 0);
  ledcWrite(greenChannel, 0);
  ledcWrite(blueChannel, 0);
  server.send(200, "text/plain", "LED is OFF");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print("Hello Sir");
  delay(1000);

  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    
    delay(100);
    Serial.println("Connecting...");
  }
  Serial.print("Connected to Wi-Fi network name ");
  Serial.println(ssid);
  Serial.print("IP Adress: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/led/on", handleLEDOn);
  server.on("/led/off", handleLEDOff);
  server.on("/led/red", handleLEDRed);
  server.on("/led/green", handleLEDGreen);
  server.on("/led/blue", handleLEDBlue);
  server.on("/led/yellow", handleLEDYellow);
  server.on("/led/purple", handleLEDPurple);
  server.on("/led/cyan", handleLEDCyan);
  server.on("/led/white", handleLEDWhite);
  server.begin();
  Serial.println("HTTP server is online.");

  ledcSetup(redChannel, pwmFreq, pwmResolution);
  ledcSetup(greenChannel, pwmFreq, pwmResolution);
  ledcSetup(blueChannel, pwmFreq, pwmResolution);

  ledcAttachPin(redPin, redChannel);
  ledcAttachPin(greenPin, greenChannel);
  ledcAttachPin(bluePin, blueChannel);

  ledcWrite(redChannel, 0);
  ledcWrite(greenChannel, 0);
  ledcWrite(blueChannel, 0);

  delay(500);
}

void loop() {
  server.handleClient();
}