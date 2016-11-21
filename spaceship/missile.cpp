#include "missile.h"
#include "Explosion.h"
#include "gamecode.h"

//////////////////////////////////////////////////////
//////////////missile////////////////////////////////
//////////////////////////////////////////////////////

void Missile::Initialise(Vector2D startPosition, Spaceship *player)
{
  m_friction = 1.5f;
  m_acceleration = 6000.0f;
  m_velocity.set(0, 0);

  m_pPlayer = player;
  m_drawDepth = 12;

  LoadImage(L"enemy_missile.png");

  m_position = startPosition;

  incrementFrame = 0;
  
  m_imageScale = 4;
  sensorPosition = (m_position + Vector2D(0, 2000));
  sensor.PlaceAt(m_position,sensorPosition);
}

void Missile::Update(float frameTime)
{
  m_frameTime = frameTime;


  if (m_position.XValue < m_pPlayer->GetPosition().XValue - 3000)
  {
    Deactivate();
  }
  
  m_imageNumber = 0;
  sensorPosition.setBearing(m_angle, -m_angle*10);
  sensor.PlaceAt(m_position, sensorPosition);

  if (!sensor.Intersects(m_pPlayer->GetCollisionShape()))
  {
    m_angle -= 8000*m_frameTime;
  }
 

  //if (sensor.GetStart().XValue < m_pPlayer->GetPosition().XValue &&
  //  !sensor.Intersects(m_pPlayer->GetCollisionShape()))
  //{
  //  m_angle += 8000 * m_frameTime;
  //}

  if (sensor.Intersects(m_pPlayer->GetCollisionShape()))
  {
    Vector2D acc;
    acc.setBearing(m_angle, m_acceleration);
    m_velocity = m_velocity + acc*m_frameTime;

    rotationToPlayer = m_angle;
    // Process movement


  }
  

  m_velocity = m_velocity - m_friction*m_frameTime*m_velocity;
  m_position = m_position + m_velocity*m_frameTime;

}

IShape2D& Missile::GetCollisionShape()
{
  collisionShape.PlaceAt(m_position, 70);
  return collisionShape;


}

void Missile::Draw()
{

  GameObject::Draw();
  MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();
  /*pTheDrawEngine->DrawLine(sensor.GetStart(), sensor.GetEnd(), 65525);*/

}

Vector2D Missile::getPosition()
{
  return m_position;
}

Vector2D Missile::getInitialPosition()
{
  return initialPosition;


}

void Missile::changeInitialPosition(Vector2D pos)
{
  initialPosition = pos;
}


void Missile::ProcessCollision(GameObject& other)
{
  if (other.GetType() == BULLET)
  {
    Explode();
    Deactivate();

  }

}

float Missile::getAngle()
{
  return m_angle;
}

float Missile::getRotationToPlayer()
{
  return rotationToPlayer;
}

void Missile::Explode()
{
  //Deactivate();
  m_imageNumber = 1;
  Explosion* pExp = new Explosion;
  //  g_soundFX.PlayExplosion();

  pExp->Initialise(m_position, Vector2D(0, 0), 4.5f, 4.5f);

  Game::instance.m_objects.AddItem(pExp, false);

  

  // g_soundFX.StopThrust();			// In case it is playing
}

Missile::Missile() :GameObject(ENEMY)
{
}