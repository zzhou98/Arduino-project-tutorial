#include <Arduino.h>                              // Include the main Arduino library
#include <Wire.h>                                 // Include the Wire library for I2C communication
#include "Adafruit_SHT31.h"                       // Include the Adafruit SHT31 library for the SHT31 sensor

bool enableHeater = false;                        // A flag to control the heater state
uint8_t loopCnt = 0;                              // To keep track of loop iterations for heater toggling

Adafruit_SHT31 sht31 = Adafruit_SHT31();          // Create an instance of the SHT31 sensor class

void setup() {
  Serial.begin(9600);                             // Start serial communication at 9600 baud rate

  while (!Serial)                                 // Wait for the serial console to open
    delay(10);     

  Serial.println("SHT31 test");                   // Print a message to the serial console

  if (!sht31.begin(0x44)) {                       // Set to 0x45 for alternate I2C address
    Serial.println("Couldn't find SHT31");         // Initialize the SHT31 sensor, check if it's connected
    while (1) delay(1);                           // Infinite loop if sensor is not found
  }

    Serial.print("Heater Enabled State: ");       // Check and display the initial state of the heater
  if (sht31.isHeaterEnabled())
    Serial.println("ENABLED");
  else
    Serial.println("DISABLED");
}

void loop() {
  float t = sht31.readTemperature();               // Read temperature and humidity from the sensor
  float h = sht31.readHumidity();

  if (!isnan(t)) {                                // Check if the temperature reading is valid and print it
    Serial.print("Temp *C = "); Serial.print(t); Serial.print("\t\t");
  } else { 
    Serial.println("Failed to read temperature");
  }

  if (!isnan(h)) {                                // Check if the humidity reading is valid and print it
    Serial.print("Hum. % = "); Serial.println(h);
  } else { 
    Serial.println("Failed to read humidity");
  }

  delay(1000);                                    // Wait for 1 second before the next reading

  if (loopCnt >= 30) {                            // Toggle the heater state every 30 seconds
    enableHeater = !enableHeater;                 // Toggle the heater state
    sht31.heater(enableHeater);                   // Enable/disable the heater on the sensor
    Serial.print("Heater Enabled State: ");
    if (sht31.isHeaterEnabled())
      Serial.println("ENABLED");
    else
      Serial.println("DISABLED");

    loopCnt = 0;                                  // Reset the counter
  }
  loopCnt++;                                      // Increment the loop counter
}