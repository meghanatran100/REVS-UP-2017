int xJoy = A8;
int yJoy = A9;
int buttonPin = 7;

int xPosition = 0;
int yPosition = 0;
int buttonState = 0;

void setup() 
{
  Serial.begin(115200);
  pinMode(xJoy,INPUT);
  pinMode(yJoy,INPUT);
  pinMode(buttonPin,INPUT_PULLUP);

}

void loop() 
{
  xPosition = analogRead(xJoy);
  yPosition = analogRead(yJoy);
  buttonState = digitalRead(buttonPin);
  Serial.print("X: ");
  Serial.print(xPosition);
  Serial.print(" | Y: ");
  Serial.print(yPosition);
  Serial.print(" | Button: ");
  Serial.println(buttonState);
  delay(100);
}
