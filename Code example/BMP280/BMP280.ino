#include <Wire.h>                                   // Include Wire library for I2C communication
#include <Adafruit_BMP280.h>                        // Include Adafruit BMP280 library

// Create an instance of the Adafruit_BMP280 class to represent the BMP280 sensor
Adafruit_BMP280 bmp;                                // use I2C interface
// Obtain pointers to the temperature and pressure sensor objects within the BMP280
Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();

void setup() {
  Serial.begin(9600);                               // Initialize serial communication at 9600 baud rate
  while ( !Serial ) delay(100);                     // wait for native usb
  Serial.println(F("BMP280 Sensor event test"));

  unsigned status;                                  // Variable to store the status of sensor initialization
  // Initialize the BMP280 sensor
  status = bmp.begin();
  if (!status) {                                    // Check if the sensor is not initialized properly
    // Print an error message if the sensor is not found
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    Serial.print("SensorID was: 0x"); Serial.println(bmp.sensorID(),16);   // Print the sensor ID
    // Print suggestions for troubleshooting based on the sensor ID
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);                            // Infinite loop if the sensor is not found
  }

  /* Configure sensor with default settings from the datasheet */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  bmp_temp->printSensorDetails();                   // Print details of the temperature sensor
}

void loop() {
  sensors_event_t temp_event, pressure_event;       // Create event objects for temperature and pressure
  bmp_temp->getEvent(&temp_event);                  // Get the temperature event
  bmp_pressure->getEvent(&pressure_event);          // Get the pressure event
  
  Serial.print(F("Temperature = "));                // Print temperature data
  Serial.print(temp_event.temperature);
  Serial.println(" *C");

  Serial.print(F("Pressure = "));                   // Print pressure data
  Serial.print(pressure_event.pressure);
  Serial.println(" hPa");

  Serial.println();                                 // Print a newline for readability
  delay(2000);                                      // Wait for 2 seconds before next read
}
