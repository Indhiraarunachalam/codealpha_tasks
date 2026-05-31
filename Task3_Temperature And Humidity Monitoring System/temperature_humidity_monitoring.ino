#include <LiquidCrystal.h>

// Initialize the LCD library with the interface pins
// RS, E, DB4, DB5, DB6, DB7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int tempPin = A0;  // TMP36 pin
const int humidPin = A1; // Potentiometer pin

void setup() {
  // Initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  // Print a starting message
  lcd.print("Weather Station");
  delay(2000);
  lcd.clear();
}

void loop() {
  // --- Temperature Calculation ---
  int reading = analogRead(tempPin);
  // Convert voltage to Celsius for TMP36 sensor
  float voltage = reading * (5.0 / 1023.0);
  float temperatureC = (voltage - 0.5) * 100;

  // --- Humidity Calculation ---
  int potValue = analogRead(humidPin);
  // Map the 0-1023 analog value to a 0-100% humidity scale
  int humidity = map(potValue, 0, 1023, 0, 100);

  // --- Display on LCD ---
  // Line 1: Temperature
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperatureC, 1); // 1 decimal place
  lcd.print(" C   ");         

  // Line 2: Humidity
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print("%   ");

  // --- Print to Serial Monitor ---
  Serial.print("Temperature: ");
  Serial.print(temperatureC, 1);
  Serial.print(" C | Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  delay(1000); // Update every second
}
