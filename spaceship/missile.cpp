//Title     : Missile.cpp
//Purpose   : Missile is a sensor which spins around and
//            follows the player when they are in sight
//Author    : Elliot Anderson
//Date      : 5/12/16

#include "missile.h"
#include "Explosion.h"
#include "gamecode.h"


//////////////////////////////////////////////////////
//////////////missile////////////////////////////////
//////////////////////////////////////////////////////

void Missile::Initialise(Vector2D startPosition, Spaceship *player, City *city)
{
  //set pointers to null pointer
  m_pCity = nullptr;
  m_pPlayer = nullptr;

  //set friction
  m_friction = 1.5f;
  //set acceleration
  m_acceleration = 4000.0f;
  //set velocity
  m_velocity.set(0, 0);

  //set city pointer
  if (m_pCity == nullptr)
  {
    m_pCity = city;
  }
  //set player pointer
  if (m_pPlayer == nullptr)
  {
    m_pPlayer = player;
  }
  //set draw depth
  m_drawDepth = 12;

  //load image
  LoadImage(L"enemy_missile.png");

  //the position becomes the start position
  m_position = startPosition;

  
  m_imageScale = 4;
  //set the end position of the sensor
  sensorPosition = (m_position + Vector2D(0, 2000));
  //Places the sensor as a segment with start at the ship and further up
  sensor.PlaceAt(m_position,sensorPosition);
}

void Missile::Update(float frameTime)
{
  m_frameTime = frameTime;


  //if the enemy is too far off screen then destroy the player
  //and deincrement enemy ammount
  if (m_position.XValue < m_pPlayer->GetPosition().XValue - 3000)
  {
    m_pCity->deincrementEnemyAmmount();

    Deactivate();
  }
  
  m_imageNumber = 0;
  //Set's the bearing of the sensor position to facing out the front
  sensorPosition.setBearing(m_angle, -m_angle*10);
  //place the sensor at the missile
  sensor.PlaceAt(m_position, sensorPosition);
  //if the sensor is not intersecting with the player
  //make the sensor spin
  if (!sensor.Intersects(m_pPlayer->GetCollisionShape()))
  {
    m_angle -= 8000*m_frameTime;
  }
 
  //if the sensor is intersecting with the player
  //then move the missile foward towards the player
  if (sensor.Intersects(m_pPlayer->GetCollisionShape()))
  {
    Vector2D acc;
    acc.setBearing(m_angle, m_acceleration);
    m_velocity = m_velocity + acc*m_frameTime;

    rotationToPlayer = m_angle;


  }
  
  //process the movement
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



void Missile::ProcessCollision(GameObject& other)
{
  if (other.GetType() == BULLET)
  {
    m_pPlayer->addScore(10);
    m_pPlayer->incrementBombCounter();
    m_pCity->deincrementEnemyAmmount();
    Explode();
    Deactivate();

  }

  if (other.GetType() == LANDER || other.GetType() == COLLIDER)
  {
    m_pCity->deincrementEnemyAmmount();
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
  pSoundEngine->Play(explosion, false);
  m_imageNumber = 1;
  Explosion* pExp = new Explosion;

  pExp->Initialise(m_position, Vector2D(0, 0), 4.5f, 4.5f);

  Game::instance.m_objects.AddItem(pExp, false);

  

}

Missile::Missile() :GameObject(ENEMY)
{
}