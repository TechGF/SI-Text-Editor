//Editor.h
#pragma once
#ifndef EDITOR_
#define EDITOR_
#include <windows.h>
#include <string>
#include <fstream>
#include "Position.h"
#include "LinkedList.h"
#include "LinkedStack.h"
#include "Snapshot.h"
#include "ListInterface.h"
#include "PrecondViolatedExcep.h"
#include "binaryNodeTree.h"
#include "binarySearchTree.h"
using namespace std;

void placeCursorAt(Position coordinate);
void colorText(int value);

class Editor
{
public:
    Editor(); 
    Editor(string _fileName);
    void displayLines();
    void run();
    void deleteCharFunc();
    void deleteLineFunc();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void undoFunc();
   
private:
    Position uPos; //user position
    string fileName, keyWordsRand;
    fstream inFile, inFileTwo;
    LinkedList <string> lines;
    LinkedStack <Snapshot> undoStack;
    BinarySearchTree <string> keyWordsRandom;
    int numOfLines; //Number of lines in the text
    int currentLineNumber = uPos.getY() + 1; //Current line starts at 1, Y value
    int currentPosition = uPos.getX(); //Current position starts at 0, X value
};
#endif