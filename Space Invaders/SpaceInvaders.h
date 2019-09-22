#pragma once

class Sheild;
class MyShi�;
class BlockOfEnemies;

class MyShip
{
public:
							//����������������� �������, ���������� ������
	int x;
	int y;
	int live;
	

	struct Shell					// ������
	{
		int x;
		int y;
	};
	MyShip();
	Shell Attack();			//����� �������, ���� �����
	void Move(int&);
	void Death(BlockOfEnemies::Position&);

};

class BlockOfEnemies
{
public:
	struct Position          // ��������� ������ �� �� � ��
	{
		int x;
		int y;
	};

	Position Enemies[32];     // 33 �����, �� 11 �� �������

	void EnemyLocation(int&, int&);     // ���������� �������������� ������

	void Move(Sheild&,const int &Time);				// ������� ������������ ������ 

	Position  Attack(int&);         // �����, Position - ����� ����� ������������ ��� �����, int ����� ���������� ������� ��������
	void Death(MyShip::Shell&);										// ������ �����, ������� ��� ��������������
	bool Over(Sheild&, int&);										// ��������, �� ������� �� ������ �����
	void ProjectileMovement(Position&);
};


class Sheild
{
public:
	struct Feature								//������������ �������� ������, �� ������� �������������
	{
		int x;
		int y;
		int live;
	};
	Sheild();
	Feature Sheilds[2];
	void Destruction(BlockOfEnemies::Position&);                        // ���������� �����
	
};



void GameOver();
