#include "Spaceship.h"
#include "entities.h"
#include "gamecode.h"
#include "myinputs.h"
#include "Building.h"


const float BULLETSPEED = 800.0f;
const float TURNSPEED = 3.0f;     // Radians per second
const float ACCELERATION = 1600.0f; // Units per second^2
const float FRICTION = 1.5f;    // Fraction of speed to lose per deltaT
const float SHOOTDELAY = 0.5f;	// Time between each spaceship bullet
const float BASEASTEROIDSIZE = 100.0f;	// Diameter of the basic asteroid
const float SHIPSIZE = 64.0f;			// Diameter of the ship
const Vector2D GRAVITY = Vector2D(0.0f, 400.0f);

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
  m_position = position;
  m_shootDelay = 0.0f;
  m_angle = 0.0f;
  m_velocity.set(0, 0);
  LoadImage(L"ship.png");
  m_imageScale = SHIPSIZE / 16;	// 64 pixel image file
  m_fuel = 1600;
}


void Spaceship::Update(float frametime)
{


  // Get input and set acceleration
  MyInputs* pInputs = MyInputs::GetInstance();
  pInputs->SampleKeyboard();
  //global.shipAngle = m_angle;
  if (m_fuel > 0)
  {
    if (pInputs->KeyPressed(DIK_LEFT))  // Turn left
    {
      m_angle -= TURNSPEED *frametime;
    }
    if (pInputs->KeyPressed(DIK_RIGHT)) // Turn right
    {
      m_angle += TURNSPEED *frametime;
    }
    if (pInputs->KeyPressed(DIK_UP))    // Thrust
    {
      if (!m_thrusting)		// If not thrusting last frame
      {
        // g_soundFX.StartThrust();	// Start the thrust sound
      }
      m_thrusting = true;			// Remember we are thrusting
      Vector2D acc;
      acc.setBearing(m_angle, ACCELERATION);
      m_velocity = m_velocity + acc*frametime;
      m_fuel--;
      //global.fuel = m_fuel;

      // Add a fire trail for thrust effect
      Explosion* pExp = new Explosion;
      Vector2D flameDirection;      // The flames move
      flameDirection.setBearing(m_angle + 3.141f, 600);  // Out of the back of the ship
      pExp->Initialise(m_position, flameDirection, 68.0f, 2.0f);
      Game::instance.m_objects.AddItem(pExp, false);		// Add to the engine


    }
    else	// Not thrusting
    {
      if (m_thrusting)		// If  thrusting last frame
      {
        //g_soundFX.StopThrust();	// Stop the thrust sound
      }
      m_thrusting = false;			// Remember we are thrusting
    }

    // Handle shooting
    if (pInputs->KeyPressed(DIK_SPACE) && m_shootDelay<0)    // Shoot
    {
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
  // Process movement
  m_velocity = m_velocity - FRICTION*frametime*m_velocity;
  m_position = m_position + m_velocity*frametime;

  MyDrawEngine::GetInstance()->theCamera.PlaceAt(Vector2D(m_position.XValue - 300, 0));


  //global.shipPosition = m_position;
  m_position = m_position - GRAVITY *frametime;


}

IShape2D& Spaceship::GetCollisionShape()
{
  // Place at the centre of the ship and slightly smaller than the image
  m_collider.PlaceAt(m_position, SHIPSIZE / 2 - 2);
  return m_collider;
}

void Spaceship::ProcessCollision(GameObject& other)
{
  //if (other.GetType() == ASTEROID)
  //  Explode();
}

void Spaceship::Explode()
{
  Deactivate();
  //  Explosion* pExp = new Explosion;
  //  g_soundFX.PlayExplosion();

  // pExp->Initialise(m_position, Vector2D(0, 0), 4.5f, 4.5f);

  //  Game::instance.m_objects.AddItem(pExp, false);

  // g_soundFX.StopThrust();			// In case it is playing
}

float Spaceship::getFuel()
{
  return m_fuel;
}

float Spaceship::getAngle()
{
  return m_angle;
}

Vector2D& Spaceship::getPosition()
{
  return m_position;
}

void Spaceship::fuelManagement()
{


}