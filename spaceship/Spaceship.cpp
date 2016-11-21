#include "Spaceship.h"
#include "entities.h"
#include "gamecode.h"
#include "myinputs.h"
#include "Building.h"
#include "Explosion.h"
#include "missile.h"
#include "EnemyOne.h"

const int MAXBULLETS = 50;
const float BULLETSPEED = 800.0f;
const float TURNSPEED = 3.0f;     // Radians per second
const float ACCELERATION = 5000.0f; // Units per second^2
const float FRICTION = 1.5f;    // Fraction of speed to lose per deltaT
const float SHOOTDELAY = 0.25f;	// Time between each spaceship bullet
const float BASEASTEROIDSIZE = 100.0f;	// Diameter of the basic asteroid
const float SHIPSIZE = 64.0f;			// Diameter of the ship
const int FUEL = 1000;
const float RESPAWNTIME = 3.0f;
//const Vector2D GRAVITY = Vector2D(0.0f, 400.0f);

//////////////////////////////////////////////////
////////////////spaceship/////////////////////////
/////////////////////////////////////////////////
// Set the object's type
Spaceship::Spaceship() : GameObject(SPACESHIP)
{
  m_drawDepth = 6;
}

// Starting position and load the image
void Spaceship::Initialise(Vector2D position)
{
  srand(time(NULL));

  bullets = MAXBULLETS;
  m_respawnTime = RESPAWNTIME;
  m_respawnCounting = false;
  m_friction = 1.5f;
  isLanded = false;
  m_position = position;
  m_shootDelay = 0.0f;
  m_angle = 0.0f;
  m_velocity.set(0, 0);
  m_objectSize = Vector2D(256, 256)*m_imageScale;
  m_acceleration = 5000.0f;
  LoadImage(L"ship.png");
  LoadImage(L"invisible.bmp");
  //m_imageScale = SHIPSIZE / 16;	// 64 pixel image file
  m_fuel = FUEL;
  m_lives = 3;
}


void Spaceship::Update(float frametime)
{

    
  m_frameTime = frametime;
 
  m_position.XValue;

  //explode
  if (m_respawnCounting == true)
  {
    gravity = Vector2D(0.0f, 0.0f);
    m_position = m_position;
    m_respawnTime -= m_frameTime;
  }

  //respawning
  if (m_respawnTime < 0)
  {
    gravity = Vector2D(0.0f, 1000.0f);
    m_imageNumber = 0;
    m_respawnTime = RESPAWNTIME;
    m_position = Vector2D(m_position.XValue - 600, 400);
    m_fuel = FUEL;
    m_respawnCounting = false;
  }

  // Get input and set acceleration
  MyInputs* pInputs = MyInputs::GetInstance();
  pInputs->SampleKeyboard();
  //global.shipAngle = m_angle;
  thrustChange();
  if (m_fuel > 0 && !m_respawnCounting)
  {
    if (pInputs->KeyPressed(DIK_LEFT))  // Turn left
    {
      m_angle -= TURNSPEED *frametime;
    }
    if (pInputs->KeyPressed(DIK_RIGHT)) // Turn right
    {
      m_angle += TURNSPEED *frametime;
    }
    if (pInputs->KeyPressed(DIK_UP) && m_position.YValue < 1200)    // Thrust
    {
      isLanded = false;
      if (!m_thrusting)		// If not thrusting last frame
      {
        // g_soundFX.StartThrust();	// Start the thrust sound
      }
      m_thrusting = true;			// Remember we are thrusting
      Vector2D acc;
      acc.setBearing(m_angle, m_acceleration);
      m_velocity = m_velocity + acc*frametime;
      m_fuel--;
      

      // Add a fire trail for thrust effect
      Explosion* pExp = new Explosion;
      Vector2D flameDirection;      // The flames move
      flameDirection.setBearing(m_angle + 3.141f, 600);  // Out of the back of the ship
      pExp->Initialise(m_position, flameDirection, 68.0f, 1.0f);
      Game::instance.m_objects.AddItem(pExp, false);		// Add to the engine


    }
    else	// Not thrusting
    {
      if (m_thrusting)		// If  thrusting last frame
      {
        //g_soundFX.StopThrust();	// Stop the thrust sound
      }
      m_acceleration = 2000;
      m_thrusting = false;			// Remember we are thrusting
    }

    // Handle shooting
    if (pInputs->KeyPressed(DIK_SPACE) && m_shootDelay<0 && bullets > 0)    // Shoot
    {
      bullets--;
      m_shootDelay = SHOOTDELAY;				// Makes it wait before it can shoot again
      Vector2D pos;
      Vector2D vel;
      pos.setBearing(m_angle, SHIPSIZE / 2);	// Offset the starting location to the front of the ship
      pos = pos + m_position;
      vel.setBearing(m_angle, BULLETSPEED);	// Set the velocity
      vel = vel + m_velocity;					// Include the launching platform's velocity

      Bullet* pBullet = new Bullet;
      pBullet->Initialise(pos, vel, m_angle);			// Intialise
      Game::instance.m_objects.AddItem(pBullet, true);	// Add to the engine
      //g_soundFX.PlayZap();					// PLay zap sound effect
    }
    m_shootDelay -= frametime;					// Cool down the gun so it can shoot again.




  }

  //for landing

  if (!isLanded)
  {
    m_velocity = m_velocity - gravity *frametime;
    
  }
  else
  {
    RotateTo(0);
  }

  // Process movement
  m_velocity = m_velocity - m_friction*frametime*m_velocity;
  m_position = m_position + m_velocity*frametime;

  MyDrawEngine::GetInstance()->theCamera.PlaceAt(Vector2D(m_position.XValue - 300,0 - m_position.YValue + 20));




}

void Spaceship::Draw()
{
  GameObject::Draw();
  //MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();
  //pTheDrawEngine->FillCircle(m_position, collisionShape.GetRadius(), 65525);

}

IShape2D& Spaceship::GetCollisionShape()
{
  // Place at the centre of the ship and slightly smaller than the image
  collisionShape.PlaceAt(m_position, 70);
  return collisionShape;
}

void Spaceship::ProcessCollision(GameObject& other)
{
  if (other.GetType() == LANDER && !m_respawnCounting)
  {
    Lander *pOtherBuilding = dynamic_cast<Lander*> (&other);

    if (pOtherBuilding->getCollisionReaction() == CollisionType::BOUNCE)
    {

      if (m_acceleration >= 3000)
      {
        Explode();
      }
      else
      {//bounce
        Bounce(other);
      }


      //m_velocity = Vector2D(0.0f, 0.0f);
      //m_angle = 0;
    }

    if (pOtherBuilding->getCollisionReaction() == CollisionType::LANDER &&!m_respawnCounting)
    {
      if (m_acceleration >= 3000)
      {
        Explode();
      }
      else
      {
        Land(other);
      }
      m_velocity = Vector2D(0.0f, 0.0f);
      
    }

  }
  //m_fuel--;
  //HitObject(other);




  if (other.GetType() == BULLET)
  {
    m_health--;
  }

  if (other.GetType() == FLOOR && !m_respawnCounting)
  {
    if (m_acceleration >= 3000)
    {
      Explode();
    }

    else
    {
      isLanded = true;


      m_position.YValue = other.GetPosition().YValue - 1020;
    }

    m_velocity = Vector2D(0.0f, 0.0f);
    m_angle = 0;
    
  }
  //if (other.GetType() == ASTEROID)
  //  Explode();
}

void Spaceship::Explode()
{
  //Deactivate();
  m_imageNumber = 1;
  Explosion* pExp = new Explosion;
  //  g_soundFX.PlayExplosion();

  pExp->Initialise(m_position, Vector2D(0, 0), 4.5f, 4.5f);

  Game::instance.m_objects.AddItem(pExp, false);

  m_respawnCounting = true;

  // g_soundFX.StopThrust();			// In case it is playing
}

void Spaceship::Bounce(GameObject &other)
{
  Lander *pOtherBuildingTwo = dynamic_cast<Lander*> (&other);

  Vector2D normal = collisionShape.CollisionNormal(pOtherBuildingTwo->GetShape());
  normal = normal.unitVector();



  m_velocity = m_velocity - (2*normal*m_velocity)*normal;
  m_health--;


  //m_position = m_position + m_velocity*globalframetime;
  //m_position = m_position - GRAVITY *globalframetime;


}

void Spaceship::Land(GameObject &other)
{
  Lander *pOtherLander = dynamic_cast<Lander*> (&other);
  if (pOtherLander->GetColType() == 1)
  {
    m_fuel = FUEL;
  }

  //landing collision
  isLanded = true;
  

  m_position.YValue = other.GetPosition().YValue + 100;


}

float Spaceship::getFuel()
{
  return m_fuel;
}

float Spaceship::getAngle()
{
  return m_angle;
}

float Spaceship::getAcceleration()
{
  return m_acceleration;
}

Vector2D Spaceship::getVelocity()
{
  return m_velocity;
}

Vector2D& Spaceship::getPosition()
{
  return m_position;
}

int Spaceship::getMaxBullets()
{
  return MAXBULLETS;
}

int Spaceship::getBullets()
{
  return bullets;
}
void Spaceship::fuelManagement()
{


}

void Spaceship::thrustChange()
{
  if (!m_thrusting || isLanded)
  {
    thrustTime = 0;
  }
  else
  {
    thrustTime++;
  }

  if (thrustTime < 10)
  {
    m_acceleration = 5000.0f;
  }

  if (thrustTime > 10)
  {
    m_acceleration = 2000.0f;
  }

  if (thrustTime > 200)
  {
    m_acceleration = 1000.0f * (thrustTime / 100);
  }

  if (thrustTime > 500)
  {
    m_acceleration = 5000.0f;
  }

}

void Spaceship::RotateTo(float angle)
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