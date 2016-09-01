#include <ESP8266WiFi.h>
#include <MQTTClient.h>

const int buttonPin = 4;     // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status
int calibrationTime = 30;        
int pirPin = 5;    //the digital pin connected to the PIRsensor's output
int pirState = 0;
int ledPin = D0;
int toggle = 0;
const char *ssid = "T-Mobile Broadband08";
const char *pass = "21485008";

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;

void connect(); // <- predefine connect() for setup()

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  client.begin("192.168.0.142", net); // IP address of my laptop, may change everytime. Or better, the mqtt server can go here.

  connect();
  pinMode(buttonPin, INPUT);
   pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(pirPin, LOW);

  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
    delay(50);
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
buttonState = digitalRead(buttonPin);

pirState = digitalRead(pirPin);
if (pirState == HIGH) {
    digitalWrite(ledPin, LOW);   //the led visualizes the sensors output pin state
    client.publish("croom", "4");
    Serial.println("motion detected!!");
    delay(1000);
    pirState = digitalRead(pirPin);
   }else {       
    digitalWrite(ledPin, HIGH);  //the led visualizes the sensors output pin stat
    client.publish("croom", "0");
    Serial.println("motion ended");
    delay(1000);
    pirState = digitalRead(pirPin);
   }
}

void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
  Serial.print("incoming: ");
  Serial.print(topic);
  Serial.print(" - ");
  Serial.print(payload);
  Serial.println();
}
