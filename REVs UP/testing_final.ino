int moistSen1 = 0;
int moistSen2 = 0;
int moistSen3 = 0;
int moistSen4 = 0;



int relV1 = 3;          //valve1
int relV2 = 4;          //valve2
int relV3 = 5;          //vslve3
int relV4 = 6;          //valve4
int relP5 = 7;          //pump

void setup() {
  Serial.begin(115200);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop() {
 
 moistSen1 = analogRead(A1);
 moistSen2 = analogRead(A2);
 moistSen3 = analogRead(A3);
 moistSen4 = analogRead(A4);

 moistSen1 = map(moistSen1,350,1023,0,500);    //makes the moisture sensors read on a range form 0(wet) to 500(dry)
 moistSen2 = map(moistSen2,350,1023,0,500);
 moistSen3 = map(moistSen3,350,1023,0,500);
 moistSen4 = map(moistSen4,350,1023,0,500);

 digitalWrite(relV1,HIGH);
 digitalWrite(relV2,HIGH);
 digitalWrite(relV3,HIGH);
 digitalWrite(relV4,HIGH);
 digitalWrite(relP5,HIGH);
 
 Serial.println();
 Serial.println("Moisture 1: ");
 Serial.print(moistSen1);
 Serial.println();
 Serial.println("Moisture 2: ");
 Serial.print(moistSen2);
 Serial.println();
 Serial.println("Moisture 3: ");
 Serial.print(moistSen3);
 Serial.println();
 Serial.println("Moisture 4: ");
 Serial.print(moistSen4);
 
 delay(5000);
while(true){
 if(moistSen1 > 415) {
  digitalWrite(relP5, LOW);
  digitalWrite(relV1, LOW);
  delay(5000);
  digitalWrite(relP5, HIGH);
  digitalWrite(relV1, HIGH);
 }
 else if(moistSen2 > 475) {
  digitalWrite(relP5, LOW);
  digitalWrite(relV2, LOW);
  delay(5000);
  digitalWrite(relP5, HIGH);
  digitalWrite(relV2, HIGH);
 }
 else if(moistSen3 > 425) {
  digitalWrite(relP5, LOW);
  digitalWrite(relV3, LOW);
  delay(5000);
  digitalWrite(relP5, HIGH);
  digitalWrite(relV3, HIGH);
 }
 else if(moistSen4 > 475) {
  digitalWrite(relP5, LOW);
  digitalWrite(relV4, LOW);
  delay(5000);
  digitalWrite(relP5, HIGH);
  digitalWrite(relV4, HIGH);
 }
 delay(60000);
}
}
