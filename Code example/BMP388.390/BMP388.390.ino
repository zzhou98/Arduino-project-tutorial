#include <Wire.h>                                        // Include the Wire library for I2C communication
#include <Adafruit_Sensor.h>                             // Include the Adafruit Unified Sensor library
#include "Adafruit_BMP3XX.h"                             // Include the library for the BMP3XX sensor

// Define the sea-level pressure in hPa as a reference for altitude calculation
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BMP3XX bmp;                                     // Create an instance of the BMP3XX class

void setup() {
  Serial.begin(115200);                                  // Start serial communication at 115200 baud rate
  while (!Serial);                                       // Wait for serial console to become ready
  Serial.println("Adafruit BMP388 / BMP390 test");       // Print a startup message

  // Initialize the BMP3XX sensor using I2C
  if (!bmp.begin_I2C()) {                                // If initialization fails, print an error message
    Serial.println("Could not find a valid BMP3 sensor, check wiring!");
    while (1);                                           // Infinite loop if the sensor is not found
  }

  // Configure sensor settings
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);  // Set temperature oversampling
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);     // Set pressure oversampling
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);        // Set the IIR filter coefficient
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);                 // Set the output data rate
}

void loop() {
  if (!bmp.performReading()) {                           //Perform reading. If failed, print error message
    Serial.println("Failed to perform reading :(");
    return;                                              // Exit the loop on failure
  }
  // Print the temperature reading in Celsius
  Serial.print("Temperature = ");
  Serial.print(bmp.temperature);
  Serial.println(" *C");

  // Print the pressure reading in hPa
  Serial.print("Pressure = ");
  Serial.print(bmp.pressure / 100.0);                    // Convert pressure from Pa to hPa
  Serial.println(" hPa");

  // Print the approximate altitude in meters
  Serial.print("Approx. Altitude = ");

 // Calculate altitude using the specified sea-level pressure
  Serial.print(bmp.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.println();                                      // Print a new line for readability
  delay(2000);                                           // Wait for 2 seconds before next read
}
