
#include "Interface.h"
#include <ctime>

using namespace std;
int main(void)
{	setlocale(LC_ALL, "Russian");
	Field field;
	MyShip ship;
	Shield sheild;
	BlockOfEnemies enemies;
	int x = 0;
	int y = 0;
	enemies.EnemyLocation(x, y);
	field.drawsEnemies(enemies);
	field.drawshield(sheild);
	field.drawship(ship);

	srand(time(0));

	char c = 'e';
	int i;

	while (c != 'q')
	{

		int time = clock();
		if ((time%1000 < 20) && (time/1000 > 1))
		{
			field.clearEnemies(enemies);
			time = time / 1000;
			enemies.Move(sheild, time);
			field.drawsEnemies(enemies);
		}
		if (_kbhit())
		{
			switch (_getch())
			{
			case 'w':

				ship.Attack();
				break;
			case 'a':
				i = -1;
				ship.Move(i);
				break;
			case 'd':
				i = 1;
				ship.Move(i);
				break;
			}
			field.clearShip(ship);
			field.drawship(ship);
		}
	}

	return 0;

}
