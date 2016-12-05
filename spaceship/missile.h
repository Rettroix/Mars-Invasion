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
  Circle2D collisionShape;  //collision shape
  Vector2D m_velocity;  //the velocity
  void Draw();
  Spaceship *m_pPlayer; //ship pointer
  City *m_pCity;  //city pointer
  float rotationToPlayer; 
  float m_friction; //friction
  float m_acceleration; //acceleration

  float m_frameTime;  //member frame time

  Vector2D sensorPosition;  //position of the end of the sensor
  Segment2D sensor; //sensor segment

  //loading sound
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
  float getRotationToPlayer();
  Missile();
};