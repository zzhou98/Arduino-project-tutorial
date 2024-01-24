#include <Wire.h>                          // Include Wire library for I2C communication
#include "Adafruit_SGP30.h"                // Include Adafruit SGP30 library for air quality sensor

Adafruit_SGP30 sgp;                        // Create an instance of the SGP30 class

// Function to calculate absolute humidity in mg/m^3
uint32_t getAbsoluteHumidity(float temperature, float humidity) {
    // Approximation formula from Sensirion SGP30 Driver Integration chapter 3.15
    const float absoluteHumidity = 216.7f * ((humidity / 100.0f) * 6.112f * exp((17.62f * temperature) / (243.12f + temperature)) / (273.15f + temperature)); // Calculate absolute humidity in g/m^3
    const uint32_t absoluteHumidityScaled = static_cast<uint32_t>(1000.0f * absoluteHumidity); // Convert to mg/m^3
    return absoluteHumidityScaled;
}

void setup() {
  Serial.begin(115200);                            // Start serial communication at 115200 baud rate
  while (!Serial) { delay(10); }                   // Wait for serial console to open
  Serial.println("SGP30 test");                    // Print test message to serial

  if (!sgp.begin()) {                              // Initialize SGP30 sensor
    Serial.println("Sensor not found :(");         // Sensor not found message
    while (1);                                     // Infinite loop if sensor not found
  } 
  Serial.print("Found SGP30 serial #");            // Print found sensor message
  Serial.print(sgp.serialnumber[0], HEX);          // Print sensor's serial number in hexadecimal format
  Serial.print(sgp.serialnumber[1], HEX);
  Serial.println(sgp.serialnumber[2], HEX);
}

int counter = 0;                                   // Counter for baseline readings

void loop() {
  if (!sgp.IAQmeasure()) {                         // Perform IAQ measurement
    Serial.println("Measurement failed");          // Print error if measurement fails
    return;
  }
  // Print Total Volatile Organic Compounds (TVOC) and equivalent CO2 (eCO2) levels
  Serial.print("TVOC "); Serial.print(sgp.TVOC); Serial.print(" ppb\t");
  Serial.print("eCO2 "); Serial.print(sgp.eCO2); Serial.println(" ppm");

  if (!sgp.IAQmeasureRaw()) {                      // Perform raw signal measurement (H2 and Ethanol)
    Serial.println("Raw Measurement failed");      // Print error if raw measurement fails
    return;
  }
  Serial.print("Raw H2 "); Serial.print(sgp.rawH2); Serial.print(" \t");           // Print raw Hydrogen
  Serial.print("Raw Ethanol "); Serial.print(sgp.rawEthanol); Serial.println("");  // Print raw Ethanol values

  delay(1000);                                     // Wait for 1 second

  counter++;                                       // Increment counter each loop
  if (counter == 30) {                             // Every 30 readings, get baseline values for eCO2 and TVOC
    counter = 0; // Reset counter

    uint16_t TVOC_base, eCO2_base;
    if (!sgp.getIAQBaseline(&eCO2_base, &TVOC_base)) {      // Get baseline values
      Serial.println("Failed to get baseline readings");    // Print error if unable to get baseline
      return;
    }
    // Print baseline values for eCO2 and TVOC in hexadecimal format
    Serial.print("****Baseline values: eCO2: 0x"); Serial.print(eCO2_base, HEX);
    Serial.print(" & TVOC: 0x"); Serial.println(TVOC_base, HEX);
  }
}