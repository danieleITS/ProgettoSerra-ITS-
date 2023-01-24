#include <LiquidCrystal.h>

TEMP "A0"           //controlla pin
MOISTURE "A1"
WATER "6"
BRIGHTNESS "A2"
LIGHT "7"
ULTRASONIC_TRIGGER "9"
ULTRASONIC_ECHO "10"

unsigned long startMillis;
unsigned long eventMillis = 0;
unsigned long waitWater = 180000;

int tempMap, valTemp;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);      //controlla pin

float moisture;

int const nightLed = 450;
int luxValue = 0;

String final_str;

void setup() {
    pinMode(TEMP, INPUT);
    pinMode(MOISTURE, INPUT);
    pinMode(WATER, OUTPUT);
    pinMode(BRIGHTNESS, INPUT);  //modifica con umidità dell'aria ???
    pinMode(LIGHT, OUTPUT);
    pinMode(ULTRASONIC_TRIGGER, OUTPUT);
    pinMode(ULTRASONIC_ECHO, INPUT);

    lcd.begin(16, 2);
    Serial.begin(9600);
    startMillis = millis();
}

void loop() {

    count = count + 1;

    // stampa valori utili a schermo
    if (count == 30000){                        //implementabile con millis()
        moisture = analogRead(MOISTURE);
        moisture = moisture /876.0 * 100;

        valTemp = analogRead(TEMP);
        tempMap = map(valTemp,20,358,-40,125);  //controlla mapping temperatura

        luxValue = analogRead(BRIGHTNESS);
        if(luxValue < nightLed){
            digitalWrite(LIGHT,HIGH);
        }
        else{
            digitalWrite(LIGHT,LOW);
        }
        
        tmp_moisture = int(moisture);
        final_str = String(tmp_moisture) + "," + String(tempMap) + "," + String(luxValue) + ",";
        //inserire livello acqua al posto della luminosità

        count = 0;  
        Serial.println(final_str);  //FAI PARSING SU PROCESSING
    }

    //
    if ((moisture < 60.00 && eventMillis + waitWater <= millis())){
        digitalWrite(WATER, HIGH);           //ANALOG O DIGITAL??
        delay();                            //TROVA POSSIBILE ALTERNATIVA CON MILLIS
        digitalWrite(WATER, LOW);
        eventMillis = millis();
    }

    if(Serial.available()){
        char read = Serial.read();
        if (read == 'a'){
            digitalWrite(WATER, HIGH);           //ANALOG O DIGITAL??
            delay();                             //TROVA POSSIBILE ALTERNATIVA CON MILLIS
            digitalWrite(WATER, LOW);
            eventMillis = millis();
        }
    }

    //GESTIONE LCD
}