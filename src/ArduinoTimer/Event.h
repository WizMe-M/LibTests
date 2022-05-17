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

#ifndef Event_h
#define Event_h

#include <inttypes.h>

enum EventTypes
{
  NoEvent = 0,
  Every = 1,
  Oscillate = 2
};

enum EventStates
{
  None = 0,
  Run = 1,
  Pause = 2,
  Stop = 3
};

class Event
{

public:
  Event(void);
  int8_t initOscillate(uint8_t pin, unsigned long period, uint8_t startingValue, int repeatCount);
  int8_t initEvery(unsigned long period, void (*callback)(), int repeatCount);
  void start(void);
  void update(void);
  void update(unsigned long now);
  void pause(void);
  void stop(void);
  void resume(void);
  void clear(void);
  bool hasEvent(void);

  unsigned long period;
  int repeatCount;
  uint8_t pin;
  uint8_t pinState;
  uint8_t startState;
  void (*callback)(void);
  unsigned long lastEventTime;
  int count;

protected:
  EventTypes eventType;
  EventStates eventState;
};

#endif
