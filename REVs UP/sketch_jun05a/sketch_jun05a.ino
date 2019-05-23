int led = 7;
int therm = 0;
int value;
int del;
void setup() 
{
  Serial.begin(115200);
  pinMode(led,OUTPUT);
}

void loop() 
{
  
  therm = analogRead(0);
  Serial.println(therm);
  delay(250);
 /*
  del = 2000/(therm - 334);
  digitalWrite(led,HIGH);
  delay(del);
  digitalWrite(led,LOW);
  delay(del);
  */
}
