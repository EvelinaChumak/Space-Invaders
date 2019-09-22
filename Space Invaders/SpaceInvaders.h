#pragma once

class Sheild;
class MyShiр;
class BlockOfEnemies;

class MyShip
{
public:
							//месторасположение корабля, количество жизней
	int x;
	int y;
	int live;
	

	struct Shell					// снаряд
	{
		int x;
		int y;
	};
	MyShip();
	Shell Attack();			//атака снаряда, куда попал
	void Move(int&);
	void Death(BlockOfEnemies::Position&);

};

class BlockOfEnemies
{
public:
	struct Position          // положение врагов по Ох и Оу
	{
		int x;
		int y;
	};

	Position Enemies[32];     // 33 врага, по 11 на строчку

	void EnemyLocation(int&, int&);     // построение местоположение вргаов

	void Move(Sheild&,const int &Time);				// функция передвижения врагов 

	Position  Attack(int&);         // Атака, Position - чтобы потом отрисовывать как летит, int чтобы определять частоту снарядов
	void Death(MyShip::Shell&);										// смерть врага, очистка его местоположения
	bool Over(Sheild&, int&);										// проверка, не слишком ли близко враги
	void ProjectileMovement(Position&);
};


class Sheild
{
public:
	struct Feature								//расположение защитных блоков, их степень разрушенности
	{
		int x;
		int y;
		int live;
	};
	Sheild();
	Feature Sheilds[2];
	void Destruction(BlockOfEnemies::Position&);                        // разрушение блока
	
};



void GameOver();
