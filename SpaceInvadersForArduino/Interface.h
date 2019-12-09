#include "SpaceInvaders.h"
//#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

Adafruit_PCD8544 display = Adafruit_PCD8544(9, 10, 11, 12, 13);  //display connection


void drawsEnemies(BlockOfEnemies& Enemies)
{
  uint8_t X;
  uint8_t Y;

  for (uint8_t k = 0; k < 3; ++k)
  {
    for (uint8_t j = 0; j < 4; ++j)
    {
      for (uint8_t i = 0; i < 33; ++i)
      {
        if (Enemies.Enemies[i].y != 0)
        {
          X = Enemies.Enemies[i].x + j;
          Y = Enemies.Enemies[i].y + k;
          display.drawPixel(X, Y, BLACK);
        }
      }
    }
  }
}

void drawSheild(Sheild& sheild)
{
  uint8_t X ;
  uint8_t Y ;

  for (uint8_t j = 0; j < 3; ++j)
  {
    for (uint8_t k = 0; k < 6; ++k)
    {
      for (uint8_t i = 0; i < sheild.sheilds[j].live; ++i)
      {
        X = sheild.sheilds[j].x + i;
        Y = sheild.sheilds[j].y + k;
        display.drawPixel(X, Y, BLACK);
      }
    }
  }


}

void drawship(MyShip &ship)
{
  int8_t X = ship.x + 3;
  int8_t Y = ship.y ;
  for (int8_t i = 0; i < 3; ++i)
  {
    X++;
    display.drawPixel(X, Y, BLACK);
  }
  X = ship.x;
  for (int8_t i = 0; i < 10; ++i)
  {
    X++;
    display.drawPixel(X, Y + 1, BLACK);
  }
}

void drawShipAttack(MyShip::Shell& shell)
{
  int8_t X = shell.x;
  int8_t Y =  shell.y;
  display.drawPixel(X, Y + 1, BLACK);
}

void drawEnemiesAttack(BlockOfEnemies::Shell& shell)
{
  int8_t X = shell.x;
  int8_t Y =  shell.y;
  display.drawPixel(X, Y + 1, BLACK);
}

void drawShipLives(MyShip &ship)
{
  display.setTextSize(0);
  display.setTextColor(BLACK);
  display.setCursor(63, 0);
  display.println ("L:");
  display.setCursor(77, 0);
  display.println (ship.live);
  display.display();
}

void drawPoint(MyShip& ship)
{
  display.setTextSize(0);
  display.setTextColor(BLACK);
  display.setCursor(1, 0);
  display.println("P:");
  display.setCursor(12, 0);
  display.println(ship.Point);
  display.display();
}

void Result(MyShip &ship)
{
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(15, 15);
  display.println("YOU RESULT");
  display.setCursor(30, 25);
  display.println (ship.Point);
  display.display();
}
