import controlP5.*;
import processing.serial.*;
import gifAnimation.*;

int WIDTH = 1024;
int HEIGHT = 576;
int N = 100;
float RADIUS = HEIGHT/10;
float SPEED = 0.0003;
float FOCAL_LENGTH = 0.3;
float BLUR_AMOUNT = 60;
int MIN_BLUR_LEVELS = 2;
int BLUR_LEVEL_COUNT = 8;
float ZSTEP = 0.008;
color BACKGROUND = color(0, 30, 30);

String str; //DEBUGGINg

Serial port;
ControlP5 cp5;

Textlabel title, 
          humidity, humidity_val,
          temperature, temperature_val,
          brightness, brightness_val,
          water_label;
Button water;
Animation loadingAnimation;

ArrayList objects;

float xoffs = 0;
float yoffs = 0;


void setup(){
   size(1024,576);
   port = new Serial(this, "COM4", 9600);
   cp5 = new ControlP5(this);
   
   
   water = cp5.addButton("ACQUA")    
             .setPosition(375,400)
             .setSize(240,80)
             .setFont(createFont("Montserrat.otf",25))
             ;
   
   title = cp5.addTextlabel("label")
                    .setText("Progetto ITS Corso IoT 12.1")
                    .setPosition(270,30)
                    .setColorValue(#53D8FB)
                    .setFont(createFont("Montserrat.otf",35))
                    ;
   
   humidity = cp5.addTextlabel("label1")
                    .setText("Umidità:")
                    .setPosition(50,150)
                    .setColorValue(#53D8FB)
                    .setFont(createFont("Montserrat.otf",20))
                    ;
   
   humidity_val =  cp5.addTextlabel("label3")
                     .setText("---")
                     .setPosition(52, 180)
                     .setFont(createFont("Montserrat.otf",17))
                     ;
                     
  temperature =  cp5.addTextlabel("label4")
                     .setText("Temperatura:")
                     .setPosition(400, 150)
                    .setColorValue(#53D8FB)
                    .setFont(createFont("Montserrat.otf",20))
                     ;
                     
  temperature_val =  cp5.addTextlabel("label5")
                     .setText("---")
                     .setPosition(402, 180)
                     .setFont(createFont("Montserrat.otf",17))
                     ;
            
  brightness =  cp5.addTextlabel("label6")
                     .setText("Luminosità:")
                     .setPosition(780, 150)
                     .setColorValue(#53D8FB)
                     .setFont(createFont("Montserrat.otf",20))
                     ;
                     
  brightness_val =  cp5.addTextlabel("label7")
                     .setText("---")
                     .setPosition(782, 180)
                     .setFont(createFont("Montserrat.otf",17))
                     ;
                     
  water_label = cp5.addTextlabel("label8")
                .setText("Versa l'acqua manualmente")
                .setPosition(350,350)
                .setFont(createFont("Montserrat.otf",20))
                .setColorValue(#53D8FB)
                ;
                
  frameRate(30);
  loadingAnimation = new Animation(12);
  
  smooth();
  noStroke();
   
  objects = new ArrayList();
  for (int i=0; i<N; i++) {
      objects.add(new ZObject(random(1.0), random(1.0), random(1.0), color(random(20.0, 20.0), random(150.0, 190.0), random(150.0, 190.0))));
  }
  
  sortBubbles();
   
}

void draw(){
  background(BACKGROUND);
  
  xoffs = xoffs*0.9 + 0.1*simX()/WIDTH;
  yoffs = yoffs*0.9 + 0.1*simY()/HEIGHT;
    
 
  for (int i=0; i<N; i++) {
    ((ZObject)objects.get(i)).draw(xoffs, yoffs);
  }
  
  fill(#4D4D4D);
  rect(162, 20, 700, 70, 28); //title box
  rect(40, 137, 220, 80, 28); //umidity box
  rect(388, 137, 220, 80, 28); //temperature box
  rect(767, 137, 205, 80, 28); //brightness box
  rect(326, 340, 335, 50, 28); //brightness box
  loadingAnimation.display(100,183);
  
  if (port.available() > 0){
    str = port.readString();
    port.clear();
    humidity_val.setValue(str);
    println("String: " + str);
  }
  
}

void ACQUA(){
  
 port.write('a');

}
