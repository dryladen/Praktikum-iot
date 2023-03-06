#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "ssid-wifi";
const char* password = "ssid-password";
const int relay_pin = 16; // pin D0

ESP8266WebServer server(80); // Port untuk web server

String webpage;
void setup() {
  Serial.begin(9600);
  delay(1000);
  pinMode(relay_pin, OUTPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi.");
  Serial.println(WiFi.localIP());

  webpage += "<h1> Web Control LED ESP8266</h1>";
  webpage += "LED : ";
  webpage += "<a href=\"LED-ON\"\"><button>ON</button></a><a href=\"LED-OFF\"\"><button>OFF</button></a><br>";

  server.on("/", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(relay_pin, LOW);
  });
  server.on("/LED-ON", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(relay_pin, LOW);
  });
  server.on("/LED-OFF", []() {
    server.send(200, "text/html", webpage);
    digitalWrite(relay_pin, HIGH);
  });
  server.begin(); // Memulai web server
}

void loop() {
  server.handleClient(); // Menangani permintaan dari klien
}