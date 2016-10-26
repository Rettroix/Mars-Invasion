#pragma once

#include "GameObject.h"
#include "mysoundengine.h"
#include "GameObject.h"
#include "Spaceship.h"

class BuildingBackground : public GameObject
{
private:
  Vector2D m_velocity;
  float m_time;
  Circle2D m_circle;
  Circle2D m_collider;
  float incrementFrame;
  Vector2D initialPosition;
  Spaceship *m_pPlayer;

public:

  void Initialise(Vector2D startPosition, Spaceship *player);

  void Update(float frameTime);
  IShape2D& GetCollisionShape();

  void ProcessCollision(GameObject& other);
  void changeInitialPosition(Vector2D pos);
  Vector2D getInitialPosition();
  Vector2D getPosition();

  BuildingBackground();
};