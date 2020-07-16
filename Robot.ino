#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial myterminal(2,3);
Servo servo_2;
int cmR = 0;
int cmL = 0;
int cm = 0;
int enA = 12;                   
int in1 = 11;                   
int in2 = 10;                    
int enB = 4;               
int in3 = 6;                   
int in4 = 5;
String voice; 
int test= 0;
int pos;
Servo servo_tete;
Servo servo_gauche;
Servo servo_droite;
void setup()
{
  myterminal.begin(9600);
  servo_2.attach(7);
  servo_2.write(90);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);         
  pinMode(in1, OUTPUT);        
  pinMode(in2, OUTPUT);                
  pinMode(in3, OUTPUT);        
  pinMode(in4, OUTPUT);
  digitalWrite(enA,HIGH);
  digitalWrite(enB,HIGH);
  servo_tete.attach(13);
  servo_gauche.attach(A3);
  servo_droite.attach(A2);
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  Serial.begin(9600);
  servo_droite.write(0);
  servo_gauche.write(0);
  servo_tete.write(90);
}
void loop()
{
  cm = 0.01723 * readUltrasoniccm(9,8);

   while (Serial.available())
  { 
  delay(10); 
  char c = Serial.read(); 
  voice += c; 
  }  
  if (voice.length() > 0)
  {
    Serial.println(voice); 
       if(voice == "right hand up" || voice == "main droite en haut" || voice == "اليد اليمنى للاعلى")
       {for (pos = 0; pos <= 90; pos += 1) {
           servo_droite.write(pos);
        }  
       }if(voice == "left hand up"|| voice == "main gauche en haut" || voice == "اليد اليسرى للاعلى"){
        for (pos = 0; pos <= 90; pos += 1) {
           servo_gauche.write(pos);
        } 
        }if(voice == "right hand down" || voice == "main droite en bas" || voice == "اليد اليمنى للاسفل")
       {for (pos = 90; pos >= 0; pos -= 1) {
           servo_droite.write(pos);
        }  
       }if(voice == "left hand down"|| voice == "main gauche en bas" || voice == "اليد اليسرى للاسفل"){
        for (pos = 90; pos >= 0; pos -= 1) {
           servo_gauche.write(pos);
        }  }
         if(voice == "head to the right" || voice == "tête à droite" || voice == "الراس يمينا")
       {for (pos = 90; pos >= 0; pos -= 1) {
           servo_tete.write(pos);
        }  
       }if(voice == "head to the left"|| voice == "tête à gauche" || voice == "الراس يسارا"){
        for (pos = 90; pos <= 180; pos += 1) {
           servo_tete.write(pos);
        } 
        } 
        if(voice == "head to the center"|| voice == "la tête au centre" || voice == "الراس في الوسط"){
           servo_tete.write(90);
        } 
        if(voice == "hands up" || voice == "les mains en haut" || voice == "اليدان للاعلى")
       {for (pos = 0; pos <= 90; pos += 1) {
           servo_droite.write(pos);
           servo_gauche.write(pos);
        }  
       }if(voice == "hands down"|| voice == "les mains en bas" || voice == "اليدان للاسفل"){
        for (pos = 90; pos >= 0; pos -= 1) {
           servo_droite.write(pos);
           servo_gauche.write(pos);
        }  }
     if(voice == "démarre"|| voice =="move"|| voice =="انطلق"){
     test=1;
     moveforward();
     }
     if(voice == "arrête"|| voice =="stop"|| voice =="توقف"){
     test=0;
     Stop();
     }
  if (test==1){
     if(voice == "avance"|| voice =="move forward"|| voice =="تحرك الى الامام"){
     moveforward();
     }
     if(voice == "tourner à droite"|| voice =="move to right"|| voice =="تحرك يمينا"){
     moveRight();
     delay(1000);
     moveforward();
     }
     if(voice == "tourner à gauche"|| voice =="move to left"|| voice =="تحرك يسارا"){
     moveLeft();
     delay(1000);
     moveforward();
     }
     if(voice == "recule"|| voice =="move backward"|| voice =="تحرك الى الخلف"){
     movebackward();
     }
  }
     
  voice="";
 }
     if(test !=0){
     myterminal.print("distance en cm : ");
     myterminal.println(cm);
     obstacle_detection();
     }
  delay(200);
}
long readUltrasoniccm(int triggerPin, int echoPin){
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}
int lookRight()
{
    servo_2.write(0);
    delay(300);
    int cm_1= 0.01723 * readUltrasoniccm(9,8);
    delay(100);
    return cm_1;
}
int lookLeft()
{
    servo_2.write(180);
    delay(300);
    int cm_1= 0.01723 * readUltrasoniccm(9,8);
    delay(100);
    return cm_1;
}
void moveforward(){   
  digitalWrite(in1,LOW);    
  digitalWrite(in2,HIGH);   
  digitalWrite(in4,LOW);    
  digitalWrite(in3,HIGH); 
}

void Stop(){
  digitalWrite(in1,LOW);    
  digitalWrite(in2,LOW);   
  digitalWrite(in3,LOW);    
  digitalWrite(in4,LOW);
}

void moveRight(){   
  digitalWrite(in1,LOW);    
  digitalWrite(in2,LOW);   
  digitalWrite(in4,LOW);    
  digitalWrite(in3,HIGH); 
}
void moveLeft(){   
  digitalWrite(in1,LOW);    
  digitalWrite(in2,HIGH);   
  digitalWrite(in4,LOW);    
  digitalWrite(in3,LOW); 
}
void movebackward(){
  digitalWrite(in1,HIGH);    
  digitalWrite(in2,LOW);   
  digitalWrite(in4,HIGH);    
  digitalWrite(in3,LOW);
}
void obstacle_detection(){
  if ( cm < 20 ){
   Stop();
   cmR = lookRight();
   cmL = lookLeft();
   if (cmR >= cmL){
    movebackward();
    delay(500);
    moveRight();
    delay(500);
    moveforward();
   }else {
    movebackward();
    delay(500);
    moveLeft();
    delay(500);
    moveforward();
   }
 }
}
