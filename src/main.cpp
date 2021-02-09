#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

int ThermistorPin = A0;
float Vo;
float R1 = 10000; // value of R1 on board
float logR2, R2, Kelvin, Celsius, Farenheit;
float A = 0.001129148, B = 0.000234125, C = 0.0000000876741; //steinhart-hart coeficients for thermistor

void setup() {
  pinMode(ThermistorPin, INPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("*Thermistor  Sensor*");

  lcd.setCursor(0, 1);
  lcd.print("Kelvin: ");

  lcd.setCursor(0, 2);
  lcd.print("Celsius: ");

  lcd.setCursor(0, 3);
  lcd.print("Farenheit: ");
}

void loop() {
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / Vo - 1.0); //calculate resistance on thermistor
  logR2 = log(R2);
  Kelvin = (1.0 / (A + B*logR2 + C*pow(logR2, 3))); // temperature in Kelvin
  lcd.setCursor(8, 1);
  lcd.print(Kelvin);

  Celsius = Kelvin - 273.15; //convert Kelvin to Celcius
  lcd.setCursor(9, 2);
  lcd.print(Celsius);

  Farenheit = Celsius * (9 / 5) + 32.0; //convert Celcius to Farenheit
  lcd.setCursor(11, 3);
  lcd.print(Farenheit);

  delay(500);
}
