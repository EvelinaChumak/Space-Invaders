#include "SpaceInvaders.h"
//#include "Methotds.cpp"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

Adafruit_PCD8544 display = Adafruit_PCD8544(9, 10, 11, 12, 13);


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
        X = Enemies.Enemies[i].x +j;
        Y = Enemies.Enemies[i].y +k;
        display.drawPixel(X, Y, BLACK);
      }
    }
  }
 // display.display();
}

void drawShield(Shield &shield)
{
  uint8_t X ;
  uint8_t Y ;
  
  for (uint8_t k = 0; k < 6; ++k)
  {
   for (uint8_t i = 0; i < 12; ++i)
    {
      Y = shield.Shields[0].y + i;
      for (uint8_t j = 0; j < 3; ++j)
      {
      X = shield.Shields[j].x + i;
      Y = shield.Shields[j].y + k;
      display.drawPixel(X, Y, BLACK);
      }
    }
  }
  //display.display();
}

void drawship(MyShip &ship)
{
  int8_t X = ship.x+3;        
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
      display.drawPixel(X, Y+1, BLACK);
  }
 // display.display();
}
