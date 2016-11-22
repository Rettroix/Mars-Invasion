#pragma once

#include "GameObject.h"
#include "mysoundengine.h"
#include "GameObject.h"
#include "Spaceship.h"

class BulletUI : public GameObject
{
private:
  Vector2D m_velocity;
  float m_time;
  Circle2D m_circle;
  Circle2D m_collider;
  float m_fuel;
  Spaceship *m_pPlayer;
  float maxBullets;
  float bulletAmmount;
  int firstFrame;
  int positionAlong;
  int uiType;
  float maxHealth;
  float healthAmmount;
  float maxFuel;
  float fuelAmmount;

public:

  void Initialise(Spaceship *player, int startingFrame, int selected, int selectUI);

  void Update(float frameTime);
  IShape2D& GetCollisionShape();
  void Draw();
  void ProcessCollision(GameObject& other);
  void addFuel(float fuel);
  void frameIncrementer(int ammount, int a);
  BulletUI();
};


