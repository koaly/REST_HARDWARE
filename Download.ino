#include <Servo.h>
#include <pt.h>
#include <UnoWiFiDevEd.h>
#include <Wire.h>
#define CONNECTOR "rest"
#define SERVER_ADDR "158.108.165.223"
#define PT_DELAY(pt, ms, ts)\
        ts = millis();\
        PT_WAIT_WHILE(pt,millis()-ts < (ms));
#define SERVO 5
#define BUZZER 6
Servo Sv;

char readServo[]  = "/data/group13/3/";
char readBuzzer[] = "/data/group13/4/";
CiaoData data;

//int tts; //time to spin!!!
String tts;
struct pt pt_taskOpenServo;
PT_THREAD(OpenServo(struct pt* pt)){
  static uint32_t ts;
  PT_BEGIN(pt);
  while(1){
    Serial.print("AAA ");
    Serial.println(tts);
    if (tts == "1"){
      Serial.println("SERVO_ON");
      Sv.write(30);
      PT_DELAY(pt, 500, ts);
      Sv.write(60);
      PT_DELAY(pt, 500, ts);
    }
    else {
      Serial.println("SERVO_OFF");
      PT_DELAY(pt, 1000, ts);
    }
  PT_END(pt);
  }
}

//int ttb;// time to beep!!!
String ttb;
struct pt pt_taskOpenBuzz;
PT_THREAD(OpenBuzz(struct pt* pt)){
  static uint32_t ts;
  PT_BEGIN(pt);
  while(1){
    Serial.print("BBB ");
    Serial.println(ttb);
    if (ttb == "1"){
      analogWrite(BUZZER, 10);
      Serial.println("BUZZER_ON");
    }
    else{
      analogWrite(BUZZER, 0); 
      Serial.println("BUZZER_OFF");
    }
    PT_DELAY(pt, 1000, ts);
  PT_END(pt);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Ciao.begin();
  pinMode(BUZZER, OUTPUT);
  pinMode(SERVO , OUTPUT);
  Sv.attach(SERVO);
  PT_INIT(&pt_taskOpenServo);
  PT_INIT(&pt_taskOpenBuzz);
}

void loop() {
  data = Ciao.read(CONNECTOR, SERVER_ADDR, readServo);
  tts = (String) data.get(2);
  if (data.isEmpty()) Serial.println("SERVO_FAILED");
 // else Serial.println(tts);
  data = Ciao.read(CONNECTOR, SERVER_ADDR, readBuzzer);
  ttb = (String) data.get(2);
  if (data.isEmpty()) Serial.println("BUZZER_FAILED");
 // else Serial.println(tts);
  OpenServo(&pt_taskOpenServo);
  OpenBuzz(&pt_taskOpenBuzz);
  delay(1000);
}
