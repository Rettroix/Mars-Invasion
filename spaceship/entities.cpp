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
Vector2D shipPosition;

//////////////////////////////////////////////////////
//////////////building////////////////////////////////
//////////////////////////////////////////////////////

void Building::Initialise(Vector2D startPosition)
{
  m_drawDepth = 5;

  LoadImage(L"building.png");

  m_position = startPosition;

  incrementFrame = 0;

  m_imageScale = 2;
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

  MyDrawEngine::GetInstance()->theCamera.PlaceAt(Vector2D(m_position.XValue - 300, 0));

  // Wrap around the screen
  //const int BORDER = 16;
  //Rectangle2D screenArea = MyDrawEngine::GetInstance()->GetViewport();
  //if (m_position.XValue + BORDER < screenArea.GetTopLeft().XValue)    // Left side
  //{
  //  m_position.XValue = screenArea.GetBottomRight().XValue + BORDER;
  //}
  //if (m_position.XValue - BORDER > screenArea.GetBottomRight().XValue)    // right side
  //{
  //  m_position.XValue = screenArea.GetTopLeft().XValue - BORDER;
  //}
  //if (m_position.YValue - BORDER > screenArea.GetTopLeft().YValue)    // top
  //{
  //  m_position.YValue = screenArea.GetBottomRight().YValue - BORDER;
  //}
  //if (m_position.YValue + BORDER < screenArea.GetBottomRight().YValue)    // bottom
  //{
  //  m_position.YValue = screenArea.GetTopLeft().YValue + BORDER;
  //}
  shipPosition = m_position;
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

///////////////////////////////////////////////////
//===============City================================
///////////////////////////////////////////////////

void City::Initialise(float timeDelay)
{
  //LoadImage(L"BG.png");
  m_imageScale = 9;
  for (int i = -50; i < 50; i++)
  {
    Building* pBuilding = new Building;
    pBuilding->Initialise(Vector2D(i*300, -470));

    Game::instance.m_objects.AddItem(pBuilding, false);
  }

  for (int i = -50; i < 50; i++)
  {
    BuildingForeground* pBuildingForeground = new BuildingForeground;
    pBuildingForeground->Initialise(Vector2D(i * 1000, -470));

    Game::instance.m_objects.AddItem(pBuildingForeground, false);
  }

  for (int i = -50; i < 50; i++)
  {
    BuildingBackground* pBuildingBackground = new BuildingBackground;
    pBuildingBackground->Initialise(Vector2D(i * 4000, 0));

    Game::instance.m_objects.AddItem(pBuildingBackground, false);
  }


}


void City::Update(float frameTime)
{
  


  
}

IShape2D& City::GetCollisionShape()
{
  m_collider.PlaceAt(m_position, 96);
  return m_collider;


}


void City::ProcessCollision(GameObject& other)
{
  //nothing

}

City::City() :GameObject(LEVEL)
{

}

//////////////////////////////////////////////////////
//////////////BuildingForeground////////////////////////////////
//////////////////////////////////////////////////////

void BuildingForeground::Initialise(Vector2D startPosition)
{
  m_drawDepth = 8;

  LoadImage(L"building.png");

  m_position = startPosition;

  incrementFrame = 0;
  initialPosition = m_position;
  m_imageScale = 3;
}

void BuildingForeground::Update(float frameTime)
{
  m_imageNumber = 0;
  
  m_position = initialPosition + Vector2D(Vector2D(shipPosition).XValue*0.5, 0);
  incrementFrame+= 0.025 *frameTime;

}

IShape2D& BuildingForeground::GetCollisionShape()
{
  m_collider.PlaceAt(m_position, 96);
  return m_collider;


}


void BuildingForeground::ProcessCollision(GameObject& other)
{
  //nothing

}

BuildingForeground::BuildingForeground() :GameObject(BUILDING)
{

}

//////////////////////////////////////////////////////
//////////////BuildingBackground////////////////////////////////
//////////////////////////////////////////////////////

void BuildingBackground::Initialise(Vector2D startPosition)
{
  m_drawDepth = 1;

  LoadImage(L"city.png");

  m_position = startPosition;

  incrementFrame = 0;
  initialPosition = m_position;
  m_imageScale = 9;
}

void BuildingBackground::Update(float frameTime)
{
  m_imageNumber = 0;

  m_position = initialPosition - Vector2D(Vector2D(shipPosition).XValue*0.5, 0);
  incrementFrame += 0.025 *frameTime;

}

IShape2D& BuildingBackground::GetCollisionShape()
{
  m_collider.PlaceAt(m_position, 96);
  return m_collider;


}


void BuildingBackground::ProcessCollision(GameObject& other)
{
  //nothing

}

BuildingBackground::BuildingBackground() :GameObject(BUILDING)
{

}