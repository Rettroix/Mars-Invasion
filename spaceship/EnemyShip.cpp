#include "EnemyShip.h"
#include "Explosion.h"
#include "gamecode.h"
#include "entities.h"
#include "EnemyBullet.h"
const float SHOOTDELAY = 1.0f;	// Time between each spaceship bullet
const float SHIPSIZE = 64.0f;			// Diameter of the ship
const float BULLETSPEED = 2000.0f;

//////////////////////////////////////////////////////
//////////////EnemyShip////////////////////////////////
//////////////////////////////////////////////////////

void EnemyShip::Initialise(Vector2D startPosition, Spaceship *player, City *city)
{
  m_friction = 1.5f;
  m_acceleration = 4000.0f;
  m_velocity.set(0, 0);
  m_shootDelay = 0.0f;
  m_pCity = city;

  m_pPlayer = player;
  m_drawDepth = 12;

  LoadImage(L"SpinEnemy.png");

  m_position = startPosition;

  incrementFrame = 0;

  m_imageScale = 4;
  sensorPosition = (m_position + Vector2D(0, 2000));
  sensor.PlaceAt(m_position, sensorPosition);
}

void EnemyShip::Update(float frameTime)
{
  if (m_position.YValue < 440)
  {
    m_position += Vector2D(0, 50);
  }

  m_frameTime = frameTime;
  m_shootDelay -= m_frameTime;

  if (m_position.XValue < m_pPlayer->GetPosition().XValue - 3000)
  {
    Deactivate();
  }

  m_imageNumber = 0;

  Vector2D playerpos = m_pPlayer->getPosition();
  Vector2D vToShip = m_position - playerpos;
  m_angle = vToShip.angle();

  if (m_shootDelay < 0)
  {
    m_shootDelay = SHOOTDELAY;				// Makes it wait before it can shoot again
    Vector2D pos;
    Vector2D vel;
    pos.setBearing(m_angle, SHIPSIZE / 2);	// Offset the starting location to the front of the ship
    pos = pos + m_position;
    vel.setBearing(m_angle, BULLETSPEED);	// Set the velocity
    vel = vel + Vector2D(m_velocity);					// Include the launching platform's velocity

    EnemyBullet* pEnemyBullet = new EnemyBullet;
    pEnemyBullet->Initialise(pos, -vel, m_angle);			// Intialise
    Game::instance.m_objects.AddItem(pEnemyBullet, true);

  }



}

IShape2D& EnemyShip::GetCollisionShape()
{
  collisionShape.PlaceAt(m_position, 70);
  return collisionShape;


}

void EnemyShip::Draw()
{

  GameObject::Draw();
  MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();
  /*pTheDrawEngine->DrawLine(sensor.GetStart(), sensor.GetEnd(), 65525);*/

}

Vector2D EnemyShip::getPosition()
{
  return m_position;
}

Vector2D EnemyShip::getInitialPosition()
{
  return initialPosition;


}

void EnemyShip::changeInitialPosition(Vector2D pos)
{
  initialPosition = pos;
}


void EnemyShip::ProcessCollision(GameObject& other)
{
  if (other.GetType() == BULLET)
  {
    m_pPlayer->addScore(5);
    m_pPlayer->incrementBombCounter();
    m_pCity->deincrementEnemyAmmount();

    Explode();
    Deactivate();

  }

}

float EnemyShip::getAngle()
{
  return m_angle;
}

float EnemyShip::getRotationToPlayer()
{
  return rotationToPlayer;
}

void EnemyShip::Explode()
{
  pSoundEngine->Play(explosion, false);

  //Deactivate();
  m_imageNumber = 1;
  Explosion* pExp = new Explosion;
  //  g_soundFX.PlayExplosion();

  pExp->Initialise(m_position, Vector2D(0, 0), 4.5f, 4.5f);

  Game::instance.m_objects.AddItem(pExp, false);



  // g_soundFX.StopThrust();			// In case it is playing
}

EnemyShip::EnemyShip() :GameObject(ENEMY)
{
}