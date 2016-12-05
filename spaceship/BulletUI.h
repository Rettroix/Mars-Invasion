//Title     : BUlletUI.h
//Purpose   : Can be used as an interface for anything not
//            just bullets
//Author    : Elliot Anderson
//Date      : 5/12/16
#pragma once

#include "GameObject.h"
#include "mysoundengine.h"
#include "GameObject.h"
#include "Spaceship.h"

class BulletUI : public GameObject
{
private:
  Circle2D m_collider;  //collision
  Spaceship *m_pPlayer; //player pointer
  float m_maxBullets; //max bullets
  float m_bulletAmmount;  //bullet ammount
  int m_firstFrame; //first frame
  int m_positionAlong;  //how far along it's placed
  int m_uiType; //what type of ui it is
  float m_maxHealth;  //max ammount of health
  float m_healthAmmount;  //health ammount
  float m_maxFuel;  //max ammount of fuel
  float m_fuelAmmount;  //fuel ammount

public:
  //initialise
  void Initialise(Spaceship *player, int startingFrame, int selected, int selectUI);
  //update
  void Update(float frameTime);
  //get collision shape
  IShape2D& GetCollisionShape();
  //draw function
  void Draw();
  //process the collision
  void ProcessCollision(GameObject& other);
  //sets the image number based on first frame added + specific ammount
  void frameIncrementer(int ammount, int a);
  BulletUI();
};


