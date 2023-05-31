#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2


// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

void setup() {
  // put your setup code here, to run once:
  // Start serial communication
  Serial.begin(115200, SERIAL_8N1);
  // Initialize the sensor
  sensors.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  // Request temperature from all connected sensors
  sensors.requestTemperatures();
  // Read temperature from sensor with index 0
  float temperatureC = sensors.getTempCByIndex(0);
  
  // Convert float temperature value to byte array and send it over serial to MATLAB
  byte *ptr = (byte*)&temperatureC;  // Get a pointer to the bytes of the float
  for (int i = 0; i < sizeof(float); i++) {
    Serial.write(*ptr);  // Send each byte over serial
    ptr++;  // Move the pointer to the next byte
  }
  
  // Wait for 1 second before taking another measurement
  delay(100);
} 

