// Include necessary libraries
#include <DHT.h> // Library for DHT22 sensor
#include <Adafruit_Sensor.h> // Adafruit base sensor library
#include <Adafruit_TSL2591.h> // Library for TSL2591 light sensor
#include <Adafruit_BMP3XX.h> // Library for BMP390 pressure sensor
#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for the LCD display

// Define sensor and display pins
#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // Specify the type of DHT sensor

// Initialize sensor objects
DHT dht(DHTPIN, DHTTYPE); // Create a DHT object for temperature and humidity
Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591); // Create a TSL2591 object for light intensity
Adafruit_BMP3XX bmp; // Create a BMP3XX object for atmospheric pressure

// Initialize the LCD display
LiquidCrystal_I2C lcd(0x27,16,2); // Create an LCD object with I2C address 0x27 and 16 columns and 2 rows

void setup() {
  Serial.begin(9600); // Start the serial communication at 9600 baud rate
  
  // Sensor initializations
  dht.begin(); // Initialize DHT22 sensor

  // TSL2591 light sensor initialization
  if (!tsl.begin()) { // Check if TSL2591 sensor is connected
    Serial.println("Could not find a TSL2591 sensor"); // Print an error message if not found
  }
  tsl.setGain(TSL2591_GAIN_MED); // Set gain to medium
  tsl.setTiming(TSL2591_INTEGRATIONTIME_100MS); // Set integration time to 100 milliseconds

  // BMP390 pressure sensor initialization
  if (!bmp.begin_I2C()) { // Check if BMP390 sensor is connected
    Serial.println("Could not find a BMP390 sensor"); // Print an error message if not found
  }

  // LCD display setup
  lcd.init(); // Initialize the LCD
  lcd.backlight(); // Turn on the backlight of the LCD
}

void loop() {
  // Reading from sensors
  float temperature = dht.readTemperature(); // Read temperature from DHT22
  float humidity = dht.readHumidity(); // Read humidity from DHT22

  // Read light intensity from TSL2591
  float light = tsl.getFullLuminosity(); // Get full luminosity (visible + infrared)
  
  // Read atmospheric pressure from BMP390
  float pressure = bmp.readPressure(); // Read pressure

  // Display data on the LCD
  lcd.clear(); // Clear the LCD screen
  lcd.setCursor(0,0); // Set cursor to the first column of the first row
  lcd.print("Temp: "); lcd.print(temperature); lcd.print(" C"); // Print temperature
  lcd.setCursor(0,1); // Set cursor to the first column of the second row
  lcd.print("Hum: "); lcd.print(humidity); lcd.print(" %"); // Print humidity
  delay(2000); // Wait for 2 seconds
  
  // Display the next set of data
  lcd.clear(); // Clear the screen for new data
  lcd.setCursor(0,0); // Set cursor to the first column of the first row
  lcd.print("Light: "); lcd.print(light); lcd.print(" lx"); // Print light intensity
  lcd.setCursor(0,1); // Set cursor to the first column of the second row
  lcd.print("Press: "); lcd.print(pressure/100.0); lcd.print(" hPa"); // Print pressure in hectopascals
  delay(2000); // Wait for 2 seconds
}
