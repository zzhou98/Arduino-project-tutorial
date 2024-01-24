#include <Wire.h>                                          // Include Wire library for I2C communication
#include <Adafruit_Sensor.h>                               // Include Adafruit Unified Sensor library
#include "Adafruit_TSL2591.h"                              // Include Adafruit TSL2591 library

Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591);   // Create an instance of the TSL2591 class with a sensor ID

// Function to display basic sensor details
void displaySensorDetails(void) {
  sensor_t sensor;
  tsl.getSensor(&sensor);                                                  // Retrieve sensor details
  Serial.print(F("Sensor:       ")); Serial.println(sensor.name);          // Display sensor name
  Serial.print(F("Driver Ver:   ")); Serial.println(sensor.version);       // Display driver version
  Serial.print(F("Unique ID:    ")); Serial.println(sensor.sensor_id);     // Display sensor ID
  delay(500);
}

// Function to configure the sensor's gain and integration time
void configureSensor(void) {
  tsl.setGain(TSL2591_GAIN_MED);                                           // Set gain to medium
  tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);                            // Set integration time to 300ms
}

void setup(void) {
  Serial.begin(9600);                                                      // Initialize serial communication
  Serial.println(F("Starting Adafruit TSL2591 Test!"));
  
  if (tsl.begin()) {
    Serial.println(F("Found a TSL2591 sensor"));                           // Sensor found
  } else {
    Serial.println(F("No sensor found ... check your wiring?"));           // Sensor not found
    while (1);
  }
    
  displaySensorDetails();                                                  // Display sensor details
  configureSensor();                                                        // Configure the sensor
}

// Function to perform a simple read and display the luminosity
void simpleRead(void) {
  uint16_t x = tsl.getLuminosity(TSL2591_VISIBLE);                         // Get visible light reading
  Serial.print(F("[ ")); Serial.print(millis()); Serial.print(F(" ms ] "));
  Serial.print(F("Luminosity: "));
  Serial.println(x, DEC);
}

// Function to read IR, Full Spectrum, and calculate Lux
void advancedRead(void) {
  uint32_t lum = tsl.getFullLuminosity();           // Get full luminosity (32 bits with IR and full spectrum)
  uint16_t ir = lum >> 16;                                                 // Upper 16 bits are IR
  uint16_t full = lum & 0xFFFF;                                            // Lower 16 bits are full spectrum
  Serial.print(F("[ ")); Serial.print(millis()); Serial.print(F(" ms ] "));
  Serial.print(F("IR: ")); Serial.print(ir);  Serial.print(F("  "));
  Serial.print(F("Full: ")); Serial.print(full); Serial.print(F("  "));
  Serial.print(F("Visible: ")); Serial.print(full - ir); Serial.print(F("  "));
  Serial.print(F("Lux: ")); Serial.println(tsl.calculateLux(full, ir), 6); // Calculate and display Lux
}

void loop(void) { 
  // Choose one of the readings
  // simpleRead(); // Uncomment for simple read
  advancedRead(); // Uncomment for advanced read
  // unifiedSensorAPIRead(); // Uncomment for Unified Sensor API read
  
  delay(500);                                                             // Delay between readings
}
