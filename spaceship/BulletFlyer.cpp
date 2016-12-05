#include "BulletFlyer.h"
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

void BulletFlyer::Initialise(Vector2D startPosition, Spaceship *player, City *city)
{
  m_pCity = nullptr;
  m_pPlayer = nullptr;
  m_acceleration = 4000.0f;
  m_velocity.set(0, 0);
  m_shootDelay = 0.0f;

  if (m_pCity == nullptr)
  {
    m_pCity = city;

  }

  if (m_pPlayer == nullptr)
  {
    m_pPlayer = player;
  }

  m_drawDepth = 12;

  LoadImage(L"flyer.png");

  m_position = startPosition;



  m_imageScale = 4;

}

void BulletFlyer::Update(float frameTime)
{
  //stops object from going too low
  if (m_position.YValue < 440)
  {
    m_position += Vector2D(0, 50);
  }

  //makes it fly to the left
  m_position += Vector2D(-20, 0);

  m_frameTime = frameTime;
  m_shootDelay -= m_frameTime;

  //destroys the enemy if too far off screen
  if (m_position.XValue < m_pPlayer->GetPosition().XValue - 3000)
  {
    Deactivate();
  }

  m_imageNumber = 0;

  //stores players position in a vector2d
  Vector2D playerpos = m_pPlayer->getPosition();
  //Get the vector between ship
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

IShape2D& BulletFlyer::GetCollisionShape()
{
  collisionShape.PlaceAt(m_position, 70);
  return collisionShape;


}

void BulletFlyer::Draw()
{

  GameObject::Draw();
  MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();

}

Vector2D BulletFlyer::getPosition()
{
  return m_position;
}



void BulletFlyer::ProcessCollision(GameObject& other)
{
  if (other.GetType() == BULLET)
  {
    //adds score to player
    m_pPlayer->addScore(5);
    //increments counter to bombs
    m_pPlayer->incrementBombCounter();
    //deincrements the enemy ammount
    m_pCity->deincrementEnemyAmmount();

    Explode();
    Deactivate();

  }

}

float BulletFlyer::getAngle()
{
  return m_angle;
}


void BulletFlyer::Explode()
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

BulletFlyer::BulletFlyer() :GameObject(ENEMY)
{
}