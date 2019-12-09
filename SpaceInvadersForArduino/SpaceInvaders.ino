#include "SpaceInvaders.h"
#include "Interface.h"

#define ButB  3
#define ButD  5
#define ButA  2


void setup() {
  pinMode(7, OUTPUT);     
  digitalWrite(7, LOW);   //7th port as ground
  pinMode(ButB, INPUT_PULLUP);
  pinMode(ButD, INPUT_PULLUP);

  Serial.begin(9600);

  display.begin();

  display.setContrast(60);
  //display.setReinitInterval(30);
  //display.setBias(4);

  display.clearDisplay();

  MyShip ship;
  BlockOfEnemies enemies;
  Sheild sheild;
  enemies.EnemyBuilding();


  drawsEnemies(enemies);
  drawSheild(sheild);
  drawship(ship);
  display.display();

  unsigned long TimeForMove = millis();
  unsigned long TimeForAttack = millis();

  while (!ship.GameEnd) {
    if ((millis() - TimeForMove) / 1000 >= 1)     //every second we move and redraw the position
    {
      TimeForMove = millis();
      int c = TimeForMove / 1000 - enemies.TimeReset;
      enemies.Move(sheild, c, ship);
    }

    if ((millis() - TimeForAttack) / 200 >= 1)    //every 200 milliseconds shells move
    {
      TimeForAttack = millis();
      int8_t NumActiveShell = 0;
      int8_t NumActiveShellEnemies = 0;

      while (NumActiveShell < ship.shells.size())
      {
        ship.shells[NumActiveShell].Move();
        int8_t k = enemies.Death(ship.shells[NumActiveShell]);    //check if the enemy was killed
        int8_t j = 1;       //for change the number of active shells
        if ((ship.shells[NumActiveShell].EndField()) or (sheild.Destruction(ship.shells[NumActiveShell])))
        {   //if the shell went out the field or hit the protective block
          ship.shells.popIndex(NumActiveShell);   //remove the shell
          j = 0;
        }
        if (k >= 0)   //if the enemy was killed
        {
          ship.Point += 15;
          ship.shells.popIndex(NumActiveShell);   //remove the shell
          enemies.Enemies[k].x = 0;       //we nullify the enemy
          enemies.Enemies[k].y = 0;
          j = 0;
        }
        NumActiveShell += j;
      }


      enemies.shells = enemies.Attack();

      while (NumActiveShellEnemies < enemies.shells.size())
      {
        enemies.shells[NumActiveShellEnemies].Move();
        int j = 1;      //for change the number of active shells

        if ((enemies.DeadShip(ship, NumActiveShellEnemies)))    //if you hit the ship
        {
          enemies.shells.popIndex(NumActiveShellEnemies);   // //remove the shell
          j = 0;
        }
        if ((enemies.shells.size() > 0) and (!ship.GameEnd))
          if ((enemies.shells[NumActiveShellEnemies].EndField()) or (sheild.Destruction(enemies.shells[NumActiveShellEnemies])))
          {   ///if the shell went out the field or hit the protective block
            enemies.shells.popIndex(NumActiveShellEnemies);   //remove the shell
            j = 0;
          }
        NumActiveShellEnemies += j;
      }

    }

    if (digitalRead(ButB) == LOW)
    {
      int8_t i = 1;
      ship.Move(i);
    }
    if (digitalRead(ButD) == LOW)
    {
      int8_t i = -1;
      ship.Move(i);
    }
    if (digitalRead(ButA) == LOW)
    {
      delay(70);
      ship.shells.push_back(ship.Attack());
    }
    display.clearDisplay();
    for (int i = 0; i < ship.shells.size(); ++i)
      drawShipAttack(ship.shells[i]);
    for (int i = 0; i < enemies.shells.size(); ++i)
      drawEnemiesAttack(enemies.shells[i]);
    drawsEnemies(enemies);
    drawSheild(sheild);
    drawship(ship);
    drawShipLives(ship);
    drawPoint(ship);
    display.display();
  }
  while (ship.GameEnd)
  {
    display.clearDisplay();
    Result(ship);
    display.display();
  }
}


void loop() {

}
