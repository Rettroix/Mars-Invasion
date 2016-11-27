#pragma once

#include "GameObject.h"
#include "mysoundengine.h"
#include "GameObject.h"
#include "Spaceship.h"

class BombUI : public GameObject
{
private:
  Vector2D m_velocity;
  float m_time;
  Circle2D m_circle;
  Circle2D m_collider;
  Spaceship *m_pPlayer;
  float bombAmmount;
  float positionAlong;

public:

  void Initialise(Spaceship *player, int offset);

  void Update(float frameTime);
  IShape2D& GetCollisionShape();
  void Draw();
  void ProcessCollision(GameObject& other);
  void addFuel(float fuel);
  void frameIncrementer(int ammount, int a);
  BombUI();
};