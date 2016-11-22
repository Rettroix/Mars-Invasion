#include "EnemyOne.h"
#include "Explosion.h"
#include "gamecode.h"
//////////////////////////////////////////////////////
//////////////Enemy One////////////////////////////////
//////////////////////////////////////////////////////

void EnemyOne::Initialise(Vector2D startPosition, Spaceship *player, Missile *missile)
{

  m_pMissile = missile;
  m_pPlayer = player;

  m_drawDepth = 12;

  LoadImage(L"Enemy1.png");

  m_position = startPosition;

  incrementFrame = 0;

  m_imageScale = 4;

}

void EnemyOne::Update(float frameTime)
{
  m_frameTime = frameTime;

  if (m_position.XValue < m_pPlayer->GetPosition().XValue - 3000)
  {
    Deactivate();
  }

  m_position = m_pMissile->GetPosition();

  m_angle = m_pMissile->getRotationToPlayer();


  m_imageNumber = 0;

}

IShape2D& EnemyOne::GetCollisionShape()
{
  collisionShape.PlaceAt(m_position, 70);
  return collisionShape;


}

void EnemyOne::Draw()
{

  GameObject::Draw();
  MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();
  //pTheDrawEngine->DrawLine(sensor.GetStart(), sensor.GetEnd(), 65525);
  //pTheDrawEngine->FillCircle(m_position, 70, 65525);
}

Vector2D EnemyOne::getPosition()
{
  return m_position;
}

Vector2D EnemyOne::getInitialPosition()
{
  return initialPosition;


}

void EnemyOne::changeInitialPosition(Vector2D pos)
{
  initialPosition = pos;
}


void EnemyOne::ProcessCollision(GameObject& other)
{
  if (other.GetType() == BULLET)
  {
   

    Explode();
    Deactivate();
  }

}


void EnemyOne::RotateTo(float angle)
{
  // Rotate to the given angle

  if (abs(m_angle) - abs(angle) < 0.05 && abs(m_angle) - abs(angle) > -0.05)
  {
    m_angle = angle;
  }
  else
  {
    if (m_angle > angle)
    {
      m_angle -= 0.1f;
    }
    else if (m_angle < angle)
    {
      m_angle += 0.1f;
    }
  }
}

float EnemyOne::getAngle()
{
  return m_angle;
}

void EnemyOne::Explode()
{
  //Deactivate();
  m_imageNumber = 1;
  Explosion* pExp = new Explosion;
  //  g_soundFX.PlayExplosion();

  pExp->Initialise(m_position, Vector2D(0, 0), 4.5f, 4.5f);

  Game::instance.m_objects.AddItem(pExp, false);

  

  // g_soundFX.StopThrust();			// In case it is playing
}

EnemyOne::EnemyOne() :GameObject(ENEMY)
{
}