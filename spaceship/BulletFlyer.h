//Title     : BulletFlyer.h
//Purpose   : Bullet shooting enemy that flies in one direction.
//Author    : Elliot Anderson
//Date      : 5/12/16
#pragma once

#include "GameObject.h"
#include "mysoundengine.h"
#include "GameObject.h"
#include "Spaceship.h"
#include "entities.h"
class BulletFlyer : public GameObject
{
private:
  Circle2D collisionShape;
  Vector2D m_velocity;
  void Draw();
  Spaceship *m_pPlayer;   //pointer to player
  float m_shootDelay;       // Time in seconds before it can shoot again
  float m_acceleration;
  City *m_pCity;
  float m_frameTime;

  Vector2D sensorPosition;

  //sound
  MySoundEngine* pSoundEngine = MySoundEngine::GetInstance();

  SoundIndex explosion = pSoundEngine->LoadWav(L"explosion.wav");

public:

  void Initialise(Vector2D startPosition, Spaceship *player, City *city);

  void Update(float frameTime);
  IShape2D& GetCollisionShape();
  void ProcessCollision(GameObject& other);
  Vector2D getPosition();
  float getAngle();
  void Explode();
  BulletFlyer();
};