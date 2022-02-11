/*
main.cpp
The purpose of this code writes an Editor class that has an instance of
the LinkedList and allows command keys of :q for quit, :w for overwriting file,
'x' to delete a character, "dd" to delete line and 'u' to undo. User cursor is able to
navigation the Editor through command keys of 'j' to move down one line, 'k' to move up one
line, 'h' to move left one position within the line and 'l' to move right one position within
the line.
*/
#include <iostream>
#include "Editor.h"
#include "Snapshot.h"
#include <conio.h>
using namespace std;

void main(int argc, const char* argv[])
{
	if (argc > 1)
	{
		Editor si(argv[1]); //Editor instance
		si.run();
	}
	else
	{
		cout << "File cannot open..." << endl;
		exit(0);
	}
}