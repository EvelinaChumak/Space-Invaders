#pragma once
#include <vector>

using namespace std;

class sheild;
class MyShið;
class BlockOfEnemies;


class MyShip
{
public:
								//ship location, number of lives
	int x;
	int y;
	int live;
	int Point;

	struct Shell			
	{
		int x ;
		int y ;
		void Move();
		bool EndField();
	};

	vector<Shell> shells;

	MyShip();
	Shell Attack();			//shell attack and where did
	void Move(int&);
	bool GameEnd;

};

class BlockOfEnemies
{
public:
	struct Position          //the position of enemies on Oh and Oh
	{
		int x;
		int y;
	};
	struct Shell
	{
		int x;
		int y;
		void Move();
		bool EndField();
	};

	int NumberOfEnemies;
	int TimeReset = 0;		//to correctly determine the position
	int DeadEnemies;

	vector<Shell> shells;

	Position Enemies[33];     // 33 enemies, 11 per line

	void EnemyLocation(int&, int&);     //how much has move, for void Move

	void EnemyBuilding();

	void Move(sheild&,int &Time, MyShip&);		

	vector<Shell> Attack();					// Attack, Position - then to draw how it flies, int to determine the frequency of the shells
	int Death(MyShip::Shell&);										// death of the enemy, clearing his location
	bool Over(sheild&, int&);										// checking if the enemies are too close
	bool DeadAllEnemies();						
	bool DeadShip(MyShip&, int&);				//whether the shell hit the ship and the death of the ship

};


class sheild
{
public:
	struct Feature								//location of protective blocks, their degree of destruction
	{
		int x;
		int y;
		int live;
	};
	sheild();
	Feature sheilds[3];
	bool Destruction(BlockOfEnemies::Shell&);                        // block destruction
	bool Destruction(MyShip::Shell&);
	
};

