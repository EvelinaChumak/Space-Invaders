#include "SpaceInvaders.h"
#include <iostream>

void BlockOfEnemies::EnemyLocation(int &MoveX, int &MoveY)				//построение врагов. Так же используется для движения
{
	const int FirstX = 9;
	const int FirstY = 7;
	int ShiftY = 0;
	int ShiftX;
	for (int i = 0; i < 33; ++i)
	{
		ShiftX = 5 * i;
		if (i > 10) ShiftY = 4;
		if (i > 21) ShiftY = 8;
		if (MoveX < 0) ShiftX = -ShiftX;
		Enemies[i].x = FirstX + ShiftX + MoveX;
		Enemies[i].x = FirstY + ShiftY + MoveY;
	}
}

void BlockOfEnemies::Move(Sheild& sheild,const int &Time)				//передвижение в зависимости от времени. Двигается каждую секунду.
																		//Так же происходит проверка на завершение игры или обновления поля
{
	int MoveX = Time % 26;
	int MoveY = Time / 26;
	bool EndGame;
	if (MoveY % 2 == 1) MoveX = -MoveX;
	if ((MoveY > 8) && (Time % 26 == 0))
	{
		EndGame = Over(sheild,MoveY);
		if ((MoveY > 12) && (EndGame == false))
		{
			EndGame = Over(sheild, MoveY);
			if ((MoveY > 16) && (EndGame == false))
			{
				EndGame = Over(sheild, MoveY);
				if (EndGame == false)
				{
					MoveX = 0;
					MoveY = 0;
					EnemyLocation(MoveX, MoveY);
				}
			}
		}
	}
	if (EndGame == true)
		GameOver();
	EnemyLocation(MoveX, MoveY);
}

BlockOfEnemies::Position BlockOfEnemies::Attack(int& Frequancy)
{
	Position Shell;								//рандомно определяет кто выстрелит, чем меньше врагов, тем уже область рандомного значения
	Shell.x = 1;
	Shell.y = 1;
	int R = rand() % Frequancy;
	if (R = 0)
	{
		int X = rand() % 11;
		if (Enemies[X + 22].y == 0)
			if (Enemies[X + 11].y == 0)
				if (Enemies[X].y == 0)
					if (Frequancy > 0)
						Frequancy -= 1;
					else Frequancy = 1;
				else Shell.y = Enemies[X].y;
			else Shell.y = Enemies[X + 11].y;
		else Shell.y = Enemies[X + 22].y;
		Shell.x = X;
	}
	return Shell;
}

void BlockOfEnemies::Death(MyShip::Shell &shell)     // елси снаряд попал в врага, то враг обнуляется. На поле потом отображаться не будет
{
	int x = 0;
	if (Enemies[shell.y].y != 0)
		for (int i = 0; i < 5; ++i)
			if (Enemies[shell.x + i].x != 0)
			{
				x = shell.x + i;
				break;
			}
	if (x !=0 )
	{
		Enemies[shell.y].y = 0;
		Enemies[shell.x].x = 0;
	}
}

bool BlockOfEnemies::Over(Sheild& sheild, int& y)   //проверка на столкновение с защитой. ЕСли ее нет, двигаемся пока
{													//не будем слишком близко к нашему кораблю
	bool r = true;
	for (int i = 0; i < 3; ++i)
	{
		if (sheild.Sheilds[i].live != 0)
			r = false;
	}

	if (r = true)
	{
		if (y = 8)
		{
			for (int i = 21; i < 32; ++i)
			{
				if (Enemies[i].y != 0)
					return true;
			}
		}
		if (y = 12)
		{
			for (int i = 11; i < 21; ++i)
			{
				if (Enemies[i].y != 0)
					return true;
			}
		}
		if (y = 16)
		{
			for (int i = 0; i < 10; ++i)
			{
				if (Enemies[i].y != 0)
					return true;
			}
		}
		return false;
	}
	return true;
}

Sheild::Sheild()
{
	const int Y = 27;
	for (int i = 0; i < 3; ++i)
	{
		Sheilds[i].x = 11 + 24 * i;
		Sheilds[i].y = Y;
		Sheilds[i].live = 6;
	}
}

void BlockOfEnemies::ProjectileMovement(Position& Projectile)
{
	Projectile.y += 1;
}

void Sheild::Destruction(BlockOfEnemies::Position& Projectile)
{
	for (int i = 0; i<3; ++i)
		for (int j = 0; j < 12; ++j)
		{
			bool q = true;
			if (Projectile.x == Sheilds[i].x + j)
			{
				q = false;
				Sheilds[i].live -= 1;
				Projectile.x = 0;
				Projectile.y = 0;
				break;
			}
			if (!q) break;
		}
}

MyShip::MyShip()
{
	live = 3;
	x = 9;
	y = 38;
}

void MyShip::Move(int& X)
{
	if ((x < 46) && (x > 2))
	x += X;

}

MyShip::Shell MyShip::Attack()
{
	Shell shell;
	shell.x = x;
	shell.y = y;
}

void MyShip::Death(BlockOfEnemies::Position& shell)
{
	if (x == shell.x)
		live -= 1;
	if (live < 0)
		GameOver;
}