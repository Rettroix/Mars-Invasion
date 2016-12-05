
#include "entities.h"
#include "gamecode.h"
#include "myinputs.h"
#include "Explosion.h"
#include "playerMissile.h"
const float SHIPSIZE = 64.0f;			// Diameter of the ship

PlayerMissile::PlayerMissile() : GameObject(BULLET)
{

}

void PlayerMissile::Initialise(Vector2D position, Vector2D velocity, float angl)
{

  m_acceleration = 700;
  m_position = position;
  m_velocity = velocity;
  m_animationSpeed = 0;
  m_currentTime = 0.0f;
  LoadImage(L"missileBlue.png");

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

  m_currentTime += 1;
  m_position = m_position + m_velocity*frametime;

  if (m_currentTime >= 13)
  {
    Explosion* pExp = new Explosion;

    pExp->Initialise(m_position, Vector2D(0, 0), 4.5f, 40.0f);

    Game::instance.m_objects.AddItem(pExp, true);
    Deactivate();

  }
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
    m_position.YValue > 2000 || m_position.YValue < -2000)
  {
    pSoundEngine->Play(explosion, false);
    Explosion* pExp = new Explosion;

    pExp->Initialise(m_position, Vector2D(0, 0), 4.5f, 40.0f);

    Game::instance.m_objects.AddItem(pExp, true);

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
  if (other.GetType() == ENEMY || other.GetType() == LANDER || other.GetType() == COLLIDER)
  {
    pSoundEngine->Play(explosion, false);

    Explosion* pExp = new Explosion;

    pExp->Initialise(m_position, Vector2D(0, 0), 4.5f, 40.0f);

    Game::instance.m_objects.AddItem(pExp, true);
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