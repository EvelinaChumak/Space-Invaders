#pragma once
#include <iostream>
#include "SpaceInvaders.h"
#include <Windows.h>
#include <conio.h>

using namespace std;

class Field
{
public:
	Field();
	//~Field();
	void clear();
	void clearShip(MyShip &ship);
	void clearEnemies(BlockOfEnemies& Enemies);
	void drawship(MyShip &ship);
	void drawshield(Shield &shield);
	void drawsEnemies(BlockOfEnemies& Enemies);

private:
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	_COORD coord;
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;
};



	

