#pragma once

#include "GameObject.h"
#include "mysoundengine.h"
#include "GameObject.h"
#include "Spaceship.h"

class Particles : public GameObject
{
private:
  Vector2D m_velocity;    // Note that my explosions move.  
  Circle2D m_collider;
  float m_animationSpeed;   // Frames of animation per second
  float m_currentAnimation; // Current animation frame
public:
  Particles();

  // Sets starting conditions
  void Initialise(Vector2D position, Vector2D velocity, float animationSpeed, float scale);
  void Update(float frametime);		// Movement and animation
  IShape2D& GetCollisionShape();	// Returns a circle for collision check
  void ProcessCollision(GameObject& other);		// needed by engine, but not used
};