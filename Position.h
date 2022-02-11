//Position.h
#pragma once
#ifndef POSITION_
#define POSITION_

class Position
{
public:
    Position();
    Position(int, int);
    void setX(int);
    void setY(int);
    int getX() const;
    int getY() const;

private:
    int mX;
    int mY;
};
#endif