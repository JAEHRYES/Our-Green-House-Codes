#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Servo.h>

// Pins for the ST7735S display
#define TFT_CS     10
#define TFT_RST    9
#define TFT_DC     8
#define TFT_SCLK   13
#define TFT_MOSI   11

// RGB LED pins
const int redPin = 4;    // Red pin of RGB LED
const int greenPin = 5;  // Green pin of RGB LED
const int bluePin = 6;   // Blue pin of RGB LED

// Button pin
const int buttonPin = 2; // Pin for the push button

// Create an instance of the display
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

Servo myServo;              // Create a Servo object
const int potPin = A0;      // Pin for the potentiometer
const int servoPin = 3;     // Pin for the servo motor

bool systemEnabled = true;  // Flag to track system state

// Define custom colors using RGB values
#define BLUE tft.color565(0, 0, 255)
#define RED tft.color565(255, 0, 0)
#define GREEN tft.color565(0, 255, 0)
#define BLACK tft.color565(0, 0, 0)

void setup() {
  Serial.begin(9600); // Initialize serial communication for debugging
  myServo.attach(servoPin); // Attach the servo to pin 3
  
  // Initialize the display
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1); // Rotate the display if necessary
  tft.fillScreen(BLACK);

  // Initialize RGB LED pins as outputs
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Initialize button pin as input with pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  handleButtonPress(); // Check and handle button press
  if (systemEnabled) {
    int potValue = analogRead(potPin); // Read the potentiometer value
    updateServo(potValue); // Update the servo position
    updateDisplay(potValue); // Update the display
    updateRGBLed(potValue); // Update the RGB LED
  } else {
    disableSystem(); // Turn off all outputs if the system is disabled
  }
  delay(100); // Small delay to stabilize readings
}

void handleButtonPress() {
  int buttonState = digitalRead(buttonPin);
  if (buttonState == LOW) {
    systemEnabled = !systemEnabled; // Toggle system state
    delay(200); // Debounce delay
  }
}

void updateServo(int potValue) {
  int servoAngle = map(potValue, 0, 1023, 0, 180); // Map the potentiometer value to a servo angle
  myServo.write(servoAngle); // Set the servo position
}

void updateDisplay(int potValue) {
  tft.fillScreen(BLACK); // Clear the display
  if (potValue < 512) {
    drawWaterDropletWithCross();
  } else {
    drawWaterDroplet();
  }
}

void updateRGBLed(int potValue) {
  if (potValue < 512) {
    analogWrite(redPin, 255);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
  } else {
    analogWrite(redPin, 0);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 0);
  }
}

void disableSystem() {
  myServo.write(0); // Set servo to minimum position
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
  tft.fillScreen(BLACK);
}

void drawWaterDroplet() {
  tft.fillCircle(64, 64, 20, RED); // Main part of the droplet
  tft.fillTriangle(64, 44, 44, 64, 84, 64, RED); // Top part of the droplet
}

void drawWaterDropletWithCross() {
  drawWaterDroplet();
  tft.drawLine(44, 44, 84, 84, BLUE); // Diagonal line from top-left to bottom-right
  tft.drawLine(44, 84, 84, 44, BLUE); // Diagonal line from bottom-left to top-right
}

/* 
Connections:
ST7735S OLED Display:
- GND to GND
- VCC to 5V
- SCL to 13 (SPI Clock)
- SDA to 11 (SPI Data)
- RES to 9 (Reset)
- DC to 8 (Data/Command)
- CS to 10 (Chip Select)
- BLK to 5V (or a PWM pin for brightness control)

SG90 Servo Motor:
- GND to GND
- VCC to 5V
- Signal to 3

Potentiometer:
- VCC to 5V
- GND to GND
- Output to A0

RGB LED:
- Red Pin to Digital Pin 4
- Green Pin to Digital Pin 5
- Blue Pin to Digital Pin 6

Push Button:
- One side to Digital Pin 2
- Other side to GND with a 10kΩ pull-down resistor
*/
