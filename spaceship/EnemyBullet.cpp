#include "EnemyBullet.h"
#include "Particles.h"
#include "gamecode.h"

EnemyBullet::EnemyBullet() : GameObject(ENEMYBULLET)
{

}

void EnemyBullet::Initialise(Vector2D position, Vector2D velocity, float angl)
{
  m_acceleration = 700;
  m_position = position;
  m_velocity = velocity;
  m_timer = 2.0;
  m_animationSpeed = 0;
  m_currentAnimation = 0.0f;
  LoadImage(L"enemy_missile.png");
  m_imageScale = 64 / 16;

  m_drawDepth = 6;
  m_angle = angl - 3.2f;
}

void EnemyBullet::Update(float frametime)
{
  /*Vector2D acc;
  acc.setBearing(m_angle, m_acceleration);
  m_velocity = m_velocity + acc*frametime;*/
  m_velocity = m_velocity + Vector2D(0, -20);

  m_timer -= frametime;
  m_position = m_position + m_velocity*frametime;

  //m_position = m_position + Vector2D(0, -20);

  if (MyDrawEngine::GetInstance()->theCamera.returnPosition().XValue + 2000 < m_position.XValue ||
    MyDrawEngine::GetInstance()->theCamera.returnPosition().XValue - 2000 > m_position.XValue ||
    m_position.YValue > 2000)
  {
    Deactivate();
  }

}

IShape2D& EnemyBullet::GetCollisionShape()
{
  collisionShape.PlaceAt(m_position, 70);
  return collisionShape;
}

void EnemyBullet::ProcessCollision(GameObject& other)
{
  if (other.GetType() != ENEMY )
  {

    Particles* pParticles = new Particles;
    pParticles->Initialise(m_position, Vector2D(0, 0), 4.5f, 2.0f);
    Game::instance.m_objects.AddItem(pParticles, false);
    Deactivate();
  }






}


