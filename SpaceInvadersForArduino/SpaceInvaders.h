#pragma once


class Shield;
class MyShip;
class BlockOfEnemies;

class MyShip
{
public:
              //ship location, number of lives
  int x;
  int y;
  int live;
  

  struct Shell  
  {
    int x;
    int y;
  };
  MyShip();
  Shell Attack();     //shell attack and where did
  void Move(int&);
  //void Death(BlockOfEnemies::Position&);

};

class BlockOfEnemies
{
public:
  struct Position          //the position of enemies on Oh and Oh
  {
    int x;
    int y;
  };

  Position Enemies[33];     // 33 enemies, 11 per line

  void EnemyLocation(int&, int&);     // building enemy location

  void Move(Shield&,unsigned long &Time);   

  Position  Attack(int&);         // Attack, Position - then to draw how it flies, int to determine the frequency of the shells
  void Death(MyShip::Shell&);                   // death of the enemy, clearing his location
  bool Over(Shield&, int&);                   // checking if the enemies are too close
  void ProjectileMovement(Position&);
  void DeathShip(MyShip&, Position&);
};


class Shield
{
public:
  struct Feature                //location of protective blocks, their degree of destruction
  {
    int x;
    int y;
    int live;
  };
  Shield();
  Feature Shields[3];
  void Destruction(BlockOfEnemies::Position&);                        // block destruction
  
};



inline void GameEnd()
{
  
}
