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
	void drawShip(MyShip &ship);
	void drawSheild(sheild &sheild);
	void clearSheild(sheild &sheild);
	void drawsEnemies(BlockOfEnemies& Enemies);
	void drawShipAttack(MyShip::Shell &shel);
	void clearShipAttack(MyShip::Shell &shell);
	void clearEnem(BlockOfEnemies& Enemies, int i);
	void drawEnemiesAttack(BlockOfEnemies::Shell&);
	void clearEnemiesAttack(BlockOfEnemies::Shell&);
	void drawShipLives(MyShip&);
	void clearShipLives();
	void drawPoint(MyShip&);
	void clearPoint();
	void ClearAll();
	void Result(MyShip&);


private:
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	_COORD coord;
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;
};



	

