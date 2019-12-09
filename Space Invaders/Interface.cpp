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
			if ((Enemies.Enemies[i].x > 0) and (Enemies.Enemies[i].y > 0))
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

void Field::drawShip(MyShip &ship)
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

void Field::drawSheild(sheild &sheild)
{
	screen.dwSize.Y = 1;

	for (int j = 0; j < 3; ++j)
		for (int i = 0; i < 4; ++i)
		{ 
			coord.Y = 27 + i;
			coord.X = sheild.sheilds[j].x;
			screen.dwSize.X = sheild.sheilds[j].live;
			FillConsoleOutputCharacterA(
			console, '@', screen.dwSize.X * screen.dwSize.Y, coord, &written);
		}
}

void Field::clearSheild(sheild & sheild)
{
	screen.dwSize.Y = 1;

	for (int j = 0; j < 3; ++j)
		for (int i = 0; i < 4; ++i)
		{
			coord.Y = 27 + i;
			coord.X = sheild.sheilds[j].x;
			screen.dwSize.X = sheild.sheilds[j].live;
			FillConsoleOutputCharacterA(
				console, ' ', screen.dwSize.X * screen.dwSize.Y, coord, &written);
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
			if ((Enemies.Enemies[i].x > 0) and (Enemies.Enemies[i].y > 0))
			{
				coord.X = Enemies.Enemies[i].x;
				coord.Y = Enemies.Enemies[i].y + j;
				FillConsoleOutputCharacterA(
					console, '*', screen.dwSize.X * screen.dwSize.Y, coord, &written);
			}
		}
	}
}

void Field::drawShipAttack(MyShip::Shell &shell)
{
	GetConsoleScreenBufferInfo(console, &screen);
	screen.dwSize.X = 1;
	screen.dwSize.Y = 1;
	coord.X = shell.x;
	coord.Y = shell.y;
	FillConsoleOutputCharacterA(
		console, '^', screen.dwSize.X * screen.dwSize.Y, coord, &written
	);
}

void Field::clearShipAttack(MyShip::Shell &shell)
{
	GetConsoleScreenBufferInfo(console, &screen);
	screen.dwSize.X = 1;
	screen.dwSize.Y = 1;
	coord.X = shell.x;
	coord.Y = shell.y;
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, coord, &written
	);
}

void Field::clearEnem(BlockOfEnemies &Enemies, int i)
{
	screen.dwSize.X = 4;
	screen.dwSize.Y = 1;

	for (int j = 0; j < 3; ++j)
	{
			coord.X = Enemies.Enemies[i].x;
			coord.Y = Enemies.Enemies[i].y + j;
			FillConsoleOutputCharacterA(
				console, ' ', screen.dwSize.X * screen.dwSize.Y, coord, &written
			);
		}
}

void Field::drawEnemiesAttack(BlockOfEnemies::Shell& shell)
{
	GetConsoleScreenBufferInfo(console, &screen);
	screen.dwSize.X = 1;
	screen.dwSize.Y = 1;
	coord.X = shell.x;
	coord.Y = shell.y;
	FillConsoleOutputCharacterA(
		console, '"', screen.dwSize.X * screen.dwSize.Y, coord, &written
	);
}

void Field::clearEnemiesAttack(BlockOfEnemies::Shell& shell)
{
	GetConsoleScreenBufferInfo(console, &screen);
	screen.dwSize.X = 1;
	screen.dwSize.Y = 1;
	coord.X = shell.x;
	coord.Y = shell.y;
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, coord, &written
	);
}

void Field::drawShipLives(MyShip &ship)
{
	COORD position = { 68,1 }; 
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, position);
	cout << "Lives: " << ship.live;
}

void Field::clearShipLives()
{
	COORD position = { 68,1 };
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, position);
	cout << "        ";
}

void Field::drawPoint(MyShip &ship)
{
	COORD position = { 1,1 };
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, position);
	cout << "Point: " << ship.Point;
}

void Field::clearPoint()
{
	COORD position = { 1,1 };
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, position);
	cout << "            ";
}

void Field::ClearAll()
{
	GetConsoleScreenBufferInfo(console, &screen);
	screen.dwSize.X = 84;
	screen.dwSize.Y = 50;
	coord.X = 0;
	coord.Y = 0;
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, coord, &written
	);
}

void Field::Result(MyShip &ship)
{
	COORD position = { 34,24 };
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, position);
	cout << "Your result: " << ship.Point << endl;
}

