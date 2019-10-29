#include "SpaceInvaders.h"
#include "Interface.h"

#define ButB  3
#define ButD  4
void setup() {
pinMode(7, OUTPUT);
digitalWrite(7, LOW);
pinMode(ButB, INPUT_PULLUP);
pinMode(ButD, INPUT_PULLUP);

Serial.begin(9600);

display.begin();

display.setContrast(30);
//display.setReinitInterval(30);
//display.setBias(4);

display.clearDisplay();

MyShip ship;
BlockOfEnemies enemies;
Shield shield;
int x= 0;
int y = 0;
enemies.EnemyLocation(x,y);

drawsEnemies(enemies);
drawShield(shield);
drawship(ship);
display.display();

unsigned long time; // объявление переменной time типа unsigned long
  // передача количества миллисекунд

while (true)
{
  time = millis();
  if ((time%1000 < 20) && (time/1000 > 1))
    {
      time = time / 1000;
      Serial.println(time);
      enemies.Move(shield, time);
    }
   if (digitalRead(ButB) == LOW)
   {
    int i = 1;
    ship.Move(i);
   }
    if (digitalRead(ButD) == LOW)
   {
    int i = -1;
    ship.Move(i);
   }
   display.clearDisplay();
   drawsEnemies(enemies);
   drawShield(shield);
   drawship(ship);
   display.display();
   //delay(10);
}

  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}
