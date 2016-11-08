#pragma once

#include "GameObject.h"
#include "mysoundengine.h"
#include "GameObject.h"

class EnemyShip : public GameObject
{
private:
  Rectangle2D collisionShape;
  Vector2D m_velocity;
  float m_time;
  float incrementFrame;


public:

  void Initialise(Vector2D startPosition);
  void Draw();
  void Update(float frameTime);
  IShape2D& GetCollisionShape();
  Vector2D getPosition(); //Get the position of the building
  void ProcessCollision(GameObject& other);
  //IShape2D& GetCollisionShape();
  Rectangle2D GetShape();
  EnemyShip();
};
