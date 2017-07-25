#include <UnoWiFiDevEd.h>
#include <Wire.h>
#define CONNECTOR "rest"
#define SERVER_ADDR "158.108.165.223"
#define SWITCH 2
#define MOTION 8

String UPLOAD;
String writeSwitch = "/data/group13/1/set/";
String writeMotion = "/data/group13/2/set/";
CiaoData data;

int switchDetect = 0;
int motionDetect = 0;

void switchPress(){
  switchDetect = !digitalRead(SWITCH);
  if (switchDetect){
    motionDetect = digitalRead(MOTION);
  }
  else motionDetect = 0;
  UPLOAD = writeSwitch + String(switchDetect);
  data = Ciao.write(CONNECTOR, SERVER_ADDR, UPLOAD);
  if (data.isEmpty()) Serial.println(F("A_Failed"));
  else Serial.println("A " + String(data.get(2)));
  UPLOAD = writeMotion + String(motionDetect);
//  Serial.println(UPLOAD);
  data = Ciao.write(CONNECTOR, SERVER_ADDR, UPLOAD);
  if (data.isEmpty()) Serial.println(F("B_Failed"));
  else Serial.println("B " + String(data.get(2)));
  Serial.print(switchDetect);
  Serial.print(" ");
  Serial.println(motionDetect);
}

void setup() {
  Serial.begin(9600);
  Ciao.begin();
  pinMode(SWITCH, INPUT);
  pinMode(MOTION, INPUT);
  switchDetect = 0;
  motionDetect = 0;
}

void loop() {
  switchPress();
  delay(1000);
}
