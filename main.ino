#include <LiquidCrystal.h>
#include <Adafruit_NeoPixel.h>

const int temp = A2;
const int moisturePin = A3;
const int water = 6;
const int waterButton = 13;
const int trigPin = 9;
const int echoPin = 10;
const int bright = A2;
const int led = 1;

int NUMPIXELS = 60;

unsigned long startMillis;
unsigned long getValueMillis = 0;
unsigned long eventMillis = 0;
unsigned long waitWater = 10000;                      //da aggiornare
unsigned long eventOpenWater = 0;
unsigned long stopWater = 6000;                     //da aggiornare
unsigned long ultrasonic_millis = 0;
unsigned long ultrasonic2_millis = 0;
unsigned int sonic_done = 0;
unsigned int open_water = 0;
unsigned int trigSonic = 0;
unsigned int duration = 0;
unsigned int maxDistance = 0;                       //da aggiornare
unsigned int minMoisture = 0;                       //da aggiornare
unsigned long timer = 0;
unsigned long myTimer = 0;
int cont = 0;
int delayval = 100;
unsigned long aux = 0;
int timerOver = 0;

int tempLCD;
int umidLCD;
int lumLCD;

int tempMap, valTemp;
int distance = 0;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, led, NEO_GRB + NEO_KHZ800);

float moisture = 0;
int tmp_moisture = 0;
int brightness = 0;
String final_str;

void setup() {
  pinMode(temp, INPUT);
  pinMode(moisturePin, INPUT);
  pinMode(water, OUTPUT); 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  lcd.begin(16, 2);
  pixels.begin();
 
  for(int i=0;i<NUMPIXELS;i++){
      pixels.setPixelColor(i, pixels.Color(254,254,254));
      pixels.show();
  }
 
  Serial.begin(9600);
  startMillis = millis();
}

void loop() {
  if (getValueMillis + 5000 <= millis() || getValueMillis == 0){                     
    moisture = analogRead(moisturePin);
    moisture = moisture /876.0 * 100;       //controlla mapping

    valTemp = analogRead(temp);
    tempMap = map(valTemp,20,358,-40,125);  //controlla mapping 
      
    tmp_moisture = int(moisture);

    brightness = analogRead(bright);

    tempLCD = tempMap;
    umidLCD = tmp_moisture;
    lumLCD = brightness;

    final_str = String(tmp_moisture) + "," + String(tempMap) + "," + String(distance) + ",";

    getValueMillis = millis();

    //Serial.println(final_str);
    Serial.flush();
  }

  /* ------ WATER ------ */

  if (/*moisture < minMoisture && */0 == 1 && eventMillis + waitWater <= millis() && open_water == 0 && distance < maxDistance){
    digitalWrite(water, HIGH);           
    open_water = 1;
    eventOpenWater = millis();
  }

  if (eventOpenWater + stopWater <= millis() && open_water == 1){
    digitalWrite(water, LOW);
    open_water = 0;
    eventMillis = millis();
  }

  if(Serial.available()){
    char read = Serial.read();
    if (read == 'a' && open_water == 0 && distance > maxDistance){
      digitalWrite(water, HIGH);
      open_water = 1;
      eventOpenWater = millis();
      eventMillis = millis();
    }
  }

  if(digitalRead(waterButton) == HIGH && open_water == 0  && distance > maxDistance){
    digitalWrite(water, HIGH);
    open_water = 1;
    eventOpenWater = millis();
    eventMillis = millis();
  }
  

  /* ------ ULTRASONIC ------ */
  
  if (ultrasonic_millis + 0.002 <= millis() && trigSonic == 0){
    digitalWrite(trigPin, LOW);
    digitalWrite(trigPin, HIGH);
    ultrasonic_millis = millis();
    trigSonic = 1;
  }
  if (ultrasonic2_millis + 0.01 <= millis() && trigSonic == 1){
    digitalWrite(trigPin, LOW);
    ultrasonic2_millis = millis();
    trigSonic = 0;
    sonic_done = 1;
  }

  if (sonic_done == 1){
    duration = pulseIn(echoPin, HIGH);
    distance = (duration*.0343)/2;
    sonic_done = 0;
  }

  /* ------ LCD ------ */
  timer=millis();
  myTimer=timer-cont*aux;

  if(myTimer > 0 && myTimer<5000){
    timerOver = 0;
    lcd.setCursor(0, 0);
    lcd.print("   Serra  ITS");
    lcd.setCursor(0, 1);
    lcd.print("Temperatura: ");
    lcd.setCursor(13, 1);
    lcd.print(tempLCD);    
  }

  if(myTimer>5000 && myTimer<5200)
    lcd.clear();

   if(myTimer >= 5200 && myTimer<10200){
    lcd.setCursor(0, 0);
    lcd.print("   Serra  ITS");
    lcd.setCursor(0, 1);
    lcd.print("Umidita':    ");
    lcd.setCursor(13, 1);
    lcd.print(umidLCD);
  }

  if(myTimer>10200 && myTimer<10400)
    lcd.clear();
  
  if(myTimer>10400 && myTimer<15400){;
    lcd.setCursor(0, 0);
    lcd.print("   Serra  ITS");
    lcd.setCursor(0, 1);
    lcd.print("Luminosita': ");
    lcd.setCursor(13, 1);
    lcd.print(lumLCD);
  }

  if(myTimer>15400 && timerOver == 0){
    cont=cont+1;
    lcd.clear();
    aux = myTimer;
    timerOver = 1;
  }
}
