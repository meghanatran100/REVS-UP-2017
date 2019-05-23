#include <IRremote.h>


int trig = 31;
int echo = 33;
int distanceCm;
int distanceIn;
long duration;
int buzz = 6;
int RECV_PIN = 4;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup() 
{
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  Serial.begin(9600);
  pinMode(buzz,OUTPUT);
  irrecv.enableIRIn();
}

void loop()
{
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
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
  delay(100);


 //tone(buzz,duration); 
  
}





