#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD object with I2C address 0x27, 16 columns, 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin definitions
int sensor_pin = A0;     // Soil moisture sensor analog pin
int relay_pin = 7;       // Relay control pin

void setup() {
  Serial.begin(9600);
  lcd.init();            // Initialize the LCD
  lcd.backlight();       // Turn on the LCD backlight
  pinMode(sensor_pin, INPUT);
  pinMode(relay_pin, OUTPUT);
}

void loop() {
  int sensor_data = analogRead(sensor_pin);  // Read sensor value

  Serial.print("Sensor_data: ");
  Serial.print(sensor_data);
  Serial.print("\t | ");

  lcd.clear(); // Clear the LCD before writing new content

  if (sensor_data > 950) {
    Serial.println("No moisture, Soil is dry");
    digitalWrite(relay_pin, LOW); // Turn ON motor (Relay active LOW)
    lcd.setCursor(0, 0);
    lcd.print("Soil Dry       ");
    lcd.setCursor(0, 1);
    lcd.print("Motor ON       ");
  }
  else if (sensor_data >= 400 && sensor_data <= 950) {
    Serial.println("There is some moisture, Soil is medium");
    digitalWrite(relay_pin, HIGH); // Turn OFF motor
    lcd.setCursor(0, 0);
    lcd.print("Soil Medium    ");
    lcd.setCursor(0, 1);
    lcd.print("Motor OFF      ");
  }
  else if (sensor_data < 400) {
    Serial.println("Soil is wet");
    digitalWrite(relay_pin, HIGH); // Turn OFF motor
    lcd.setCursor(0, 0);
    lcd.print("Soil Wet       ");
    lcd.setCursor(0, 1);
    lcd.print("Motor OFF      ");
  }

  delay(1000); // Wait for 1 second before next reading
}
