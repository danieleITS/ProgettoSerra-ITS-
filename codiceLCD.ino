#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 int tempLCD;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(9600);
 
}

void loop() {
 
  int valTemp = analogRead(1);
  Serial.println(tempLCD);
  
  tempLCD=map(valTemp,20,358,-40,125);
  
  lcd.setCursor(0, 0);
  lcd.print("Temperatura: ");
  lcd.setCursor(13, 0);
  lcd.print(tempLCD);
  delay(1000);
  lcd.clear();
  
}