#pragma once

#include "GameObject.h"
#include "mysoundengine.h"
#include "GameObject.h"

// Create your game entity classes here

const struct globalstuffs
{
  Vector2D shipPosition;
  float fuel;
};


class Building : public GameObject
{
private:
  Vector2D m_velocity;
  float m_time;
  Circle2D m_circle;
  Circle2D m_collider;
  float incrementFrame;

public:

  void Initialise(Vector2D startPosition);

  void Update(float frameTime);
  IShape2D& GetCollisionShape();

  void ProcessCollision(GameObject& other);
  Building();
};

// Class to handle the spaceship
class Spaceship : public GameObject
{
private:
  Vector2D m_velocity;		// Velocity of the ship
  Circle2D m_collider;		// Used for collision
  float m_shootDelay;       // Time in seconds before ship can shoot again
  bool m_thrusting;			// Whether ship is currently thrusting
  float m_fuel;         //The ship's fuel
  
public:
  Spaceship();
  void Initialise(Vector2D position);		// Sets to the starting position
  void Update(float frametime);			// Handle input, shooting and movement
  IShape2D& GetCollisionShape();			// Provides a collision area
  void ProcessCollision(GameObject& other);	// Makes ship explode if hit by an asteroid
  void Explode();							// Deactivates ship and creates an explosion
  void fuelManagement();
};

class City : public GameObject
{
private:    
  Circle2D m_circle;
  Circle2D m_collider;
  float incrementFrame;

public:

  void Initialise(float timeDelay);

  void Update(float frameTime);
  IShape2D& GetCollisionShape();

  void ProcessCollision(GameObject& other);
  City();
};

class BuildingForeground : public GameObject
{
private:
  Vector2D m_velocity;
  float m_time;
  Circle2D m_circle;
  Circle2D m_collider;
  float incrementFrame;
  Vector2D initialPosition;

public:

  void Initialise(Vector2D startPosition);

  void Update(float frameTime);
  IShape2D& GetCollisionShape();

  void ProcessCollision(GameObject& other);
  BuildingForeground();
};

class BuildingBackground : public GameObject
{
private:
  Vector2D m_velocity;
  float m_time;
  Circle2D m_circle;
  Circle2D m_collider;
  float incrementFrame;
  Vector2D initialPosition;

public:

  void Initialise(Vector2D startPosition);

  void Update(float frameTime);
  IShape2D& GetCollisionShape();

  void ProcessCollision(GameObject& other);
  BuildingBackground();
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
  void Initialise(Vector2D position, Vector2D velocity);
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
