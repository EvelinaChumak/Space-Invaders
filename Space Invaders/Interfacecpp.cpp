#include "Interface.h"


Field::Field()
{
	coord.X = 84;
	coord.Y = 48;
	_SMALL_RECT Rect = { 0,0,83,47 };

	SetConsoleTitle("Space");

	SetConsoleScreenBufferSize(console, coord);            // Set Buffer Size 
	SetConsoleWindowInfo(console, TRUE, &Rect);            // Set Window Size 


}

void Field::clearEnemies(BlockOfEnemies& Enemies)
{
	screen.dwSize.X = 4;
	screen.dwSize.Y = 1;

	for (int j = 0; j < 3; ++j)
	{

		for (int i = 0; i < 33; ++i)
		{
			coord.X = Enemies.Enemies[i].x;
			coord.Y = Enemies.Enemies[i].y + j;
			FillConsoleOutputCharacterA(
				console, ' ', screen.dwSize.X * screen.dwSize.Y, coord, &written
			);
		}
	}
}
void Field::clearShip(MyShip &ship) {
	GetConsoleScreenBufferInfo(console, &screen);
	screen.dwSize.X = 12;
	screen.dwSize.Y = 1;
	coord.X = ship.x - 1;
	coord.Y = ship.y + 1;
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, coord, &written
	);

	screen.dwSize.X = 5;
	screen.dwSize.Y = 1;
	coord.X = ship.x + 2;
	coord.Y = ship.y;

	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, coord, &written
	);
}
void Field::clear() {
	coord = { 0, 0 };

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, coord, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, coord, &written
	);
	SetConsoleCursorPosition(console, coord);
}

void Field::drawship(MyShip &ship)
{
	GetConsoleScreenBufferInfo(console, &screen);
	screen.dwSize.X = 10;
	screen.dwSize.Y = 1;
	coord.X = ship.x;
	coord.Y = ship.y + 1;
	FillConsoleOutputCharacterA(
		console, '#', screen.dwSize.X * screen.dwSize.Y, coord, &written
	);

	screen.dwSize.X = 3;
	screen.dwSize.Y = 1;
	coord.X = ship.x + 3;
	coord.Y = ship.y;

	FillConsoleOutputCharacterA(
		console, '#', screen.dwSize.X * screen.dwSize.Y, coord, &written
	);
}

void Field::drawshield(Shield &shield)
{
	screen.dwSize.X = 12;
	screen.dwSize.Y = 1;

	for (int i = 0; i < 4; ++i)
	{
		coord.Y = 27 + i;
		for (int j = 0; j < 3; ++j)
		{
			coord.X = shield.Shields[j].x;
			FillConsoleOutputCharacterA(
				console, '@', screen.dwSize.X * screen.dwSize.Y, coord, &written
			);
		}
	}
}

void Field::drawsEnemies(BlockOfEnemies& Enemies)
{
	screen.dwSize.X = 4;
	screen.dwSize.Y = 1;

	for (int j = 0; j < 3; ++j)
	{

		for (int i = 0; i < 33; ++i)
		{
			coord.X = Enemies.Enemies[i].x;
			coord.Y = Enemies.Enemies[i].y + j;
			FillConsoleOutputCharacterA(
				console, '*', screen.dwSize.X * screen.dwSize.Y, coord, &written
			);
		}
	}
}