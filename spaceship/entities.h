#pragma once

#include "GameObject.h"
#include "mysoundengine.h"
#include "GameObject.h"
#include "Spaceship.h"
#include "Building.h"
// Create your game entity classes here






class City : public GameObject
{
private:    
  Circle2D m_circle;
  Circle2D m_collider;
  float incrementFrame;
  int spawnedBuildings[10];
  Vector2D shipsPosition;
  int shipXValue;
  float fship;
  Spaceship *m_pPlayer;

public:

  void Initialise(Spaceship *player);

  void Update(float frameTime);
  IShape2D& GetCollisionShape();

  void ProcessCollision(GameObject& other);
  void addShipPosition(Vector2D pos);
  City();
};





class Bullet : public GameObject
{
private:
  Vector2D m_velocity;
  Point2D m_collider;
  float m_timer;  // Lifetime

  float m_animationSpeed;   // Frames of animation per second
  float m_currentAnimation; // Current animation frame

public:
  Bullet();
  void Initialise(Vector2D position, Vector2D velocity, float angl);
  void Update(float frametime);
  IShape2D& GetCollisionShape();
  void ProcessCollision(GameObject& other);
  
};

class userInterface : public GameObject
{
private:
  Vector2D m_velocity;
  float m_time;
  Circle2D m_circle;
  Circle2D m_collider;
  float m_fuel;

public:

  void Intialise(Vector2D startPosition, Vector2D startVelocity, float timeDelay);

  void Update(float frameTime);
  IShape2D& GetCollisionShape();
  void Draw();
  void ProcessCollision(GameObject& other);
  void addFuel(float fuel);
  userInterface();
};

class Explosion : public GameObject
{
private:
  Vector2D m_velocity;    // Note that my explosions move.  
  Circle2D m_collider;
  float m_animationSpeed;   // Frames of animation per second
  float m_currentAnimation; // Current animation frame
public:
  Explosion();

  // Sets starting conditions
  void Initialise(Vector2D position, Vector2D velocity, float animationSpeed, float scale);
  void Update(float frametime);		// Movement and animation
  IShape2D& GetCollisionShape();	// Returns a circle for collision check
  void ProcessCollision(GameObject& other);		// needed by engine, but not used
};

