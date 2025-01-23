int PUL=3; //define Pulse pin
int DIR=2; //define Direction pin
//int ENA=8; //define Enable Pin

void setup() {
  pinMode (PUL, OUTPUT);
  pinMode (DIR, OUTPUT);
  //pinMode (ENA, OUTPUT);
  //digitalWrite(ENA, LOW);
  digitalWrite(DIR,HIGH);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(DIR, HIGH);
  int adc = analogRead(A2);
  Serial.println(adc);
    for(int x=0; x<800; x++){
      digitalWrite(PUL,HIGH);
      delayMicroseconds(500);
      digitalWrite(PUL,LOW);
      delayMicroseconds(500);
    }
    delay(100);
 
 
 
 /*
  for (int i=0; i<6400; i++)    //Forward 6400 steps
  {
    digitalWrite(DIR,LOW);
    digitalWrite(ENA,HIGH);
    digitalWrite(PUL,HIGH);
    delayMicroseconds(100);
    digitalWrite(PUL,LOW);
    delayMicroseconds(100);
  }
  for (int i=0; i<6400; i++)   //Backward 6400 steps
  {
    digitalWrite(DIR,HIGH);
    digitalWrite(ENA,HIGH);
    digitalWrite(PUL,HIGH);
    delayMicroseconds(100);
    digitalWrite(PUL,LOW);
    delayMicroseconds(100);
  }
  */
}
