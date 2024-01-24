#include "DHT.h"

#define DHTPIN 2                                   // Define the digital pin connected to the DHT sensor.
#define DHTTYPE DHT22                              // Specify the DHT sensor type. In this case, DHT22.

DHT dht(DHTPIN, DHTTYPE);                         // Initialize the DHT sensor.

void setup() {
  Serial.begin(9600);                             // Initialize serial communication at 9600 bits per second.
  Serial.println(F("DHTxx test!"));               // Print characters "DHTxx test!".

  dht.begin();                                    // Initialize the DHT sensor.
}

void loop() {
  delay(2000);                                    // Wait for 2000 milliseconds between each measurement.

  float h = dht.readHumidity();                    // Read the humidity value.
  float t = dht.readTemperature();                 // Read the temperature in Celsius.
  float f = dht.readTemperature(true);             // Read the temperature in Fahrenheit.

  // Check for failed readings from the DHT sensor.
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  float hif = dht.computeHeatIndex(f, h);          // Compute heat index in Fahrenheit.
  float hic = dht.computeHeatIndex(t, h, false);   // Compute heat index in Celsius.

  // Print the results to the serial plotter.
  Serial.print("Humidity:");
  Serial.print(h);
  Serial.print(",");
  Serial.print("Temperature:");
  Serial.print(t);
  Serial.print(",");
  Serial.print("TemperatureF:");
  Serial.print(f);
  Serial.print(",");
  Serial.print("Heat_indexC:");
  Serial.print(hic);
  Serial.print(",");
  Serial.print("Heat_indexF:");
  Serial.print(hif);
  Serial.println("°F");
}
