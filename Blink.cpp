/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Blink.h"

Blink::Blink(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void Blink::on(int time)
{
  digitalWrite(_pin, HIGH);
  delay(time);
}

void Blink::off(int time)
{

  digitalWrite(_pin, LOW);
  delay(time);
}