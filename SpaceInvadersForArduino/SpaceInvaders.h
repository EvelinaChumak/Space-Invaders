#pragma once
#include <Arduino.h>
#include "vector.h"


class Sheild;
//class MyShip;
class BlockOfEnemies;


class MyShip
{
  public:
    //ship location, number of lives
    int8_t x;
    int8_t y;
    int8_t live;
    unsigned long Point;
    bool GameEnd;

    struct Shell
    {
      int8_t x ;
      int8_t y ;
      void Move();
      bool EndField();
    };


    vector<Shell> shells;

    MyShip();
    Shell Attack();     //shell attack and where did
    void Move(int8_t&);

};

class BlockOfEnemies
{
  public:
    struct Position          //the position of enemies on Oh and Oh
    {
      int8_t x;
      int8_t y;
    };
    struct Shell
    {
      int8_t x;
      int8_t y;
      void Move();
      bool EndField();
    };


    int8_t NumberOfEnemies;
    unsigned long TimeReset = 0;   //to correctly determine the position
    int8_t DeadEnemies;

    vector<Shell> shells;

    Position Enemies[33];     // 33 enemies, 11 per line

    void EnemyLocation(int8_t&, int8_t&);     // building enemy location

    void EnemyBuilding();

    void Move(Sheild&, int &Time, MyShip&);

    vector<Shell> Attack();         // Attack, Position - then to draw how it flies, int to determine the frequency of the shells
    int8_t Death(MyShip::Shell);                    // death of the enemy, clearing his location
    bool Over(Sheild&, int8_t&);                   // checking if the enemies are too close to ship or protective blocks
    bool DeadAllEnemies();
    bool DeadShip(MyShip&, int8_t&);      //whether the shell hit the ship and the death of the ship

};


class Sheild
{
  public:
    struct Feature                //location of protective blocks, their degree of destruction
    {
      int8_t x;
      int8_t y;
      int8_t live;
    };
    Sheild();
    Feature sheilds[3];
    bool Destruction(BlockOfEnemies::Shell&);                        // block destruction
    bool Destruction(MyShip::Shell&);

};
