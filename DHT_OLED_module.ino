#include "DHT.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define DHTPIN 6     
#define DHTTYPE DHT11   

DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

float difft[2] = {};
float diff = 0;
float h = 0;
float t = 0;

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  dht.begin();
}

void loop() {
  h = dht.readHumidity();
  t = dht.readTemperature();
  difft[1] = t;
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  diff = abs(difft[0] - difft[1]);
  sp();
  dt();
  if((t > 28 && h > 65) || (t < 20 && h < 30) ){
    toohot();
  }
  delay(2000);
}
void sp(){
  Serial.print(F("Humidity: "));
  Serial.println(h);
  Serial.print(F("Temperature: "));
  Serial.println(t);
  Serial.print(F("Difference: "));
  Serial.println(diff);
}
void dt(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Temperature is: ");
  display.println(t);
  display.print("Humidity is: ");
  display.println(h);
  display.print("Difference is: ");
  display.println(diff);
  display.print("Water sat. is: ");
  display.display();
}
void toohot(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Conditions");
  display.println("Not suitable");
  display.println("For plant");
  display.display();
}
void ssdtest(){
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Hello");
  display.display();
  dht.begin();
}