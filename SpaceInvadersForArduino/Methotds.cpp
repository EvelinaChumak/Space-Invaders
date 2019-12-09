#include "SpaceInvaders.h"

void BlockOfEnemies::EnemyBuilding()    //fist location
{
  DeadEnemies = 0;
  const int8_t FirstX = 2;
  const int8_t FirstY = 7;
  int8_t ShiftY = 0;
  int8_t ShiftX;
  for (int8_t i = 0; i < 33; ++i)
  {
    ShiftX = 5 * (i % 11);
    if (i > 10) ShiftY = 4;
    if (i > 21) ShiftY = 8;
    Enemies[i].x = FirstX + ShiftX;
    Enemies[i].y = FirstY + ShiftY;
  }
  NumberOfEnemies = 33;
}

void BlockOfEnemies::EnemyLocation(int8_t &MoveX, int8_t &MoveY)    //change of fosition depending on movement
{
  for (int8_t i = 0; i < 33; ++i)
  {
    if ((Enemies[i].x != 0) or (Enemies[i].y != 0))
    {
      Enemies[i].x += MoveX;
      Enemies[i].y += MoveY;
    }
  }
}

void BlockOfEnemies::Move(Sheild& sheild, int &Time, MyShip& ship)      // movement depending on time. It moves every second.
// This also checks to complete the game or update the field
{
  int8_t MoveX = 1;
  int8_t MoveY = 0;
  int8_t Downward = Time / 26;
  if (Downward - (Time - 1) / 26 == 1)    //it takes 26 sec to move along the line, go down further
    MoveY = 1;
  bool EndGame = false;
  if (Downward % 2 == 1) MoveX = -1;          //depending on the downward movement, determine the right or left moves
  if ((Downward > 8) && (EndGame == false))   // check each line of enemies for collision with a protective block
  {
    EndGame = Over(sheild, Downward);

    if ((Downward > 12) && (EndGame == false))
    {
      EndGame = Over(sheild, Downward);
      if ((Downward > 16) && (EndGame == false))
      {
        EndGame = Over(sheild, MoveY);
        if (EndGame == false)
        {
         EndGame = Over(sheild, Downward);
        }
      }
    }
  }
  if (DeadAllEnemies())   //if we destroyed all blocks, we build them from the biginning
  {
    TimeReset += Time;   // add the past time to implent the movement correctly
    MoveX = 0;
    MoveY = 0;
    EnemyBuilding();
    EnemyLocation(MoveX, MoveY);
  }
  if (EndGame == true)
  {
    ship.GameEnd = true;
  }
  EnemyLocation(MoveX, MoveY);

}

vector<BlockOfEnemies::Shell> BlockOfEnemies::Attack()
{
  Shell shell;                //randomly determines who shoots, the fewer enemies, the narrower the range of random value
  shell.x = 1;
  shell.y = 1;

 if (NumberOfEnemies > 0)
 {
    int R = rand() % NumberOfEnemies;
    if (R < 2)
    {
      int X = rand() % 11;

      if (Enemies[X + 22].y != 0)
      {
        shell.y = Enemies[X + 22].y + 3;
        shell.x = Enemies[X+22].x;
      }
      else
        if (Enemies[X + 11].y != 0)
        {
          shell.y = Enemies[X + 11].y + 3;
          shell.x = Enemies[X+11].x;
        }
        else
          if (Enemies[X].y != 0)
          {
            shell.y = Enemies[X].y + 3;
            shell.x = Enemies[X].x;
          }
    }
  }

  if (shell.y > 1)            //check if the shot was
    shells.push_back(shell);
  return shells;
}

int8_t BlockOfEnemies::Death(MyShip::Shell shell)     // if the shell hits the enemy, then the enemy is reset. Will not be displayed on the field later
{
  int8_t k = 0;
  for (int8_t i = 33; i >= 0; --i)
  {
    for (int8_t j = 0; j < 5; ++j)
    {
      if ((Enemies[i].y + 2 == shell.y) and (Enemies[i].x + j == shell.x))
      {
        DeadEnemies++;
        NumberOfEnemies--;
        k = i;
        return k;
      }
      else k = -1;
    }
  }
  return k;
}

bool BlockOfEnemies::Over(Sheild& sheild, int8_t& y)   // check for collision with protection and ship
{ 
  bool r = true;
  for (int i = 0; i < 3; ++i)           //check the collision with the ship or with protective blockss
  {
    if (sheild.sheilds[i].live != 0)
      r = false;
  }
  if (r == true)              //we check each line of enemies, if there are enemies in the line, there will be a colision with ship
  {
    if (y == 20)
    {
      for (int i = 21; i < 32; ++i)
      {
        if (Enemies[i].y != 0)
          return true;
      }
    }
    if (y == 24)
    {
      for (int i = 11; i < 21; ++i)
      {
        if (Enemies[i].y != 0)
          return true;
      }
    }
    if (y == 28)
    {
      for (int i = 0; i < 10; ++i)
      {
        if (Enemies[i].y != 0)
          return true;
      }
    }
  }
  else {
    if (y == 9)             //we check each line of enemies, if there are enemies in the line, there will be a colision with protection blocks
    {
      for (int i = 21; i < 32; ++i)
      {
        if (Enemies[i].y != 0)
          return true;
      }
    }
    if (y == 13)
    {
      for (int i = 11; i < 21; ++i)
      {
        if (Enemies[i].y != 0)
          return true;
      }
    }
    if (y == 17)
    {
      for (int i = 0; i < 10; ++i)
      {
        if (Enemies[i].y != 0)
          return true;
      }
    }
  }
}

Sheild::Sheild()
{
  const int8_t Y = 27;
  for (int8_t i = 0; i < 3; ++i)
  {
    sheilds[i].x = 11 + 24 * i;
    sheilds[i].y = Y;
    sheilds[i].live = 12;
  }
}

bool Sheild::Destruction(BlockOfEnemies::Shell& shell)
{
  for (int8_t i = 0; i < 3; ++i)
    for (int8_t j = 0; j < sheilds[i].live; ++j)
    {
      if ((sheilds[i].x + j == shell.x) and (sheilds[i].y == shell.y))
        if (sheilds[i].live != 0)
        {
          sheilds[i].live--;
          return true;
        }
    }
  return false;
}

bool Sheild::Destruction(MyShip::Shell&  shell)
{
  for (int8_t i = 0; i < 3; ++i)
    for (int8_t j = 0; j < sheilds[i].live; ++j)
    {
      if ((sheilds[i].x + j == shell.x ) and (sheilds[i].y + 4 == shell.y))
        if (sheilds[i].live != 0)
        {
          sheilds[i].live--;
          return true;
        }
    }
  return false;
}

MyShip::MyShip()
{
  live = 3;
  GameEnd = false;
  x = 9;
  y = 38;
  Point = 0;
}

void MyShip::Move(int8_t& X)
{
  if ((x < 72) && (x > 2) || ((x == 72) && (X < 0)) || ((x == 2) && (X > 0)))   //check if the ship went out of the border
    x += X;

}

bool BlockOfEnemies::DeadShip(MyShip &ship, int8_t &j)
{
  for (int8_t i = 0; i < 10; ++i)
    if ((ship.x + i == shells[j].x ) and (ship.y == shells[j].y))
    {
      ship.live--;
      if (ship.live < 0)
      {
        ship.GameEnd = true;
      }
      return true;
    }
  return false;
}

MyShip::Shell MyShip::Attack()
{
  Shell shell;
  shell.x = x + 4;
  shell.y = y - 1;
  return shell;
}


bool BlockOfEnemies::DeadAllEnemies()
{
  if (DeadEnemies == 33) return true;
  return false;
}

void MyShip::Shell::Move()
{
  y--;
  //Serial.print8_tln(y);
}

bool MyShip::Shell::EndField()
{
  if (y == 0) return true;
  return false;
}

void BlockOfEnemies::Shell::Move()
{
  y++;
}

bool BlockOfEnemies::Shell::EndField()
{
  if (y == 48) return true;
  return false;
}
