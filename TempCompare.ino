#include <DHT.h>

#include <TMP36.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define DHTPIN 3
#define DHTTYPE DHT11   // DHT 21 (AM2301)

#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

TMP36 tmp36_5v(A3, 5);
long lastTmpCheckLastMillis = 0;
long lastDhtMillis = 0;

//TMP36 tmp36_3v(A2, 3.3);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  Serial.begin(9600);
  lastTmpCheckLastMillis = millis();
  lastDhtMillis = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  //display.display();
  //displayOnOled();
  //testSize2();
  //testdrawstyles();
  //Serial.println("test...");
  checkDHT();
  
  //checktmp36();
  delay(3000);
  //Serial.println("test 2....");
}
void checkDHT(){
    if ((millis() - lastDhtMillis) < 10000){
    return;
  }
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  //float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  //float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
//  Serial.println(h);
//  Serial.println(t);
  Serial.println(f);
//  // Check if any reads failed and exit early (to try again).
  if (isnan(f)){
  //if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
//  float hif = dht.computeHeatIndex(f, h);
//  // Compute heat index in Celsius (isFahreheit = false)
//  float hic = dht.computeHeatIndex(t, h, false);

//  Serial.print(F("Humidity: "));
//  Serial.print(h);
//  Serial.print(F("%  Temperature: "));
//  Serial.print(t);
//  Serial.print(F("°C "));
//  Serial.print(f);
//  Serial.print(F("°F  Heat index: "));
//  Serial.print(hic);
//  Serial.print(F("°C "));
//  Serial.print(hif);
//  Serial.println(F("°F"));

display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(3, 2);     // Start at top-left corner
  
  display.cp437(true);       
  
  display.println(F("°F"));
lastDhtMillis = millis();
 // delay(3000);
  
}

void checktmp36(){
  if ((millis() - lastTmpCheckLastMillis) < 30000){
    return;
  }
  
  display.clearDisplay();

  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  
  display.cp437(true);       
  
  display.println(tmp36_5v.getTempF());
//  display.println(tmp36_5v.getTempC());
//  display.println(tmp36_5v.getTempK());
  display.display();

  //set last run for this code
  lastTmpCheckLastMillis = millis();
}

void displayOnOled(void) {
  display.clearDisplay();

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  display.println("06/06/2021 13:05.33");
  display.print("    ");
  display.println("basement");
  display.println();
  display.setTextSize(2);
  display.println("   70.69");
  display.println();
  display.setTextSize(1);
  display.println("SD Ready");

  display.display();
  //delay(2000);
}

void testSize2(){
  display.clearDisplay();
 
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
 display.println("06/06/2021 13:05.33");
  display.setTextSize(2);
 
  display.println("Line 1");
  display.println("Line 2");
  display.println("1234567890");
  display.println("Line 3");
  display.display();
}

void testdrawstyles(void) {
  display.clearDisplay();

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("Hello, world!"));

  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  display.println(3.141592);

  display.setTextSize(2);             // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.print(F("0x")); display.println(0xDEADBEEF, HEX);

  display.display();
  delay(2000);
}

  
