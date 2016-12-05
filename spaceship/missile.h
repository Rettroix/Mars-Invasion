//Title     : Missile.h
//Purpose   : Missile is a sensor which spins around and
//            follows the player when they are in sight
//Author    : Elliot Anderson
//Date      : 5/12/16
#pragma once

#include "GameObject.h"
#include "mysoundengine.h"
#include "GameObject.h"
#include "Spaceship.h"
#include "entities.h"

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
  City *m_pCity;
  float rotationToPlayer;
  float m_friction;
  float m_acceleration;

  float m_frameTime;

  Vector2D sensorPosition;
  Segment2D sensor;

  //sound
  MySoundEngine* pSoundEngine = MySoundEngine::GetInstance();

  SoundIndex explosion = pSoundEngine->LoadWav(L"explosion.wav");

public:

  void Initialise(Vector2D startPosition, Spaceship *player, City *city);

  void Update(float frameTime);
  IShape2D& GetCollisionShape();
  Vector2D getInitialPosition();
  void ProcessCollision(GameObject& other);
  Vector2D getPosition();
  void changeInitialPosition(Vector2D pos);
  float getAngle();
  void Explode();
  float getRotationToPlayer();
  Missile();
};