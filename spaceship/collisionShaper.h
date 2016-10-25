#pragma once

#include "GameObject.h"
#include "mysoundengine.h"
#include "GameObject.h"
#include "Spaceship.h"
#include "Building.h"

class CollisionShaper : public GameObject
{
private:
  Segment2D collisionShape;

  Vector2D m_velocity;
  float m_time;
  Circle2D m_circle;
  Circle2D m_collider;
  float incrementFrame;
  Vector2D initialPosition;
  Building *m_pBuilding;
  float position1;
  float position2;
  float position3;
  float position4;
  int selectedType;

public:

  void Initialise(Building *pBuilding, float pos1, float pos2, float pos3, float pos4, int coltype);
  void Draw();
  void Update(float frameTime);
  IShape2D& GetCollisionShape();
  float GetTop();
  void ProcessCollision(GameObject& other);
  CollisionShaper();
};