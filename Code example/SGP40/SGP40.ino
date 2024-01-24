#include "Adafruit_SGP40.h"   // Include the library for the SGP40 VOC sensor
#include "Adafruit_SHT31.h"   // Include the library for the SHT31 temperature and humidity sensor

Adafruit_SGP40 sgp;           // Create an instance of the SGP40 class for the VOC sensor
Adafruit_SHT31 sht31;         // Create an instance of the SHT31 class for the temperature and humidity sensor

void setup() {
  Serial.begin(115200);              // Start serial communication at 115200 baud rate
  while (!Serial) { delay(10); }     // Wait for the serial console to open

  Serial.println("SGP40 test with SHT31 compensation");  // Print a startup message

  if (!sgp.begin()) {                                    // Initialize the SGP40 sensor
    Serial.println("SGP40 sensor not found :(");         // Print an error message if the sensor is not found
    while (1);                                           // Infinite loop if the sensor is not found
  }

  if (!sht31.begin(0x44)) {                      // Initialize the SHT31 sensor at I2C address 0x44 (default)
    Serial.println("Couldn't find SHT31");        // Print an error message if the sensor is not found
    while (1);                                   // Infinite loop if the sensor is not found
  }

  Serial.print("Found SHT3x + SGP40 serial #");  // Print a message indicating both sensors are found
  // Print the SGP40 sensor's serial number in hexadecimal format
  Serial.print(sgp.serialnumber[0], HEX);
  Serial.print(sgp.serialnumber[1], HEX);
  Serial.println(sgp.serialnumber[2], HEX);
}

int counter = 0;              // Counter variable for tracking loop iterations (unused in this code)

void loop() {
  uint16_t sraw;              // Variable to store raw VOC sensor reading
  int32_t voc_index;          // Variable to store calculated VOC index
  
  float t = sht31.readTemperature();                                     // Read temperature from SHT31
  Serial.print("Temp *C = "); Serial.print(t); Serial.print("\t\t");    // Print temperature
  float h = sht31.readHumidity();                                        // Read humidity from SHT31
  Serial.print("Hum. % = "); Serial.println(h);                         // Print humidity

  sraw = sgp.measureRaw(t, h);            // Measure raw VOC signal with temperature and humidity compensation
  Serial.print("Raw measurement: "); 
  Serial.println(sraw);                   // Print raw VOC measurement

  voc_index = sgp.measureVocIndex(t, h);  // Calculate VOC index using temperature and humidity compensation
  Serial.print("Voc Index: "); 
  Serial.println(voc_index);              // Print VOC index

  delay(1000);                            // Wait for 1 second before repeating the loop
}
