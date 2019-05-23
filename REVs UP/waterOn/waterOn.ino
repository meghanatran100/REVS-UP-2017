int rel5 = 12;
int rel1 = 8;
int flowSen = 6;

byte sensorInterrupt = 0;
byte sensorPin = 2;

float calibrationFactor = 4.5;
volatile byte pulseCount;  
float flowRate;
unsigned int flowMilliLitres;
unsigned int totalMilliLitres;
unsigned long oldTime;

void setup()

{
Serial.begin(115200);
  pulseCount        = 0;
  flowRate          = 0.0;
  flowMilliLitres   = 0;
  totalMilliLitres  = 0;
  oldTime           = 0;

  attachInterrupt(sensorInterrupt, pulseCounter2, FALLING);

  pinMode(rel1,OUTPUT);
  pinMode(rel5,OUTPUT);
  digitalWrite(rel1,HIGH);
  digitalWrite(rel5,HIGH);
  
}

void loop()
{
  char key;
  key = Serial.read();
  if (key == '1')
  {
    
    waterOn1(rel1);
    key=0;
  }
   delay(10);
  

 
}


void waterOn1(int relForPlant)
{
  const int fillTime = 2500;
  const int endTime = 2500;
  const int limitFilled = 100;
  pulseCount = 0;
  digitalWrite(rel5,LOW);

  

  delay(fillTime);
  digitalWrite(relForPlant,LOW);
  
  while(totalMilliLitres < limitFilled)
  {
   delay(10);
   
   if((millis() - oldTime) > 1000)
    {
      
      detachInterrupt(sensorInterrupt);
      flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
      oldTime = millis();
      flowMilliLitres = (flowRate / 60) * 1000;
      totalMilliLitres += flowMilliLitres;
      Serial.print("  Output Liquid Quantity: ");            
      Serial.print(totalMilliLitres);
      Serial.println("mL");
      Serial.println(flowMilliLitres);
      Serial.println(flowRate);
      Serial.println(oldTime); 
      pulseCount = 0;
      attachInterrupt(sensorInterrupt, pulseCounter2, FALLING);
    }
    
   
  }
  digitalWrite(relForPlant,HIGH);
  delay(endTime);
  digitalWrite(rel5,HIGH);
  totalMilliLitres = 0;
  flowMilliLitres = 0;
  flowRate = 0.0;
  
  Serial.print("  Output Liquid Quantity: ");            
      Serial.print(totalMilliLitres);
      Serial.println("mL");
      Serial.println(flowMilliLitres);
      Serial.println(flowRate);
      Serial.println(oldTime); 

}

void floodPipes(int 
{
  const int floodTime = 3000;
}

void pulseCounter2()
{
  pulseCount++;
}
