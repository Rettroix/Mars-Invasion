#pragma once

#include "GameObject.h"
#include "mysoundengine.h"
#include "GameObject.h"
#include "Spaceship.h"

class Missile : public GameObject
{
private:
  Circle2D collisionShape;
  Vector2D m_velocity;
  void Draw();
  float m_time;
  Circle2D m_circle;
  Circle2D m_collider;
  float incrementFrame;
  Vector2D initialPosition;
  Spaceship *m_pPlayer;

  float rotationToPlayer;
  float m_friction;
  float m_acceleration;

  float m_frameTime;

  Vector2D sensorPosition;
  Segment2D sensor;

public:

  void Initialise(Vector2D startPosition, Spaceship *player);

  void Update(float frameTime);
  IShape2D& GetCollisionShape();
  Vector2D getInitialPosition();
  void ProcessCollision(GameObject& other);
  Vector2D getPosition();
  void changeInitialPosition(Vector2D pos);
  float getAngle();
  float getRotationToPlayer();
  Missile();
};