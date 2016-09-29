#pragma once

#include "GameObject.h"
#include "mysoundengine.h"
#include "GameObject.h"

// Create your game entity classes here



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
public:
  Spaceship();
  void Initialise(Vector2D position);		// Sets to the starting position
  void Update(float frametime);			// Handle input, shooting and movement
  IShape2D& GetCollisionShape();			// Provides a collision area
  void ProcessCollision(GameObject& other);	// Makes ship explode if hit by an asteroid
  void Explode();							// Deactivates ship and creates an explosion
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