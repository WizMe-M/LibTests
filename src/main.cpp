#include <Arduino.h>
#include "SimpleTimer/Timer.h"
#include "OneButton.h"

Timer t;
OneButton btn(A1);
OneButton btn1(A2);

byte ledValue;

void blink()
{
  ledValue = !ledValue;
  digitalWrite(LED_BUILTIN, ledValue);
}

void start()
{
  t.start();
}

void pause()
{
  t.pause();
}

void stop()
{
  t.stop();
}

void setup() {
  ledValue = HIGH;
  
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, ledValue);

  btn.attachClick(start);
  btn1.attachClick(pause);
  btn1.attachDoubleClick(stop);

  t.init(1000, blink);
}

void loop() {
  t.update();
  btn.tick();
  btn1.tick();
}