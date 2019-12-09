
#include "Interface.h"
#include <ctime>


using namespace std;
int main(void)
{	setlocale(LC_ALL, "Russian");

	Field field;
	MyShip ship;
	sheild sheild;
	BlockOfEnemies enemies;
	enemies.EnemyBuilding();

	field.drawsEnemies(enemies);
	field.drawSheild(sheild);
	field.drawShip(ship);
	field.drawShipLives(ship);
	field.drawPoint(ship);

	srand(time(0));

	char c = 'e';
	int i;
	int TimeForMove = clock();
	int TimeForAttack = clock();

	while (c != 'q')
	{
		if ((clock() - TimeForMove) / 1000 == 1)				//every second we move and redraw the position
		{
			TimeForMove = clock();
			field.clearEnemies(enemies);
			int c = TimeForMove / 1000 - enemies.TimeReset;
			enemies.Move(sheild, c, ship);
			field.drawsEnemies(enemies);
		}

		if ((clock() - TimeForAttack) / 200 == 1)				//every 200 milliseconds shells move
		{
			TimeForAttack = clock();

			int NumActiveShell = 0;
			int NumActiveShellEnemies = 0;

			while (NumActiveShell < ship.shells.size())
			{
					field.clearShipAttack(ship.shells[NumActiveShell]);
					field.clearSheild(sheild);
					ship.shells[NumActiveShell].Move();
					int k = enemies.Death(ship.shells[NumActiveShell]);		 //check if the enemy was killed
					int j = 1;						//for change the number of active shells
					if ((ship.shells[NumActiveShell].EndField()) or (sheild.Destruction(ship.shells[NumActiveShell])))	
					{		//if the shell went out the field or hit the protective block
						ship.shells.erase(ship.shells.begin() + NumActiveShell);	//remove the shell
						j = 0;
					}
					if (k >= 0)				//if the enemy was killed
					{
						field.clearPoint();
						ship.Point += 15;
						field.drawPoint(ship);
						ship.shells.erase(ship.shells.begin() + NumActiveShell);		//remove the shell
						field.clearEnem(enemies, k);
						enemies.Enemies[k].x = 0;				//we nullify the enemy
						enemies.Enemies[k].y = 0;
						j = 0;
					}
					NumActiveShell += j;   //change the number of active shells
					if ((!ship.shells.empty()) and (NumActiveShell == 0))		//if it was the fist shell
						field.drawShipAttack(ship.shells[NumActiveShell]);
					else if (!ship.shells.empty())
						field.drawShipAttack(ship.shells[NumActiveShell - 1]);
					field.drawSheild(sheild);
			}

			enemies.shells = enemies.Attack();

			while (NumActiveShellEnemies < enemies.shells.size())
			{
				field.clearEnemiesAttack(enemies.shells[NumActiveShellEnemies]);
				field.clearSheild(sheild);
				enemies.shells[NumActiveShellEnemies].Move();
				int j = 1;		//for change the number of active shells

				if ((enemies.DeadShip(ship, NumActiveShellEnemies)))		//if you hit the ship
				{
					enemies.shells.erase(enemies.shells.begin() + NumActiveShellEnemies);	 //remove the shell
					j = 0;
					field.clearShipLives();
					field.drawShipLives(ship);
				}
				if (!enemies.shells.empty() and (!ship.GameEnd))
					if ((enemies.shells[NumActiveShellEnemies].EndField()) or (sheild.Destruction(enemies.shells[NumActiveShellEnemies])))
					{			///if the shell went out the field or hit the protective block
						enemies.shells.erase(enemies.shells.begin() + NumActiveShellEnemies);		//remove the shell
						j = 0;
					}
				NumActiveShellEnemies += j;
				if ((!enemies.shells.empty()) and (NumActiveShellEnemies == 0))			//if it was the fist shell
					field.drawEnemiesAttack(enemies.shells[NumActiveShellEnemies]);
				else if (!enemies.shells.empty())
					field.drawEnemiesAttack(enemies.shells[NumActiveShellEnemies - 1]);
				field.drawSheild(sheild);
			}

		}


		if (_kbhit())
		{
			switch (_getch())
			{
			case 'w':
				{
					ship.shells.push_back(ship.Attack());
					field.drawShipAttack(ship.shells[ship.shells.size()-1]);
				}
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
			field.drawShip(ship);
		}
		while (ship.GameEnd)
		{
			field.ClearAll();
			field.Result(ship);
			system("pause");
		}
	}

	return 0;

}
