#pragma once

#include "GameObject.h"
#include "mysoundengine.h"
#include "GameObject.h"
#include "Spaceship.h"


class PlayerMissile : public GameObject
{
private:
  Vector2D m_velocity;
  Point2D m_collider;
  float m_acceleration;
  float m_timer;  // Lifetime
  Spaceship *m_pPlayer;

  float m_animationSpeed;   // Frames of animation per second
  float m_currentAnimation; // Current animation frame
  
  //sound
  MySoundEngine* pSoundEngine = MySoundEngine::GetInstance();
  SoundIndex recharge = pSoundEngine->LoadWav(L"recharge.wav");

  SoundIndex explosion = pSoundEngine->LoadWav(L"explosion.wav");
public:
  PlayerMissile();
  void Initialise(Vector2D position, Vector2D velocity, float angl, Spaceship *player);
  void Update(float frametime);
  IShape2D& GetCollisionShape();
  void ProcessCollision(GameObject& other);

};

