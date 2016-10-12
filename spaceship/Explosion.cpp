#include "Explosion.h"
//////////////////////////////////////////////
/////////Explosion///////////////////////
/////////////////////////////////////////////

Explosion::Explosion() : GameObject(EXPLOSION)
{

}

void Explosion::Initialise(Vector2D position, Vector2D velocity, float animationSpeed, float scale)
{
  m_drawDepth = 6;
  m_velocity = velocity;
  m_position = position;
  m_animationSpeed = 0;
  m_currentAnimation = 0.0f;
  m_imageScale = scale;       // Part of the superclass

  // Loading a sequence of images for animation
  LoadImage(L"explosion1.bmp");
  LoadImage(L"explosion2.bmp");
  LoadImage(L"explosion3.bmp");
  LoadImage(L"explosion4.bmp");
  LoadImage(L"explosion5.bmp");
  LoadImage(L"explosion6.bmp");
  LoadImage(L"explosion7.bmp");
  LoadImage(L"explosion8.bmp");
}

void Explosion::Update(float frametime)
{
  m_animationSpeed = m_animationSpeed + 0.6;

  m_position = m_position + m_velocity*frametime;

  if (m_animationSpeed >= 7)
  {
    m_animationSpeed = 7;
    m_imageNumber = 7;
    m_active = false;
  }
  else
  {
    m_imageNumber = m_animationSpeed;
  }

}

IShape2D& Explosion::GetCollisionShape()
{
  m_collider.PlaceAt(m_position, 32.0f* m_imageScale);
  return m_collider;
}

void Explosion::ProcessCollision(GameObject& other)
{
  // No-op
}