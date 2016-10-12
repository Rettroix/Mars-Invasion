#pragma once

#include "GameObject.h"
#include "mysoundengine.h"
#include "GameObject.h"
#include "Spaceship.h"

class userInterface : public GameObject
{
private:
  Vector2D m_velocity;
  float m_time;
  Circle2D m_circle;
  Circle2D m_collider;
  float m_fuel;
  Spaceship *m_pPlayer;

public:

  void Intialise(Spaceship *player);

  void Update(float frameTime);
  IShape2D& GetCollisionShape();
  void Draw();
  void ProcessCollision(GameObject& other);
  void addFuel(float fuel);
  userInterface();
};


