#pragma once

#include "GameObject.h"
#include "mysoundengine.h"
#include "GameObject.h"

// Class to handle the spaceship
class Spaceship : public GameObject
{
private:
  Circle2D collisionShape;
  Vector2D m_velocity;		// Velocity of the ship
  Circle2D m_collider;		// Used for collision
  float m_shootDelay;       // Time in seconds before ship can shoot again
  bool m_thrusting;			// Whether ship is currently thrusting
  float m_fuel;         //The ship's fuel
  bool m_landed;
  float m_health;

public:
  Spaceship();
  void Initialise(Vector2D position);		// Sets to the starting position
  void Update(float frametime);			// Handle input, shooting and movement
  IShape2D& GetCollisionShape();			// Provides a collision area
  void ProcessCollision(GameObject& other);	// Makes ship explode if hit by an asteroid
  void Explode();							// Deactivates ship and creates an explosion
  void fuelManagement();
  float getFuel();
  void HitObject(GameObject &other);
  float getAngle();
  Vector2D& getPosition();
};