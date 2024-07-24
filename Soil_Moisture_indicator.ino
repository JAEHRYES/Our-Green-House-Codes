#include <Adafruit_NeoPixel.h>

#define MOISTURE_SENSOR_PIN A0 // Analog pin for moisture sensor (can be changed as per your wiring)

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, 6, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);   // Initialize serial communication for debugging
  pixels.begin();       // Initialize NeoPixel strip
}

void loop() {
  // Read moisture sensor
  int moistureValue = analogRead(MOISTURE_SENSOR_PIN);
  float moisturePercent = map(moistureValue, 0, 1023, 0, 100); // Map analog value to percentage (0-100%)

  Serial.print("Moisture Value: ");
  Serial.print(moistureValue);
  Serial.print("\t Moisture Percent: ");
  Serial.print(moisturePercent);
  Serial.println("%");

  // Convert moisture percentage to NeoPixel color (simplified example)
  //int red = map(moisturePercent, 0, 100, 0, 255);
  //int green = map(100 - moisturePercent, 0, 100, 0, 255); // Inverse of red for demonstration
  //int blue = 0;

  // Set NeoPixels color based on moisture level
  if (moistureValue < 50){
    pixels.setPixelColor(0, 23,255,10);
  }
  else if(moistureValue < 550 && moistureValue > 100){
    pixels.setPixelColor(0, 255, 0, 0);
  }
  pixels.show(); // Display the updated pixels

  delay(1000); // Delay for readability and to update sensor data
}
/*Connections:

 1. soil moisture - to gnd,+ to 5V, S (log input ) A0
 2. Neopixel Gnd go to Gnd, V go to 5v and I go to Input 6
 */
 