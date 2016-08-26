#include <ESP8266WiFi.h>
#include <MQTTClient.h>

int trigPin = 4;
int echoPin = 5;
const int ledPin = D0;
const char *ssid = "T-Mobile Broadband08";
const char *pass = "21485008";
int count = 1;

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;

void connect(); // <- predefine connect() for setup()

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  client.begin("192.168.0.142", net); // IP address of my laptop, may change everytime. Or better, the mqtt server can go here.

  connect();
}

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("arduino", "try", "try")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

//  client.subscribe("sensor");
  // client.unsubscribe("/example");
}

void loop() {
  client.loop();
  delay(10); // <- fixes some issues with WiFi stability

  if(!client.connected()) {
    connect();
  } 

//USS code
long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 30){
    count++;
    delay(3000);
  }

  if (count%2 == 0){
    Serial.println("In use");
    client.publish("mens", "3"); 
    digitalWrite(ledPin, LOW);
//    delay(3000);
  }else{
    Serial.println("Not in use");
    client.publish("mens", "0"); 
    digitalWrite(ledPin, HIGH);
  }

  if (count == 100){
    count=1;
  }
  delay(200);
}

void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
  Serial.print("incoming: ");
  Serial.print(topic);
  Serial.print(" - ");
  Serial.print(payload);
  Serial.println();
}
