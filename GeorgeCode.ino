#include <Servo.h>
Servo myservo;
#include "LedControl.h"
#include "binary.h"
#include "IRremote.h"
#include "DHT.h"
#define DHTPIN 1 
#define DHTTYPE DHT11   // DHT 11 
DHT dht(DHTPIN, DHTTYPE);

const int receiver = 2;
bool a = true;
int rand1 = 0;
int waitValue = 0;
int area = 0;
IRrecv IrReciever(receiver);     // create instance of 'irrecv'
decode_results results;
LedControl lc=LedControl(12,11,10,1);
int choosingFace = 0;

/* Reciever: +, -, 5 on y --
 * LightSensor: +, -, A9 --
 * Motor: +, -, 8 --
 * Face: DIN 12, CLK 11, CS 10
 * SoundSensor: d0 3, A0 A0 --
 * LED: 2, gnd, 5, 4 --
 * 
 */


//sad face
byte sf[8]= {B01100110, B10000001, B00100100, B00100100,B00000000,B00111100,B01000010,B00000000};
byte sfb[8]= {B01100110, B10000001, B00000000, B00100100,B00000000,B00111100,B01000010,B00000000};
byte sb[8]= {B01100110, B10000001, B00000000, B00000000,B00000000,B00111100,B01000010,B00000000};

//excited face
byte ef[8]= {B01100110, B00000000, B00100100, B00000000, B00111100, B00111100, B00011000, B00000000};
byte eb[8]= {B01100110, B00000000, B00000000, B00000000, B00111100, B00111100, B00011000, B00000000};

//neutral face
byte pf[8]= {B01100110, B00000000, B00100100, B00100100, B00000000, B00111100, B00000000, B00000000};
byte pb[8]= {B01100110, B00000000, B00000000, B00000000, B00100100, B00111100, B00000000, B00000000};
byte pfb[8]= {B01100110, B00000000, B00000000, B00000000, B00000000, B00111100, B00000000, B00000000};

//doneFace
byte df[8] = {B00000000, B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000};

int pos = 0; 
int sensorAnalogPin = A0;
int sensorDigitalPin = 3;
int analogValue = 0;
int digitalValue;
int LED13 = 13;
int timeset = 180;
int practiceVal = 0;
int HolderVal = 0;
int MeasureLight = A8;
int LightVal = 0;

void setup() {
  lc.shutdown(0,false);
  // Set brightness to a medium value
  lc.setIntensity(0,1);
  // Clear the display
  lc.clearDisplay(0);  
  Serial.begin(9600);
  IrReciever.enableIRIn();           // Start the receiver
  myservo.attach(8);  
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  pinMode(sensorDigitalPin, INPUT);
  pinMode(9, OUTPUT);
  digitalWrite(9, HIGH);
  pinMode(LED13, OUTPUT);
  for (int i = 0; i < 10; i++){
    analogValue = analogRead(sensorAnalogPin);
    practiceVal += analogValue;
    area += analogRead(MeasureLight);
  }
  area = area / 10;
  practiceVal = practiceVal/10;
  analogValue = 0;
  HolderVal = practiceVal;
  practiceVal = 0;
}

void loop() {
  if (IrReciever.decode()){
    if (a == false){
      a = true;
    }
    else{
      a = false;
    }
    
    IrReciever.resume();
  }
  if (a == true){
    activate();
  }
  else{
    deactivate();
  }
  delay(5);
}

///////////////////////////////////////
void ExcitedFace(){
  lc.setRow(0,0,ef[0]);
  lc.setRow(0,1,ef[1]);
  lc.setRow(0,2,ef[2]);
  lc.setRow(0,3,ef[3]);
  lc.setRow(0,4,ef[4]);
  lc.setRow(0,5,ef[5]);
  lc.setRow(0,6,ef[6]);
  lc.setRow(0,7,ef[7]);
}
void ExcitedFaceA(){
  lc.setRow(0,0,eb[0]);
  lc.setRow(0,1,eb[1]);
  lc.setRow(0,2,eb[2]);
  lc.setRow(0,3,eb[3]);
  lc.setRow(0,4,eb[4]);
  lc.setRow(0,5,eb[5]);
  lc.setRow(0,6,eb[6]);
  lc.setRow(0,7,eb[7]);
}
////////////////////////////////////
void NeutralFace(){
  lc.setRow(0,0,pf[0]);
  lc.setRow(0,1,pf[1]);
  lc.setRow(0,2,pf[2]);
  lc.setRow(0,3,pf[3]);
  lc.setRow(0,4,pf[4]);
  lc.setRow(0,5,pf[5]);
  lc.setRow(0,6,pf[6]);
  lc.setRow(0,7,pf[7]);
}
void NeutralFaceA(){ 
  lc.setRow(0,0,pfb[0]);
  lc.setRow(0,1,pfb[1]);
  lc.setRow(0,2,pfb[2]);
  lc.setRow(0,3,pfb[3]);
  lc.setRow(0,4,pfb[4]);
  lc.setRow(0,5,pfb[5]);
  lc.setRow(0,6,pfb[6]);
  lc.setRow(0,7,pfb[7]);
}
void NeutralFaceB(){
  lc.setRow(0,0,pb[0]);
  lc.setRow(0,1,pb[1]);
  lc.setRow(0,2,pb[2]);
  lc.setRow(0,3,pb[3]);
  lc.setRow(0,4,pb[4]);
  lc.setRow(0,5,pb[5]);
  lc.setRow(0,6,pb[6]);
  lc.setRow(0,7,pb[7]);
}
///////////////////////////////////////////////
void SadFace(){
  lc.setRow(0,0,sf[0]);
  lc.setRow(0,1,sf[1]);
  lc.setRow(0,2,sf[2]);
  lc.setRow(0,3,sf[3]);
  lc.setRow(0,4,sf[4]);
  lc.setRow(0,5,sf[5]);
  lc.setRow(0,6,sf[6]);
  lc.setRow(0,7,sf[7]);
}
void SadFaceA(){
  lc.setRow(0,0,sfb[0]);
  lc.setRow(0,1,sfb[1]);
  lc.setRow(0,2,sfb[2]);
  lc.setRow(0,3,sfb[3]);
  lc.setRow(0,4,sfb[4]);
  lc.setRow(0,5,sfb[5]);
  lc.setRow(0,6,sfb[6]);
  lc.setRow(0,7,sfb[7]);
}
void SadFaceB(){
  lc.setRow(0,0,sb[0]);
  lc.setRow(0,1,sb[1]);
  lc.setRow(0,2,sb[2]);
  lc.setRow(0,3,sb[3]);
  lc.setRow(0,4,sb[4]);
  lc.setRow(0,5,sb[5]);
  lc.setRow(0,6,sb[6]);
  lc.setRow(0,7,sb[7]);
}
void DoneFace(){
  lc.setRow(0, 0, df[0]);
  lc.setRow(0, 1, df[1]);
  lc.setRow(0, 2, df[2]);
  lc.setRow(0, 3, df[3]);
  lc.setRow(0, 4, df[4]);
  lc.setRow(0, 5, df[5]);
  lc.setRow(0, 6, df[6]);
  lc.setRow(0, 7, df[7]);
}
void deactivate(){
  digitalWrite(7, LOW);
  digitalWrite(6, LOW);
  lc.clearDisplay(0);  
  DoneFace();
}
void activate(){
  pinMode(sensorDigitalPin, INPUT);
  pinMode(LED13, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(2, INPUT);
  LightVal = analogRead(MeasureLight);
  Serial.println(LightVal);
  if (LightVal < area + 2){
    choosingFace = 1;
  }
  else if(LightVal >= area + 2 and LightVal < area + 100){
    choosingFace = 2;
  }
  else{
    choosingFace = 3;
  }
  if (choosingFace == 1){
    SadFace();
  }
  else if(choosingFace == 2){
    NeutralFace();
  }
  else{
    ExcitedFace();
  }
  analogValue =  analogRead(sensorAnalogPin);
  Serial.println(analogValue);
  if (abs(analogValue - HolderVal) > 15){
    for (int j = 0; j < 2; j++){
      for (int i = 0; i < 50; i++){
        pos = i;
        myservo.write(pos);
        delay(1);
      }
      for (int i = 50; i > 0; i--){
        pos = i;
        myservo.write(pos);
        delay(1);
      }
      SadFace();
    }
  }
  else if (dht.readTemperature(true) < 72){
    choosingFace = 1;
  }
  delay(700);
  if (choosingFace == 1){
      SadFaceA();
      delay(40);
      SadFaceB();
      delay(9);
  }
  else if(choosingFace == 2){
      NeutralFaceA();
      delay(40);
      NeutralFaceB();
      delay(9);
  }
  else{
      ExcitedFaceA();
      delay(18);
  }
}
