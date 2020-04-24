#define I2C_HARDWARE 1
#define I2C_TIMEOUT 10
#define I2C_MAXWAIT 10
#define I2C_PULLUP 1
#define I2C_FASTMODE 1
#define SDA_PORT PORTC
#define SDA_PIN 4 // = A4
#define SCL_PORT PORTC
#define SCL_PIN 5 // = A5

// config for tinyprint lib
#define TP_PRINTLINES 0
#define TP_FLASHSTRINGHELPER 1
#define TP_NUMBERS 0
#define TP_FLOAT 0
#define TP_WINDOWSLINEENDS 0

#include <SH1106Lib.h>
#include "glcdfont.h"
#include <ColorConverterLib.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6

#define NUMPIXELS 64

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500

SH1106Lib display;

uint8_t r;
uint8_t g;
uint8_t b;

char rFlt[15];
char gFlt[15];
char bFlt[15];

double SatPot;
double SatPct;
char SatPctFlt[15];

double HuePot;
double HuePct;
char HuePctFlt[15];

double BrgPot;
double BrgPct;
char BrgPctFlt[15];

int mode = 1;

char PoliceSpeed[15];
char StrobeSpeed[15];
char PulseSpeed[15];

int mnclr = 0;
int modeclr = 1;

float vmeterin;
float voltage;
char VoltageFlt[15];

float brgp;

// Voltage meter

void VoltageMeter() {
  float r1 = 30000;
  float r2 = 7500;
  vmeterin = analogRead(7);
  voltage = vmeterin * 5 / 1023 * (r1 + r2) / r2;
  dtostrf(voltage, 5, 2, VoltageFlt);
}

// Input

void getSatPot() {
  SatPot = analogRead(A0);
  SatPct = SatPot/1023*100;
  dtostrf(SatPct, 5, 0, SatPctFlt);
}

void getHuePot() {
  HuePot = analogRead(A1);
  HuePct = HuePot/1023*100;
  dtostrf(HuePct, 5, 0, HuePctFlt);
}

void getBrgPot() {
  BrgPot = analogRead(A2);
  BrgPct = BrgPot/1023*100;
  dtostrf(BrgPct, 5, 0, BrgPctFlt);
}

void HSVtoRGB() {
  ColorConverter::HsvToRgb(HuePct/100, SatPct/100, BrgPct/100, r, g, b);
  dtostrf(r, 3, 0, rFlt);
  dtostrf(g, 3, 0, gFlt);
  dtostrf(b, 3, 0, bFlt);
}

// Display

void DisplayAnalogData() {
  display.setCursor(0, 0);
	display.print(F("Voltage:"));
  display.setCursor(0, 14);
  display.print(F("Brightness:"));
  display.setCursor(0, 28);
  display.print(F("Hue:"));
  display.setCursor(0, 42);
  display.print(F("Saturation:"));
  display.setCursor(0, 56);

  display.print(F("rgb("));
  display.print(rFlt);
  display.print(F(", "));
  display.print(gFlt);
  display.print(F(", "));
  display.print(bFlt);
  display.print(F(")"));

  display.setCursor(90, 0);
  display.print(VoltageFlt);
  display.print(F("V"));
  display.setCursor(85, 14);
  display.print(BrgPctFlt);
  display.print(F("%"));
  display.setCursor(85, 28);
  display.print(HuePctFlt);
  display.print(F("%"));
  display.setCursor(85, 42);
  display.print(SatPctFlt);
  display.print(F("%"));
}

void DisplayPolice() {
  display.setCursor(0, 0);
	display.print(F("Voltage:"));
  display.setCursor(0, 14);
  display.print(F("Mode:"));

  display.setCursor(90, 0);
  display.print(VoltageFlt);
  display.print(F("V"));
  display.setCursor(0, 28);
  display.print(F("Police"));
}

void DisplayStorm() {
  display.setCursor(0, 0);
	display.print(F("Voltage:"));
  display.setCursor(0, 14);
  display.print(F("Mode:"));

  display.setCursor(90, 0);
  display.print(VoltageFlt);
  display.print(F("V"));
  display.setCursor(0, 28);
  display.print(F("Storm"));
}

void DisplayStrobe() {
  display.setCursor(0, 0);
	display.print(F("Voltage:"));
  display.setCursor(0, 14);
  display.print(F("Mode:"));
  display.setCursor(0, 28);
  display.print(F("Hue:"));
  display.setCursor(0, 42);
  display.print(F("Saturation:"));
  display.setCursor(0, 56);
  display.print(F("Speed:"));

  display.setCursor(90, 0);
  display.print(VoltageFlt);
  display.print(F("V"));
  display.setCursor(85, 14);
  display.print(F("Strobe"));
  display.setCursor(85, 28);
  display.print(HuePctFlt);
  display.print(F("%"));
  display.setCursor(85, 42);
  display.print(SatPctFlt);
  display.print(F("%"));
  display.setCursor(85, 56);
  display.print(StrobeSpeed);
  display.print(F("ms"));
}

void DisplayPulse() {
  display.setCursor(0, 0);
	display.print(F("Voltage:"));
  display.setCursor(0, 14);
  display.print(F("Mode:"));
  display.setCursor(0, 28);
  display.print(F("Hue:"));
  display.setCursor(0, 42);
  display.print(F("Saturation:"));
  display.setCursor(0, 56);
  display.print(F("Speed:"));

  display.setCursor(90, 0);
  display.print(VoltageFlt);
  display.print(F("V"));
  display.setCursor(85, 14);
  display.print(F("Pulse"));
  display.setCursor(85, 28);
  display.print(HuePctFlt);
  display.print(F("%"));
  display.setCursor(85, 42);
  display.print(SatPctFlt);
  display.print(F("%"));
  display.setCursor(85, 56);
  display.print(PulseSpeed);
  display.print(F("ms"));
}

void DisplayFire() {
  display.setCursor(0, 0);
	display.print(F("Voltage:"));
  display.setCursor(0, 14);
  display.print(F("Mode:"));

  display.setCursor(90, 0);
  display.print(VoltageFlt);
  display.print(F("V"));
  display.setCursor(0, 28);
  display.print(F("Fire"));
}

void DisplayClub() {
  display.setCursor(0, 0);
	display.print(F("Voltage:"));
  display.setCursor(0, 14);
  display.print(F("Mode:"));

  display.setCursor(90, 0);
  display.print(VoltageFlt);
  display.print(F("V"));
  display.setCursor(0, 28);
  display.print(F("Club lights"));
}

void DisplayFlicker() {
  display.setCursor(0, 0);
	display.print(F("Voltage:"));
  display.setCursor(0, 14);
  display.print(F("Mode:"));

  display.setCursor(90, 0);
  display.print(VoltageFlt);
  display.print(F("V"));
  display.setCursor(0, 28);
  display.print(F("Flicker"));
}

void DisplayWelding() {
  display.setCursor(0, 0);
	display.print(F("Voltage:"));
  display.setCursor(0, 14);
  display.print(F("Mode:"));

  display.setCursor(90, 0);
  display.print(VoltageFlt);
  display.print(F("V"));
  display.setCursor(0, 28);
  display.print(F("Welding"));
}

void DisplayCloudPass() {
  display.setCursor(0, 0);
	display.print(F("Voltage:"));
  display.setCursor(0, 14);
  display.print(F("Mode:"));

  display.setCursor(90, 0);
  display.print(VoltageFlt);
  display.print(F("V"));
  display.setCursor(0, 28);
  display.print(F("Cloud Passing"));
}

void DisplayMenu() {

  if (mnclr == 0) {
    display.clearDisplay();
    mnclr = 1;
    modeclr = 1;
  }

  display.setCursor(0, 0);
	display.print(F("Voltage:"));
  display.setCursor(0, 14);
  display.print(F("-- Menu --"));
  display.setCursor(0, 28);
  display.print(F("Firmware V1.0"));
  display.setCursor(0, 42);
  display.print(F("Mode:"));
  display.setCursor(0, 56);

  switch (mode) {
    case 1:
      display.print(F("Color             "));
      break;
    case 2:
      display.print(F("Strobe            "));
      break;
    case 3:
      display.print(F("Police            "));
      break;
    case 4:
      display.print(F("Storm             "));
      break;
    case 5:
      display.print(F("Pulse             "));
      break;
    case 6:
      display.print(F("Fire              "));
      break;
    case 7:
      display.print(F("Club lights       "));
      break;
    case 8:
      display.print(F("Flicker           "));
      break;
    case 9:
      display.print(F("Welding           "));
      break;
    case 10:
      display.print(F("Cloud passing     "));
      break;
  }

  display.setCursor(90, 0);
  display.print(VoltageFlt);
  display.print(F("V"));
}

// LED Modes

void NormalMode() {
  HSVtoRGB();
  DisplayAnalogData();
  pixels.clear();
  uint32_t color = pixels.Color(r, g, b);
  pixels.fill(color, 0, 64);
  pixels.show();
}

void Strobe() {
  dtostrf(BrgPct*30, 3, 0, StrobeSpeed);
  DisplayStrobe();
  ColorConverter::HsvToRgb(HuePct/100, SatPct/100, 1, r, g, b);
  pixels.clear();
  uint32_t color = pixels.Color(r, g, b);
  pixels.fill(color, 0, 64);
  pixels.show();
  delay(BrgPct*30);

  pixels.clear();
  uint32_t color2 = pixels.Color(0, 0, 0);
  pixels.fill(color2, 0, 64);
  pixels.show();
  delay(BrgPct*30);
}

void Police() {
  dtostrf(SatPct*30, 3, 0, PoliceSpeed);
  DisplayPolice();
  pixels.clear();
  uint32_t color = pixels.Color(255, 0, 0);
  pixels.fill(color, 0, 64);
  pixels.show();
  delay(SatPct*50);

  pixels.clear();
  uint32_t color2 = pixels.Color(0, 0, 255);
  pixels.fill(color2, 0, 64);
  pixels.show();
  delay(SatPct*30);
}

void Storm() {
  DisplayStorm();
  pixels.clear();
  uint32_t color = pixels.Color(255, 255, 255);
  pixels.fill(color, 0, 64);
  pixels.show();
  delay(random(50, 500));

  pixels.clear();
  uint32_t color2 = pixels.Color(0, 0, 0);
  pixels.fill(color2, 0, 64);
  pixels.show();
  delay(random(500, 5000));
}

void Pulse() {
  dtostrf(BrgPct, 3, 0, PulseSpeed);
  DisplayPulse();

  for (int pos = 0; pos <= 100; pos++) {
    brgp = pos;
    ColorConverter::HsvToRgb(HuePct/100, SatPct/100, brgp/100, r, g, b);
    pixels.clear();
    uint32_t color = pixels.Color(r, g, b);
    pixels.fill(color, 0, 64);
    pixels.show();
    delay(BrgPct);
  }
  for (int pos = 100; pos >= 0; pos--) {
    brgp = pos;
    ColorConverter::HsvToRgb(HuePct/100, SatPct/100, brgp/100, r, g, b);
    pixels.clear();
    uint32_t color = pixels.Color(r, g, b);
    pixels.fill(color, 0, 64);
    pixels.show();
    delay(BrgPct);
  }
}

void Fire() {
  DisplayFire();
  pixels.clear();
  uint32_t color = pixels.Color(255, 90, 0);
  pixels.fill(color, 0, 64);
  pixels.show();
  delay(random(200, 700));

  pixels.clear();
  uint32_t color2 = pixels.Color(255, 115, 0);
  pixels.fill(color2, 0, 64);
  pixels.show();
  delay(random(50, 400));
}

void ClubLights() {
  DisplayClub();
  pixels.clear();
  uint32_t color = pixels.Color(0, 255, 0);
  pixels.fill(color, 0, 64);
  pixels.show();
  delay(500);

  pixels.clear();
  uint32_t color2 = pixels.Color(255, 0, 221);
  pixels.fill(color2, 0, 64);
  pixels.show();
  delay(500);

  pixels.clear();
  uint32_t color3 = pixels.Color(255, 255, 0);
  pixels.fill(color3, 0, 64);
  pixels.show();
  delay(500);

  pixels.clear();
  uint32_t color4 = pixels.Color(0, 145, 255);
  pixels.fill(color4, 0, 64);
  pixels.show();
  delay(500);

  pixels.clear();
  uint32_t color5 = pixels.Color(255, 0, 55);
  pixels.fill(color5, 0, 64);
  pixels.show();
  delay(500);

  pixels.clear();
  uint32_t color6 = pixels.Color(255, 162, 0);
  pixels.fill(color6, 0, 64);
  pixels.show();
  delay(500);
}

void Flicker() {
  DisplayFlicker();
  pixels.clear();
  uint32_t color = pixels.Color(120, 120, 120);
  pixels.fill(color, 0, 64);
  pixels.show();
  delay(random(20, 70));

  DisplayFlicker();
  pixels.clear();
  uint32_t color2 = pixels.Color(50, 50, 50);
  pixels.fill(color2, 0, 64);
  pixels.show();
  delay(random(10, 50));

  pixels.clear();
  uint32_t color3 = pixels.Color(255, 255, 255);
  pixels.fill(color3, 0, 64);
  pixels.show();
  delay(random(200, 1000));
}

void Welding() {
  DisplayWelding();
  pixels.clear();
  uint32_t color = pixels.Color(120, 120, 120);
  pixels.fill(color, 0, 64);
  pixels.show();
  delay(random(10, 20));

  pixels.clear();
  uint32_t color2 = pixels.Color(255, 255, 255);
  pixels.fill(color2, 0, 64);
  pixels.show();
  delay(random(20, 30));
}

void CloudPass() {
  DisplayCloudPass();

  for (int pos = 25; pos <= 100; pos++) {
    brgp = pos;
    ColorConverter::HsvToRgb(HuePct/100, 0, brgp/100, r, g, b);
    pixels.clear();
    uint32_t color = pixels.Color(r, g, b);
    pixels.fill(color, 0, 64);
    pixels.show();
    delay(100);
  }
  for (int pos = 100; pos >= 25; pos--) {
    brgp = pos;
    ColorConverter::HsvToRgb(HuePct/100, 0, brgp/100, r, g, b);
    pixels.clear();
    uint32_t color = pixels.Color(r, g, b);
    pixels.fill(color, 0, 64);
    pixels.show();
    delay(100);
  }
}

void Menu() {

  pixels.clear();
  uint32_t color2 = pixels.Color(0, 0, 0);
  pixels.fill(color2, 0, 64);
  pixels.show();

  DisplayMenu();

  if (BrgPct >= 0 && BrgPct < 10) {
    mode = 1;
  } else if (BrgPct >= 10 && BrgPct < 20) {
    mode = 2;
  } else if (BrgPct >= 20 && BrgPct < 30) {
    mode = 3;
  } else if (BrgPct >= 30 && BrgPct < 40) {
    mode = 4;
  } else if (BrgPct >= 40 && BrgPct < 50) {
    mode = 5;
  } else if (BrgPct >= 50 && BrgPct < 60) {
    mode = 6;
  } else if (BrgPct >= 60 && BrgPct < 70) {
    mode = 7;
  } else if (BrgPct >= 70 && BrgPct < 80) {
    mode = 8;
  } else if (BrgPct >= 80 && BrgPct < 90) {
    mode = 9;
  } else if (BrgPct >= 90 && BrgPct < 100) {
    mode = 10;
  }
}

// Setup

void setup() {
  Serial.begin(9600);
	display.initialize();
	display.clearDisplay();
  display.clearDisplay();
  display.clearDisplay();

	display.setFont(font, 5,7);
	display.setTextWrap(true);
	display.setTextColor(WHITE, SOLID);

  display.setCursor(0, 0);
  display.print(F("SilverWolf \n\nBrightStar \n\n\n\npowered by \n\nSilverWolf Production"));

  pixels.begin();

  delay(1500);

  display.clearDisplay();
}

// Loop

void loop() {
  Serial.print("ping");
  VoltageMeter();
  getSatPot();
  getHuePot();
  getBrgPot();

  if (SatPct <= 1 && HuePct <= 1) {
    Menu();
    return;
  }

  if (modeclr == 1) {
    display.clearDisplay();
    modeclr = 0;
  }

  mnclr = 0;

  switch (mode) {
    case 1:
      NormalMode();
      break;
    case 2:
      Strobe();
      break;
    case 3:
      Police();
      break;
    case 4:
      Storm();
      break;
    case 5:
      Pulse();
      break;
    case 6:
      Fire();
      break;
    case 7:
      ClubLights();
      break;
    case 8:
      Flicker();
      break;
    case 9:
      Welding();
      break;
    case 10:
      CloudPass();
      break;
  }
}
