#include "SpaceInvaders.h"
#include <Windows.h>
#include <conio.h>

class Field
{
public:
	Field();
	~Field();
	void cursor_show(bool visable);
	void text_attr(WORD attr);
	void pos(int x, int y, char ch = 0);
	void pos_str(int x, int y, const char *str);
	void cls();
private:
	HANDLE hConsoleOutput;
	CONSOLE_CURSOR_INFO oldCursorInfo, curCursorInfo;
	WORD oldTextAttr;


};

Field::Field()
{
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleCursorInfo(hConsoleOutput, &oldCursorInfo);


	curCursorInfo.dwSize = oldCursorInfo.dwSize;
	curCursorInfo.bVisible = oldCursorInfo.bVisible;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsoleOutput, &csbi);
	oldTextAttr = csbi.wAttributes;
}

Field::~Field() {
	SetConsoleCursorInfo(hConsoleOutput, &oldCursorInfo);
	SetConsoleTextAttribute(hConsoleOutput, oldTextAttr);

}