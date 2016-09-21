#include "entities.h"
#include "gamecode.h"
#include "myinputs.h"

const float BULLETSPEED = 800.0f;
const float TURNSPEED = 3.0f;     // Radians per second
const float ACCELERATION = 1600.0f; // Units per second^2
const float FRICTION = 1.5f;    // Fraction of speed to lose per deltaT
const float SHOOTDELAY = 0.5f;	// Time between each spaceship bullet
const float BASEASTEROIDSIZE = 100.0f;	// Diameter of the basic asteroid
const float SHIPSIZE = 64.0f;			// Diameter of the ship

//////////////////////////////////////////////////////
//////////////building////////////////////////////////
//////////////////////////////////////////////////////

void Building::Intialise(Vector2D startPosition, Vector2D startVelocity, float timeDelay)
{
  m_drawDepth = 5;

  LoadImage(L"building.png");

  m_position = Vector2D(0, 500);

  incrementFrame = 0;
}

void Building::Update(float frameTime)
{
  m_imageNumber = 0;



}

IShape2D& Building::GetCollisionShape()
{
  m_collider.PlaceAt(m_position, 96);
  return m_collider;


}


void Building::ProcessCollision(GameObject& other)
{
  //nothing

}

Building::Building() :GameObject(BUILDING)
{

}

//////////////////////////////////////////////////
////////////////spaceship/////////////////////////
/////////////////////////////////////////////////
// Set the object's type
Spaceship::Spaceship() : GameObject(SPACESHIP)
{

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
}


void Spaceship::Update(float frametime)
{


  // Get input and set acceleration
  MyInputs* pInputs = MyInputs::GetInstance();
  pInputs->SampleKeyboard();

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

    // Add a fire trail for thrust effect
   // Explosion* pExp = new Explosion;
  //  Vector2D flameDirection;      // The flames move
    //flameDirection.setBearing(m_angle + 3.141f, 600);  // Out of the back of the ship
    //pExp->Initialise(m_position, flameDirection, 68.0f, 0.3f);
 //   Game::instance.m_objects.AddItem(pExp, false);		// Add to the engine
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
    //Bullet* pBullet = new Bullet;
    //pBullet->Initialise(pos, vel);			// Intialise
    //Game::instance.m_objects.AddItem(pBullet, true);	// Add to the engine
    //g_soundFX.PlayZap();					// PLay zap sound effect
  }
  m_shootDelay -= frametime;					// Cool down the gun so it can shoot again.


  // Process movement
  m_velocity = m_velocity - FRICTION*frametime*m_velocity;
  m_position = m_position + m_velocity*frametime;

  // Wrap around the screen
  const int BORDER = 16;
  Rectangle2D screenArea = MyDrawEngine::GetInstance()->GetViewport();
  if (m_position.XValue + BORDER < screenArea.GetTopLeft().XValue)    // Left side
  {
    m_position.XValue = screenArea.GetBottomRight().XValue + BORDER;
  }
  if (m_position.XValue - BORDER > screenArea.GetBottomRight().XValue)    // right side
  {
    m_position.XValue = screenArea.GetTopLeft().XValue - BORDER;
  }
  if (m_position.YValue - BORDER > screenArea.GetTopLeft().YValue)    // top
  {
    m_position.YValue = screenArea.GetBottomRight().YValue - BORDER;
  }
  if (m_position.YValue + BORDER < screenArea.GetBottomRight().YValue)    // bottom
  {
    m_position.YValue = screenArea.GetTopLeft().YValue + BORDER;
  }

}

IShape2D& Spaceship::GetCollisionShape()
{
  // Place at the centre of the ship and slightly smaller than the image
  m_collider.PlaceAt(m_position, SHIPSIZE / 2 - 2);
  return m_collider;
}

void Spaceship::ProcessCollision(GameObject& other)
{
 // if (other.GetType() == ASTEROID)
 //   Explode();
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
