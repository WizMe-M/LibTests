/*
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *      MA 02110-1301, USA.
 */

/*  * * * * * * * * * * * * * * * * * * * * * * * * * * *
 Code by Simon Monk
 http://www.simonmonk.org
* * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// For Arduino 1.0 and earlier
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Event.h"

Event::Event(void)
{
	eventType = NoEvent;
	eventState = None;
}

int8_t Event::initOscillate(uint8_t pin, unsigned long period, uint8_t startingValue, int repeatCount)
{
	eventType = Oscillate;
	eventState = Stop;
	this->pin = pin;
	this->period = period;
	startState = startingValue;
	pinState = startingValue;
	this->repeatCount = repeatCount * 2; // full cycles not transitions
	count = 0;
}

int8_t Event::initEvery(unsigned long period, void (*callback)(), int repeatCount)
{
	eventType = Every;
	eventState = Stop;
	this->period = period;
	this->repeatCount = repeatCount;
	this->callback = callback;
}

void Event::start(void)
{
	switch (eventState)
	{
	case None:
		Serial.println("Timer isn't initialized!");
		break;

	default:
		eventState = Run;
		lastEventTime = millis();
		count = 0;
		pinState = startState;
		break;
	}
}

void Event::pause(void)
{
	switch (eventState)
	{
	case None:
		Serial.println("Timer isn't initialized!");
		break;

	case Run:
		eventState = Pause;
		break;

	case Pause:
		Serial.println("Timer already paused");
		break;
	
	case Stop:
		Serial.println("Timer already stopped");
		break;

	default:
		break;
	}
}

void Event::stop(void)
{
	switch (eventState)
	{
	case None:
		Serial.println("Timer isn't initialized!");
	
	case Stop:
		Serial.println("Timer already stopped");
		break;
	
	default:
		eventState = Stop;
		break;
	}
}

void Event::resume(void)
{
	switch (eventState)
	{
	case None:
		Serial.println("Timer isn't initialized!");
		break;
	
	case Pause:
		eventState = Run;
		break;

	case Stop:
		start();
		break;

	default:
		break;
	}
}

void Event::clear(void)
{
	eventState = None;
	eventType = NoEvent;
}

bool Event::hasEvent(void)
{
	return eventType != NoEvent;
}

void Event::update(void)
{
	unsigned long now = millis();
	update(now);
}

void Event::update(unsigned long now)
{
	if (now - lastEventTime >= period)
	{
		if (eventState == Run)
		{
			switch (eventType)
			{
			case Every:
				(*callback)();
				break;

			case Oscillate:
				pinState = !pinState;
				digitalWrite(pin, pinState);
				break;
			}
			lastEventTime = now;
			count++;
		}
	}

	if (repeatCount > -1 && count >= repeatCount)
	{
		eventType = NoEvent;
	}
}