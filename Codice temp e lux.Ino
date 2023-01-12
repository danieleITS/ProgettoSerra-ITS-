int const nightLed = 450;
int Led = 2;
int pinLux = A0;
int pinTemp = A1;
int luxValue = 0;
int tempValue=0;

void setup() {
  Serial.begin(9600);
  
  pinMode(pinLux, INPUT);
  pinMode(pinTemp, INPUT);
  pinMode(Led,OUTPUT);
  
}
 
void loop() {
  luxValue = analogRead(pinLux);
  tempValue = analogRead(pinTemp);
  tempValue = map(tempValue,20,358,-40,125);
  
  Serial.println("\n");
  Serial.print("temp = ");
  Serial.println(tempValue);
  
  if(luxValue < nightLed){
    digitalWrite(Led,HIGH);
  	Serial.print("lux = " );
  	Serial.println("Luce accesa");
  	
  }
  else{
    digitalWrite(Led,LOW);
  	Serial.print("lux = " );
  	Serial.println("Luce spenta");
  	
  }
  
  delay(1000);
}