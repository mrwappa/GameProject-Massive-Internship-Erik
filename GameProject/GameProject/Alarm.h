#ifndef ALARM_H
#define ALARM_H

#include "GrowingArray.h"

class Alarm
{
public:
	Alarm();
	~Alarm();

	static GrowingArray<Alarm*> Alarms;

	void Decrement();
	static void DecrementAlarms();

	void SetTick(int aTick);

	int GetTick();

private:
	int myTick;
};

#endif // !ALARM_H