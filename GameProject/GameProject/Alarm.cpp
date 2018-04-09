#include "stdafx.h"
#include "Alarm.h"

GrowingArray<Alarm*> Alarm::Alarms;

Alarm::Alarm()
{
	Alarms.Add(this);
	myTick = -1;
}


Alarm::~Alarm()
{
	Alarms.RemoveCyclic(this);
}

void Alarm::Decrement()
{
	myTick--;
	if (myTick <= -1)
	{
		myTick = -1;
	}
}

void Alarm::DecrementAlarms()
{
	for (int i = 0; i < Alarms.Size(); i++)
	{
		Alarms[i]->Decrement();
	}
}

void Alarm::SetTick(int aTick)
{
	myTick = aTick;
}

int Alarm::GetTick()
{
	return myTick;
}
