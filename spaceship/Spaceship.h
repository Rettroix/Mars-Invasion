#pragma once

#include "GameObject.h"
#include "mysoundengine.h"
#include "GameObject.h"

// class makes the player spaceship
class Spaceship : public GameObject
{
private:
  int damageDelay;
  int score;
  Circle2D collisionShape;
  Vector2D m_velocity;		// Velocity of the ship
  Circle2D m_collider;		// Used for collision
  float m_shootDelay;       // Time delay when the player can shoot
  bool m_thrusting;			// Whether ship is currently thrusting
  float m_fuel;         //The ship's fuel
  bool m_landed;        //has ship landed
  float m_health;       //ships health
  Vector2D gravity = Vector2D(0.0f, 1000.0f); //gravity of the ship
  bool isLanded;
  float m_friction;
  float m_acceleration;
  bool gameOver;
  float bullets;
  int enemyOneCoolDown;
  int m_lives;
  int m_damage;
  float m_damageDelay;

  float m_invinsibleTime;
  bool m_isInvinsible;

  float m_respawnTime;
  bool m_respawnCounting;
  float m_frameTime;

  float health;
  int thrustTime;

  int m_bombCounter;

  //sound
  MySoundEngine* pSoundEngine = MySoundEngine::GetInstance();
  SoundIndex recharge = pSoundEngine->LoadWav(L"recharge.wav");

  SoundIndex explosion = pSoundEngine->LoadWav(L"explosion.wav");
  SoundIndex thrust = pSoundEngine->LoadWav(L"thrusting.wav");
  SoundIndex whoosh = pSoundEngine->LoadWav(L"whoosh.wav");


public:
  Spaceship();
  void Initialise(Vector2D position);		// Sets to the starting position
  void Update(float frametime);			// Handle input, shooting and movement
  void Draw();
  IShape2D& GetCollisionShape();			// Provides a collision area
  void ProcessCollision(GameObject& other);	// Makes ship explode if hit by an asteroid
  void Explode();							// Deactivates ship and creates an explosion
  void fuelManagement();
  float getFuel();
  float getMaxFuel();

  void Bounce(GameObject &other);
  void Land(GameObject &other);
  float getAngle();
  Vector2D getVelocity();
  float getAcceleration();
  void thrustChange();  //increases thrust speed
  void RotateTo(float angle);
  float getMaxBullets();
  float getBullets();
  float getMaxHealth();
  float getHealth();
  float getSpeed();
  int getScore();
  bool isGameOver();
  void addScore(int ammount);
  void incrementBombCounter();
  int getBombCounter(); //returns bomb counter
  void doDamage();  //deal damage to the player
  void teleport(Vector2D  pos); //moves spaceship to specified position
  void UpdateDamage();  //update damage effects
  void ShootBombs();  //shoot bombs
  void ShootBullets();  //shoots bullets
  void HandleControl(float frametime);  //move spaceship around with keyboard
  Vector2D& getPosition();
};