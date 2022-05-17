#include <Arduino.h>
#include "ArduinoTimer/Timer.h"
#include "OneButton.h"

Timer t;
uint8_t id;
byte b;
int state;

OneButton btn1(A1);
OneButton btn2(A2);
OneButton btn3(A3);

void blink() {
  state = !state;
  digitalWrite(LED_BUILTIN, state);
}

void initTimer() {
  Serial.println("timer initialized");
  id = t.every(1000, blink);
}

void startTimer() {
  Serial.println("timer started");
  t.start(id);
}

void pauseTimer() {
  Serial.println("timer paused");
  t.pause(id);
}

void resumeTimer() {
  Serial.println("timer resumed");
  t.resume(id);
}

void stopTimer(){
  Serial.println("timer stopped");
  t.stop(id);
}

void clearTimer() {
  Serial.println("timer cleared");
  t.clear(id);
}

void setup() {
  Serial.begin(9600);
  state = HIGH;
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, state);
  Serial.println("led shutdown");
  
  btn1.attachClick(startTimer);
  btn1.attachDoubleClick(initTimer);

  btn2.attachClick(pauseTimer);
  btn2.attachDoubleClick(resumeTimer);
  
  btn3.attachClick(stopTimer);
  btn3.attachDoubleClick(clearTimer);
}

void loop() {
  t.update();
  btn1.tick();
  btn2.tick();
  btn3.tick();
}