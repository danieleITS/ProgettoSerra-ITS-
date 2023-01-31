#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 int tempLCD;
 int umidLCD;
 int lumLCD;
 LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 unsigned long millisPrecedente = 0;
 
 void setup() {
 lcd.begin(16, 2);
 Serial.begin(9600);
 

}

void loop() {
  
  int valLum = analogRead(0);
  int valTemp = analogRead(1);
  int valUmid = analogRead(2);
  
  //Serial.println(tempLCD);
  
  tempLCD=map(valTemp,20,358,-40,125);
  
  if(millis() - millisPrecedente > 2000){
  	millisPrecedente=millis();
    lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   Serra  ITS");
  lcd.setCursor(0, 1);
  lcd.print("Temperatura: ");
  lcd.setCursor(13, 1);
  lcd.print(tempLCD);
    
  
  }
  
  umidLCD=map(valUmid,0,100,0,100);
  
  if(millis() - millisPrecedente > 2000){
    millisPrecedente=millis();
  	lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   Serra  ITS");
  lcd.setCursor(0, 1);
  lcd.print("Umidita': ");
  lcd.setCursor(13, 1);
  lcd.print(umidLCD);
  
  
  
  
  }
  
  lumLCD=map(valLum,0,100,0,100);
  
  if(millis() - millisPrecedente > 2000){
   	millisPrecedente=millis();
  	lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   Serra  ITS");
  lcd.setCursor(0, 1);
  lcd.print("Luminosita': ");
  lcd.setCursor(13, 1);
  lcd.print(lumLCD);
 
  }
  

    

  Serial.println(millisPrecedente);
}