#include <Servo.h>
#include <DHT.h>;

Servo myservo;  // create servo object to control a servo

int sensorPin = A0; 
int sensorValue;  
int limit = 300; 
int pos = 0;    // variable to store the servo position

#define DHTPIN 7     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);

  dht.begin();
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  hum = dht.readHumidity();
  temp= dht.readTemperature();

  //Print temp and humidity values to serial monitor
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print(" Temp: ");
  Serial.print(temp);

  for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  sensorValue = analogRead(sensorPin); 
  Serial.print(" Soil Moisture: ");
  Serial.print(sensorValue);
  Serial.println("\n");
  
  if (sensorValue<limit) {
  digitalWrite(13, HIGH); 
  }
  else {
  digitalWrite(13, LOW); 
  }
  delay(5000);
  for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
 
  delay(10000); 
}
