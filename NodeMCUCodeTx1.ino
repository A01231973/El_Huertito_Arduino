//Arduino code
#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial s(10 ,6);

#define HUMEDAD A0 //declaracion del sensor de humedad
int LecturaHumedad=0;// variable para las lecturas del sensor humedad

#define TEMP A1 //declaracion del sensor de humedad
int LecturaTemp=0;// variable para las lecturas del sensor humedad

Servo regador; //servomotor regador
Servo vent; //servomotor regador
int angulo;//angulo que se mueve el servo
int angulo1;//angulo que se mueve el servo


 
void setup() {
Serial.begin(9600);
s.begin(9600);

pinMode(HUMEDAD, INPUT);
pinMode(TEMP, INPUT);

regador.attach(4);
regador.write(0);

vent.attach(3);
vent.write(0);
}
 
void loop() {
LecturaHumedad=analogRead(HUMEDAD);
LecturaTemp=analogRead(TEMP);
if(s.available()>0)
{
 s.write(LecturaTemp);
 s.write(LecturaHumedad);
 delay (10);
}

if (LecturaHumedad>700){
  for (angulo=0; angulo<180; angulo+=1){
    regador.write(angulo);
    delay (10);
  }
}

if (LecturaTemp>70){
  for (angulo1=0; angulo1<180; angulo1+=1){
    vent.write(angulo1);
    delay (10);
  }
}
}
