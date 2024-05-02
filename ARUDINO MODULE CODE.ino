#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD object with the I2C address 0x20 (replace with your actual I2C address)
LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust the columns (16) and rows (2) according to your LCD

const int doorPin = 2;  // Replace 2 with the actual pin number connected to the door sensor
const int buzzerPin = 3;  // Replace 3 with the actual pin number connected to the buzzer

// Define pins for the RGB LED
const int redPin = 9;   // Replace with the pin number connected to the Red channel of the RGB LED
const int greenPin = 10; // Replace with the pin number connected to the Green channel of the RGB LED
const int bluePin = 11;  // Replace with the pin number connected to the Blue channel of the RGB LED

// Replace the below values with the desired beep tone and duration
const unsigned int beepFrequency = 1000;  // In Hz
const unsigned int beepDuration = 100;    // In milliseconds

void setup() {
  // Initialize I2C communication
  Serial.begin(115200);
  pinMode(doorPin, INPUT_PULLUP);
  Wire.begin();

  // Initialize the LCD with the number of columns and rows
  lcd.begin();

  // Your setup code here (if any)

  // Set RGB LED pins as OUTPUT
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Print a welcome message on the LCD
  lcd.print("Hello, I2C LCD!");

  // Set the RGB LED to blue during system startup
  setColor(0, 0, 255);
  
}

void doorControl() {
  pinMode(doorPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);

  bool doorOpen = false;
  bool doorState = digitalRead(doorPin);

  if (doorState == HIGH) {
    doorOpen = true;
    lcd.clear();
    lcd.print("Door is OPEN");   // Display the message on the LCD
    setColor(255, 0, 0);  // Set RGB LED to red when the door is open
     Serial.println("OPEN");
    delay(500);
  } else {
    doorOpen = false;
    lcd.clear();
    lcd.print("Door is CLOSED"); // Display the message on the LCD
    setColor(0, 255, 0);  // Set RGB LED to green when the door is closed
     Serial.println("CLOSED");
    delay(500);
  }

  if (doorOpen) {
    // Make the buzzer beep when the door is opened
    tone(buzzerPin, beepFrequency, beepDuration);
    delay(beepDuration);  // Add a delay to avoid multiple beeps for a single door open event
  }
}

void loop() {
  // Your other code here (if any)

  // Call the doorControl function
  doorControl();

  // More of your other code here (if any)
}

void setColor(int redValue, int greenValue, int blueValue) {
  // Set the intensity of each color channel using analogWrite
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}
