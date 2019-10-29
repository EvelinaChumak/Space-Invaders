 //#pragma once

#include "SpaceInvaders.h"
#include <Arduino.h>
//#include <iostream>

void BlockOfEnemies::EnemyLocation(int &MoveX, int &MoveY)        //building enemies. Also used for movement
{
  const int FirstX = 2;
  const int FirstY = 7;
  int ShiftY = 0;
  int ShiftX;
  for (int i = 0; i < 33; ++i)
  {
    ShiftX = 5 * (i%11);
    if (i > 10) ShiftY = 4;
    if (i > 21) ShiftY = 8;
    //if (MoveX < 0) ShiftX = -ShiftX;
    Enemies[i].x = FirstX + ShiftX + MoveX;
    Enemies[i].y = FirstY + ShiftY + MoveY;
  }
}

void BlockOfEnemies::Move(Shield& Shield, unsigned long &Time)       // movement depending on time. It moves every second.
                                // This also checks to complete the game or update the field
{
  int MoveX = Time % 26;
  int MoveY = Time / 26;
  bool EndGame = false;
  if (MoveY % 2 == 1) MoveX = 25 - MoveX;
  if ((MoveY > 8) && (Time % 26 == 0) && (EndGame == false))
  {
    EndGame = Over(Shield,MoveY);

    if ((MoveY > 12) && (EndGame == false))
    {
      EndGame = Over(Shield, MoveY);
      if ((MoveY > 16) && (EndGame == false))
      {
        EndGame = Over(Shield, MoveY);
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
    GameEnd();
  EnemyLocation(MoveX, MoveY);
}

BlockOfEnemies::Position BlockOfEnemies::Attack(int& Frequency)
{
  Position Shell;               //randomly determines who shoots, the fewer enemies, the narrower the range of random value
  Shell.x = 1;
  Shell.y = 1;
  int R; //= random(10) % Frequency;
  if (R = 0)
  {
    int X = random(10) % 11;
    //int X=0;
    if (Enemies[X + 22].y == 0)
      if (Enemies[X + 11].y == 0)
        if (Enemies[X].y == 0)
          if (Frequency > 0)
            Frequency -= 1;
          else Frequency = 1;
        else Shell.y = Enemies[X].y;
      else Shell.y = Enemies[X + 11].y;
    else Shell.y = Enemies[X + 22].y;
    Shell.x = X;
  }
  return Shell;
}

void BlockOfEnemies::Death(MyShip::Shell &shell)     // if the shell hits the enemy, then the enemy is reset. Will not be displayed on the field later
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

bool BlockOfEnemies::Over(Shield& Shield, int& y)   // check for collision with protection.  If it’s not there, we
{                         // move until we are too close to our ship
  bool r = true;
  for (int i = 0; i < 3; ++i)
  {
    if (Shield.Shields[i].live != 0)
      r = false;
  }

  if (r == true)
  {
    if (y == 8)
    {
      for (int i = 21; i < 32; ++i)
      {
        if (Enemies[i].y != 0)
          return true;
      }
    }
    if (y == 12)
    {
      for (int i = 11; i < 21; ++i)
      {
        if (Enemies[i].y != 0)
          return true;
      }
    }
    if (y == 16)
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

Shield::Shield()
{
  const int Y = 27;
  for (int i = 0; i < 3; ++i)
  {
    Shields[i].x = 11 + 24 * i;
    Shields[i].y = Y;
    Shields[i].live = 6;
  }
}

void BlockOfEnemies::ProjectileMovement(Position& Projectile)
{
  Projectile.y += 1;
}

void Shield::Destruction(BlockOfEnemies::Position& Projectile)
{
  for (int i = 0; i<3; ++i)
    for (int j = 0; j < 12; ++j)
    {
      bool q = true;
      if (Projectile.x == Shields[i].x + j)
      {
        q = false;
        Shields[i].live -= 1;
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
  if ((x < 72) && (x > 2) || ((x == 72) && (X < 0)) || ((x == 2) && (X > 0)))
  x += X;

}

MyShip::Shell MyShip::Attack()
{
  Shell shell;
  shell.x = x;
  shell.y = y;
  return shell;
}

void BlockOfEnemies::DeathShip(MyShip& ship, Position& shell)
{
  
  if (ship.x == shell.x)
    ship.live -= 1;
  if (ship.live < 0)
    GameEnd();
}
