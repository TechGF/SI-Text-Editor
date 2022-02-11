//Editor.cpp
#pragma once
#include <iostream>
#include "Editor.h"
#include <string>
#include <conio.h>
#include <fstream>
#include <windows.h> //for placeCursorAt
#include "LinkedList.h"
#include "Position.h"
#include "Snapshot.h"
#include "ListInterface.h"
#include "LinkedStack.h"
#include "PrecondViolatedExcep.h"
#include "binaryNodeTree.h"
#include "binarySearchTree.h"
using namespace std;

//Default Constructor
Editor::Editor()
{
	//Empty
}

//parameterized constructor
Editor::Editor(string _fileName)
{
	string temp;
	fileName = _fileName;
	numOfLines = 0;

	inFile.open(fileName); //open a file in read mode
	if (!inFile.is_open()) //error in opening file
	{
		cout << "Error... Unable to read file." << endl;
		exit(0);
	}

	for (int i = 1; !inFile.eof();i++)
	{
		getline(inFile, temp);
		lines.insert(i, temp); //places the contents into list of lines
		numOfLines++;
	}

	inFileTwo.open("keywordsRandom.txt");
	if (!inFileTwo.is_open()) //error in opening file
	{
		cout << "Error... Unable to read file." << endl;
	}

	while (!inFileTwo.eof()) //File exist
	{
		inFileTwo >> keyWordsRand; //reading text file
		keyWordsRandom.add(keyWordsRand);
	}
}//end Editor

//Display Lines function
void Editor::displayLines()
{
	int position;
	string nextLine, nextWord, line, word;
	system("cls");
	// goes through each line in the linked list 
	for (position = 1; position <= lines.getLength(); position++)
	{
		nextLine = lines.getEntry(position);
	
		int i = 0;
		while (i < nextLine.length()) {
			string word;
			// isolate a word at a time (can contain underscores)
			if (isalpha(nextLine[i])) {
				while (isalpha(nextLine[i]) || nextLine[i] == '_') {
					word += nextLine[i];
					i++;

				}

				if (keyWordsRandom.contains(word)) //binary search tree
					colorText(1);
				else
					colorText(0);
				cout << word;

			}

			else {
				colorText(0);
				cout << nextLine[i];
				i++;
			}

		}

		cout << endl;
	}
	placeCursorAt(uPos);
} // end displayLines

//run function
void Editor::run()
{
	displayLines();
	placeCursorAt(uPos); //User cursor starts at position (0,0)
	bool running = true;
	char userEntry;
	int endOfLines = lines.getLength() + 5;

	while (running)
	{
		userEntry = _getch(); //user input a character for entry
		
		switch(userEntry)
		{
			case ':':
				uPos.setX(0);
				uPos.setY(endOfLines);
				placeCursorAt(uPos);
				
				cout << userEntry;
				userEntry = _getche();
				if (userEntry == 'w') //input 'w' to write the file
				{
					ofstream newFile;
					newFile.open(fileName);
					for (int i = 1; i <= lines.getLength(); i++)
					{
						newFile << lines.getEntry(i) << endl;
					}
					newFile.close();
					cout << "\nFile has been successfully overwritten." << endl;
				}
				else if (userEntry == 'q') //input 'q' to quit the file
				{
					inFile.close();
					running = false;
					cout << "\n\nFile Closed." << endl;
					system("pause");
				}
				else
					cout << "Invalid Entry." << endl;
					break;
			case 'x': //input 'x' to delete one character
					deleteCharFunc();
					break;
			case 'd': //input "dd" to delete whole line
				userEntry = _getche();
				if (userEntry == 'd')
				{
					if (currentLineNumber > 0 && currentLineNumber < numOfLines)
					{
						deleteLineFunc();
					}
				}
				break;
			case 'u': //Input 'u' to undo
				if (!undoStack.isEmpty())
				{
					undoFunc();
				}
				break;
			case 'k': //Input 'k' to move up one line
				if (currentLineNumber > 0)
				{
					moveUp();
				}
				break;
			case 'j': //Input 'j' to move down one line
				if (currentLineNumber < numOfLines)
				{
					moveDown();
				}
				break;
			case 'l': //Input 'l' to move right one
				if (currentPosition < lines.getEntry(currentLineNumber).length())
				{
					moveRight();
				}
				break;
			case 'h': //Input 'h' to move left one
				if (currentPosition > 0)
				{
					moveLeft();
				}
				break;

			default: //When user input an wrong command
				uPos.setX(0);
				uPos.setY(endOfLines);
				placeCursorAt(uPos);
				cout << "\nInvalid Entry." << endl;
				break;
		}
		placeCursorAt(uPos);
	}
}//end run

//delete one character function 'x'
void Editor::deleteCharFunc()
{
	int yCoord = uPos.getY();
	string currentLine = lines.getEntry(yCoord + 1);
	Snapshot savedDeletedChar('x', currentLine, uPos);
	undoStack.push(savedDeletedChar); //push deleted char into top of the stack
	currentLine.erase(currentPosition, 1);
	lines.replace(currentLineNumber, currentLine);
	displayLines();
}//end deleteCharFunc

//delete one line function "dd"
void Editor::deleteLineFunc()
{
	int yCoord = uPos.getY();
	string currentLine = lines.getEntry(yCoord + 1);
	Snapshot savedDeletedLine('d', currentLine, uPos);
	undoStack.push(savedDeletedLine); //push deleted line into top of the stack
	lines.remove(currentLineNumber);
	displayLines();
}//end deleteLineFunc

//cursor navigation for Up 'k'
void Editor::moveUp()
{
	currentLineNumber--; //decrement the Y component
	uPos.setY(currentLineNumber - 1);
	placeCursorAt(uPos);
}//end moveUp

//cursor navigation for Down 'j'
void Editor::moveDown()
{
	currentLineNumber++; //increment the Y component
	uPos.setY(currentLineNumber - 1);
	placeCursorAt(uPos);
}//end moveDown

//cursor navigation for Right 'l'
void Editor::moveRight()
{
	currentPosition++; //increment the X component
	uPos.setX(currentPosition);
	placeCursorAt(uPos);
}//end moveRight

//cursor navigation for Left 'h'
void Editor::moveLeft()
{
	currentPosition--; //decrement the X component
	uPos.setX(currentPosition);
	placeCursorAt(uPos);
}//end moveLeft

//Undo Function
void Editor::undoFunc()
{
	if (!undoStack.isEmpty())
	{
		Snapshot snapShot; //Snapshot instance
		string savedValue;
		snapShot = undoStack.peek(); //peek the top of the stack
		char cmd = snapShot.getCommand();
		undoStack.pop(); //pop the top of the stack

		switch (cmd)
		{
		case 'x': //command for 'x'
			savedValue = snapShot.getValue();
			uPos = snapShot.getPosition();
			lines.replace(uPos.getY() + 1, savedValue);
			displayLines();
			break;
		case 'd': //command for 'dd'
			uPos = snapShot.getPosition();
			savedValue = snapShot.getValue();
			lines.insert(uPos.getY() + 1, savedValue);
			displayLines();
			break;
		}
	}
}//end undoFunc

//placeCursorAt tracks the cursor position
void placeCursorAt(Position coordinate)
{
	COORD coord;
	coord.X = coordinate.getX();
	coord.Y = coordinate.getY();
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord);
}//end placeCursorAt

//Color Text
void colorText(int value)
{
	COORD coord;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	FlushConsoleInputBuffer(hConsole);
	SetConsoleTextAttribute(hConsole, value + 240);
}//end colorText