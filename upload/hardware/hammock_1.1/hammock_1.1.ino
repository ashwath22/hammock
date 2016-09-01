// Sensor pin - GND
// Sensor pin - Analog In 0, with 10K resistor to +5V


#include <ESP8266WiFi.h>
#include <MQTTClient.h>

int sensorPin = A0;    // Sensor connected to analog pin A0
int ledPin =  D0;  
int before = 0; 
const char *ssid = "T-Mobile Broadband08";
const char *pass = "21485008";

WiFiClient net;
MQTTClient client;

void connect(); // <- predefine connect() for setup()
 
void setup()
{
  // initialize serial communications
  Serial.begin(9600); 

  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(sensorPin, INPUT);
//  
  WiFi.begin(ssid, pass);
  client.begin("192.168.0.142", net); // IP address of my laptop, may change everytime. Or better, the mqtt server can go here.

  connect();
  int sensor = analogRead(sensorPin);
  before = sensor;
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
 
void loop()
{
   client.loop();
   delay(10); // <- fixes some issues with WiFi stability
//    
    // read the voltage from the voltage divider (sensor plus resistor)
    int sensor = analogRead(sensorPin);
    Serial.println(sensor);
    if( sensor <= before && sensor < 56){
      client.publish("hammock", "0");
      Serial.println("Hammock not in use");
      digitalWrite(ledPin, HIGH);
      Serial.println("light off");
    } else{
      client.publish("hammock", "1");
      Serial.println("Hammock in use");
      digitalWrite(ledPin, LOW);
      Serial.println("light on");
      before=sensor;
    }
    // pause before taking the next reading
    delay(1000); 
    
}

void messageReceived(String topic, String payload, char * bytes, unsigned int length) {
  Serial.print("incoming: ");
  Serial.print(topic);
  Serial.print(" - ");
  Serial.print(payload);
  Serial.println();
}
