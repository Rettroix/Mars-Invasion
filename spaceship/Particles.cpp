#include "Particles.h"
//////////////////////////////////////////////
/////////Particles///////////////////////
/////////////////////////////////////////////

Particles::Particles() : GameObject(EXPLOSION)
{

}

void Particles::Initialise(Vector2D position, Vector2D velocity, float animationSpeed, float scale)
{
  m_drawDepth = 6;
  m_velocity = velocity;
  m_position = position + Vector2D(0,-50);
  m_animationSpeed = 0;
  m_currentAnimation = 0.0f;
  m_imageScale = scale;       // Part of the superclass

  // Loading a sequence of images for animation
  LoadImage(L"particles1.png");
  LoadImage(L"particles2.png");
  LoadImage(L"particles3.png");
  LoadImage(L"particles4.png");
  LoadImage(L"particles5.png");
  LoadImage(L"particles6.png");
  LoadImage(L"particles7.png");
  LoadImage(L"particles8.png");
  LoadImage(L"particles9.png");
  LoadImage(L"particles10.png");
  LoadImage(L"particles11.png");
  LoadImage(L"particles12.png");
  LoadImage(L"particles13.png");
  LoadImage(L"particles14.png");
  LoadImage(L"particles15.png");
  LoadImage(L"particles16.png");
  LoadImage(L"particles17.png");
  LoadImage(L"particles18.png");
  LoadImage(L"particles19.png");
  LoadImage(L"particles20.png");
  LoadImage(L"particles21.png");
  LoadImage(L"particles22.png");
  LoadImage(L"particles23.png");
  LoadImage(L"particles24.png");
  LoadImage(L"particles25.png");
  LoadImage(L"particles26.png");
  LoadImage(L"particles27.png");





}

void Particles::Update(float frametime)
{
  m_animationSpeed = m_animationSpeed + 0.6;

  m_position = m_position + m_velocity*frametime;

  if (m_animationSpeed >= 27)
  {
    m_animationSpeed = 27;
    m_imageNumber = 27;
    m_active = false;
  }
  else
  {
    m_imageNumber = m_animationSpeed;
  }

}

IShape2D& Particles::GetCollisionShape()
{
  m_collider.PlaceAt(m_position, 32.0f* m_imageScale);
  return m_collider;
}

void Particles::ProcessCollision(GameObject& other)
{
  // No-op
}