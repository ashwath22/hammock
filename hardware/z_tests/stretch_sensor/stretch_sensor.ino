// Sensor pin - GND
// Sensor pin - Analog In 0, with 10K resistor to +5V

int SensorPin = A0;    // Sensor connected to analog pin A0
int before = 0; 
 
void setup()
{
    // initialize serial communications
    Serial.begin(9600); 
    int sensor = analogRead(SensorPin);
    before = sensor;
}
 
void loop()
{
    // read the voltage from the voltage divider (sensor plus resistor)
    int sensor = analogRead(SensorPin);
    Serial.println(sensor);
    if( sensor <= before && sensor < 55){
      Serial.println("Hammock not in use");
    } else{
      Serial.println("Hammock in use");
      before=sensor;
    }
    
 
    // pause before taking the next reading
    delay(1000); 
}

