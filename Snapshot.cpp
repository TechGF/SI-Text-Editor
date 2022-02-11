//Snapshot.cpp
#include "Snapshot.h"

//constructor
Snapshot::Snapshot()
{
	//Empty
}

//constructor for delete char and line
Snapshot::Snapshot(char command, string value, Position position)
{
	this->command = command;
	this->value = value;
	this->position = position;
}
//set for command
void Snapshot::setCommand(char command)
{
	this->command = command;
}

//set for value
void Snapshot::setValue(string value)
{
	this->value = value;
}

//set for position
void Snapshot::setPosition(Position position)
{
	this->position = position;
}

//get for command
char Snapshot::getCommand() const
{
	return command;
}

//get for value
string Snapshot::getValue() const
{
	return value;
}

//get for position
Position Snapshot::getPosition() const
{
	return position;
}