#include <ESP8266WiFi.h>
#include <MQTTClient.h>

int buttonPin = 4;     // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status
int ledPin =  D0;  

const char *ssid = "T-Mobile Broadband08";
const char *pass = "21485008";

WiFiClient net;
MQTTClient client;

void connect(); // <- predefine connect() for setup()

void setup() {   
                
  Serial.begin(9600);
  
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  
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

//  client.subscribe("hammock");
  // client.unsubscribe("/example");
}

void loop() {
  client.loop();
  delay(10); // <- fixes some issues with WiFi stability

  if(!client.connected()) {
    connect();
  } 
  buttonState = digitalRead(buttonPin);
  
  // look for button strikes
  if (buttonState == HIGH) {
    client.publish("couch", "2");
    Serial.println("button hit!!");
    digitalWrite(ledPin, LOW);
    Serial.println("light on");
    delay(1000);
  } else {
      // turn LED off:
      client.publish("couch", "0");
      digitalWrite(ledPin, HIGH);
      Serial.println("light off");
      delay(1000);
  }

}

void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
  Serial.print("incoming: ");
  Serial.print(topic);
  Serial.print(" - ");
  Serial.print(payload);
  Serial.println();
}
