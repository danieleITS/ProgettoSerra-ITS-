#include <LiquidCrystal.h>

TEMP "A0"           //controlla pin
MOISTURE "A1"
WATER "6"
BRIGHTNESS "A2"
LIGHT "7"
ULTRASONIC_TRIGGER "9"
ULTRASONIC_ECHO "10"
LED_WATER "13"

unsigned long startMillis;
unsigned long eventMillis = 0;
unsigned long waitWater = 180000;


int tempMap, valTemp;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);      //controlla pin

float moisture;

int const full_capacity = 20;   //da modificare con l'altezza in cm del serbatoio 
int const low_water_level = 6;  //da modificare con il livello acqua basso
int water_level_perc;
long ultrasound_duration, water_level;

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
    pinMode(LED_WATER, OUTPUT);

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

    //controllo livello serbatoio con ultrasuoni
    if (count == 30000){
        digitalWrite(ULTRASONIC_TRIGGER, LOW);
        delayMicroseconds(2);
        digitalWrite(ULTRASONIC_TRIGGER, HIGH);
        delayMicroseconds(10);
        digitalWrite(ULTRASONIC_TRIGGER, LOW);
        ultrasound_duration = pulseIn(ULTRASONIC_ECHO, HIGH);
        water_level = full_capacity-(ultrasound_duration / 58);
        water_level_perc = (water_level/full_capacity)*100;
        Serial.println(water_level);

    }
    
    //controllo per l'accensione del led di avviso per l'acqua bassa
    if(water_level <= low_water_level){
        digitalWrite(LED_WATER, HIGH);
    } else {
        digitalWrite(LED_WATER, LOW);
    }


    //gestione pompa
    if ((moisture < 60.00 && eventMillis + waitWater <= millis())){
        digitalWrite(WATER, HIGH);           //ANALOG O DIGITAL??
        delay();                            //TROVA POSSIBILE ALTERNATIVA CON MILLIS
        digitalWrite(WATER, LOW);
        eventMillis = millis();
    }

    //if di test???
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

/*
#CHECKLIST
## sensori da implementare
1) Temperatura 
2) umidità
3) ultrasuoni
4) luce

##LCD
1) temperatura
2) umidità
3) livello acqua + led rosso per livello basso

##APP
    */