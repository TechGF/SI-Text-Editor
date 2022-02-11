//Snapshot.h
#pragma once
#ifndef SNAPSHOT_
#define SNAPSHOT_
#include <iostream>
#include <string>
#include "LinkedStack.h"
#include "StackInterface.h"
#include "Node.h"
#include "Position.h"
using namespace std;

class Snapshot
{
public:
	Snapshot(); //constructor
	Snapshot(char, string, Position); //constructor for delete char and line
	void setCommand(char); //set for command
	void setValue(string); //set for value
	void setPosition(Position); //set for position
	char getCommand() const; //get for command
	string getValue() const; //get for value
	Position getPosition() const; //get for position

private:
	Position position;
	char command;
	string value;
};

#endif
