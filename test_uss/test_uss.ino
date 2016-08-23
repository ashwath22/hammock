#define trigPin 13
#define echoPin 12
#define led 11
#define led2 10
int count = 0;
void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
//  pinMode(ledPin, OUTPUT);
//  pinMode(led2, OUTPUT);
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print(distance);
  Serial.println(" cm");
//
//  if (distance < 13){
//    count++;
//    delay(3000);
//  }
//
//  if (count%2 == 0){
//    Serial.println("In use"); 
//  }else{
//    Serial.println("Not in use");
//  }
//
//  if (count == 100){
//    count=0;
//  }
  delay(1000);
}
