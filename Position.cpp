//Position.cpp
#pragma once
#include "Position.h"  
#include "windows.h"

//default constructor
Position::Position()
{
	mX = 0;
	mY = 0;
}
//parameterized constructor
Position::Position(int x, int y)
{
	mX = x;
	mY = y;
}
//setX
void Position::setX(int x)
{
	mX = x;
}
//setY
void Position::setY(int y)
{
	mY = y;
}
//getX
int Position::getX() const
{
	return mX;
}
//getY
int Position::getY() const
{
	return mY;
}

