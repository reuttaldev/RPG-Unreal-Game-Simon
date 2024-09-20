#include "SimonData.h"

FSimonData::FSimonData()
{
	mapColorToNote.Add(ButtonColors::Red, Notes::A);
	mapColorToNote.Add(ButtonColors::Blue, Notes::B);
	mapColorToNote.Add(ButtonColors::Yellow, Notes::C);
	mapColorToNote.Add(ButtonColors::Green, Notes::E);
}
