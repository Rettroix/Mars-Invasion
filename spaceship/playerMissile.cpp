
#include "entities.h"
#include "gamecode.h"
#include "myinputs.h"
#include "Explosion.h"
#include "playerMissile.h"
const float SHIPSIZE = 64.0f;			// Diameter of the ship

PlayerMissile::PlayerMissile() : GameObject(BULLET)
{

}

void PlayerMissile::Initialise(Vector2D position, Vector2D velocity, float angl, Spaceship *m_pPlayer)
{
  m_acceleration = 700;
  m_position = position;
  m_velocity = velocity;
  m_timer = 2.0;
  m_animationSpeed = 0;
  m_currentAnimation = 0.0f;
  LoadImage(L"missileBlue.png");
  LoadImage(L"bullet2.png");
  LoadImage(L"bullet3.png");
  LoadImage(L"bullet4.png");
  LoadImage(L"bullet5.png");
  LoadImage(L"bullet6.png");
  m_imageScale = SHIPSIZE / 16;
  m_drawDepth = 6;
  m_angle = angl - 1.4;
}

void PlayerMissile::Update(float frametime)
{
  /*Vector2D acc;
  acc.setBearing(m_angle, m_acceleration);
  m_velocity = m_velocity + acc*frametime;*/
  m_velocity = m_velocity + Vector2D(0, -20);

  m_animationSpeed = m_animationSpeed + 0.15;
  m_timer -= frametime;
  m_position = m_position + m_velocity*frametime;

  //m_position = m_position + Vector2D(0, -20);
  //if (m_animationSpeed >= 5)
  //{
  //  m_animationSpeed = 5;
  //  m_imageNumber = 5;
  //}
  //else
  //{
  //  m_imageNumber = m_animationSpeed;
  //}

  if (MyDrawEngine::GetInstance()->theCamera.returnPosition().XValue + 2000 < m_position.XValue ||
    MyDrawEngine::GetInstance()->theCamera.returnPosition().XValue - 2000 > m_position.XValue ||
    m_position.YValue > 2000)
  {
    Deactivate();
  }

}

IShape2D& PlayerMissile::GetCollisionShape()
{
  m_collider = m_position;
  return m_collider;
}

void PlayerMissile::ProcessCollision(GameObject& other)
{
  if (other.GetType() != SPACESHIP)
  {
    Deactivate();
  }

  //if (other.GetType() == ASTEROID)
  // {
  // Deactivate();

  // Send message that a bullet has died
  // (The fragment class will need to know)
  //Event evt;
  //evt.position = m_position;
  //evt.pSource = this;
  //evt.type = EVENT_OBJECTDESTROYED;

  //Game::instance.NotifyEvent(evt);
  //}



}