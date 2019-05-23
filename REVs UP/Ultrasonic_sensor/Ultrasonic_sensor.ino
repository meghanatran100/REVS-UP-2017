#include "DHT.h"

int trig = 31;
int echo = 33;
int distanceCm;
int distanceIn;
long duration;

void setup() 
{
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  Serial.begin(115200);

}

void loop() {
digitalWrite(trig,LOW);
  delayMicroseconds(5);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  duration = pulseIn(echo,HIGH);
  //distanceCm = duration * .034/2;
  distanceIn = duration * .0133/2;
  Serial.print("distance: ");
  Serial.println(distanceIn);
  delay(150);

}
