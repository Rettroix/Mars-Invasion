//Title     : BombUI.h
//Purpose   : The user interface to represent the bomb counter
//Author    : Elliot Anderson
//Date      : 5/12/16

#pragma once

#include "GameObject.h"
#include "mysoundengine.h"
#include "GameObject.h"
#include "Spaceship.h"

class BombUI : public GameObject
{
private:
  Circle2D m_collider;  //collision shape
  Spaceship *m_pPlayer; //player pointer
  float positionAlong;  //where the ui element is places relative to the player

public:

  void Initialise(Spaceship *player, int offset); 

  void Update(float frameTime);
  IShape2D& GetCollisionShape();
  void Draw();
  void ProcessCollision(GameObject& other);
  BombUI();
};