#include <Wire.h>                            // Include Wire library for I2C communication
#include <Adafruit_Sensor.h>                 // Include Adafruit Unified Sensor library
#include <Adafruit_TSL2561_U.h>              // Include Adafruit TSL2561 library

// Initialize the TSL2561 light sensor with a unique ID
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

// Function to display basic sensor details
void displaySensorDetails(void) {
  sensor_t sensor;
  tsl.getSensor(&sensor);                                            // Get sensor parameters
  Serial.println("------------------------------------");
  Serial.print("Sensor:      "); Serial.println(sensor.name);        // Display sensor name
  Serial.print("Driver Ver:  "); Serial.println(sensor.version);     // Display driver version
  Serial.print("Unique ID:   "); Serial.println(sensor.sensor_id);   // Display sensor ID
  Serial.print("Max Value:   "); Serial.print(sensor.max_value); Serial.println(" lux");  // Display max value
  Serial.print("Min Value:   "); Serial.print(sensor.min_value); Serial.println(" lux");  // Display min value
  Serial.print("Resolution:  "); Serial.print(sensor.resolution); Serial.println(" lux"); // Display resolution
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

// Function to configure the sensor gain and integration time
void configureSensor(void) {
  tsl.enableAutoRange(true);                                         // Enable auto-gain
  tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);              // Set integration time to 13ms

  // Display the current gain and integration time settings
  Serial.println("------------------------------------");
  Serial.print("Gain:         "); Serial.println("Auto");            // Auto-gain enabled
  Serial.print("Timing:       "); Serial.println("13 ms");           // Integration time
  Serial.println("------------------------------------");
}

void setup(void) {
  Serial.begin(9600);                                                // Initialize serial communication
  Serial.println("Light Sensor Test"); Serial.println("");
  
  // Initialize the sensor
  if(!tsl.begin()) {
    Serial.print("Ooops, no TSL2561 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  displaySensorDetails();                                            // Display sensor details
  configureSensor();                                                  // Configure the sensor
}

void loop(void) {  
  sensors_event_t event;
  tsl.getEvent(&event);                                              // Get a new sensor event
 
  // Display the results (light is measured in lux)
  if (event.light) {
    Serial.print(event.light); Serial.println(" lux");               // Display light reading in lux
  } else {
    // If the sensor is saturated and cannot provide a reliable reading
    Serial.println("Sensor overload");
  }
  delay(250);                                                        // Delay before next reading
}