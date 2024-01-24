// Include the LiquidCrystal library for controlling LCDs
#include <LiquidCrystal.h>

// Initialize the library with the numbers of the interface pins
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; // Define pin numbers for the LCD
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);                  // Create an LCD object and assign the pins

void setup() {
  // Set up the number of columns and rows on the LCD (16x2 in this case)
  lcd.begin(16, 2);

  // Print a message to the LCD's first row
  lcd.print("hello, world!");
}

void loop() {
  // Set the cursor to the first column (0) of the second row (1)
  lcd.setCursor(0, 1);

  // Print the number of seconds since the Arduino was reset
  // millis() returns the number of milliseconds since reset, divide by 1000 to get seconds
  lcd.print(millis() / 1000);
}
