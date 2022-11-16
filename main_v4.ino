#include <Servo.h>
#include <DHT.h>
#include <SPI.h>
#include <WiFiNINA.h>

// Wifi Module
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                 // your network key index number (needed only for WEP)

int status = WL_IDLE_STATUS;
WiFiServer server(80);

// Servo and soil moisture sensor
Servo myservo;  // create servo object to control a servo

int sensorPin = A0; 
int sensorValue;  
int limit = 300; 
int pos = 0;    // variable to store the servo position

// DHT22 sensor
#define DHTPIN 7     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value

// Setup
void setup() {
  Serial.begin(9600);

  pinMode(9, OUTPUT);      // set the LED pin mode
  pinMode(13, OUTPUT);

    // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }
  server.begin();                           // start the web server on port 80
  printWifiStatus();                        // you're connected now, so print out the status

  // Start DHT sensor
  dht.begin();

  // Mount Servo
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  WiFiClient client = server.available();   // listen for incoming clients
  hum = dht.readHumidity();
  temp = dht.readTemperature();

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            client.print("<h2> Humidity: </h2>");
            client.print(hum);
            client.println();
            client.print("<h2> Temperature: </h2>");
            client.print(temp);
            client.println();
            client.print("<h2> Soil Moisture: </h2>");
            client.print(sensorValue);
            client.println();

            client.print("<form action=\"/soil\"> <input type=\"submit\" value=\"Soil Sensor Test\" /> </form>")

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H\">here</a> turn the LED on<br>");
            client.print("Click <a href=\"/L\">here</a> turn the LED off<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(LED_BUILTIN, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(LED_BUILTIN, LOW);                // GET /L turns the LED off
        }
        if (currentLine.endsWith("GET /soil")) {
            for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 90 degrees
              myservo.write(pos);              // tell servo to go to position in variable 'pos'
              delay(15);                       // waits 15 ms for the servo to reach the position
            }
            sensorValue = analogRead(sensorPin);
            delay(5000);
            for (pos = 90; pos >= 0; pos -= 1) { // goes from 90 degrees to 0 degrees
              myservo.write(pos);              // tell servo to go to position in variable 'pos'
              delay(15);                       // waits 15 ms for the servo to reach the position
            }
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
}
