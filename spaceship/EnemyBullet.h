#pragma once

#include "GameObject.h"
#include "mysoundengine.h"
#include "Spaceship.h"

class EnemyBullet : public GameObject
{
private:
  Vector2D m_velocity;
  Circle2D collisionShape;
  float m_acceleration;
  float m_timer;  // Lifetime

  float m_animationSpeed;   // Frames of animation per second
  float m_currentAnimation; // Current animation frame

public:
  EnemyBullet();
  void Initialise(Vector2D position, Vector2D velocity, float angl);
  void Update(float frametime);
  IShape2D& GetCollisionShape();
  void ProcessCollision(GameObject& other);

};