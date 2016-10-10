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
const Vector2D GRAVITY = Vector2D(0.0f, 400.0f);

globalstuffs global;


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
  m_fuel = 1600;
}


void Spaceship::Update(float frametime)
{


  // Get input and set acceleration
  MyInputs* pInputs = MyInputs::GetInstance();
  pInputs->SampleKeyboard();

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
      global.fuel = m_fuel;

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
      pBullet->Initialise(pos, vel);			// Intialise
      Game::instance.m_objects.AddItem(pBullet, true);	// Add to the engine
      //g_soundFX.PlayZap();					// PLay zap sound effect
    }
    m_shootDelay -= frametime;					// Cool down the gun so it can shoot again.




  }
  // Process movement
  m_velocity = m_velocity - FRICTION*frametime*m_velocity;
  m_position = m_position + m_velocity*frametime;

  MyDrawEngine::GetInstance()->theCamera.PlaceAt(Vector2D(m_position.XValue - 300, 0));


  global.shipPosition = m_position;
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

void Spaceship::fuelManagement()
{


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

  LoadImage(L"buildingfore.png");

  m_position = startPosition;

  incrementFrame = 0;
  initialPosition = m_position;
  m_imageScale = 3;
}

void BuildingForeground::Update(float frameTime)
{
  m_imageNumber = 0;
  
  m_position = initialPosition + Vector2D(Vector2D(global.shipPosition).XValue*0.5, 0);
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
//////////////BuildingBackground//////////////////////
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

  m_position = initialPosition - Vector2D(Vector2D(global.shipPosition).XValue*0.5, 0);
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

Bullet::Bullet() : GameObject(BULLET)
{

}

void Bullet::Initialise(Vector2D position, Vector2D velocity)
{
  m_position = position;
  m_velocity = velocity;
  m_timer = 2.0;
  m_animationSpeed = 0;
  m_currentAnimation = 0.0f;
  LoadImage(L"bullet1.png");
  LoadImage(L"bullet2.png");
  LoadImage(L"bullet3.png");
  LoadImage(L"bullet4.png");
  LoadImage(L"bullet5.png");
  LoadImage(L"bullet6.png");
  m_imageScale = SHIPSIZE / 16;
  m_drawDepth = 6;
}

void Bullet::Update(float frametime)
{
  m_animationSpeed = m_animationSpeed + 0.15;
  m_timer -= frametime;
  m_position = m_position + m_velocity*frametime;

  if (m_animationSpeed >= 5)
  {
    m_animationSpeed = 5;
    m_imageNumber = 5;
  }
  else
  {
    m_imageNumber = m_animationSpeed;
  }
  
}

  IShape2D& Bullet::GetCollisionShape()
{
  m_collider = m_position;
  return m_collider;
}

void Bullet::ProcessCollision(GameObject& other)
{
  //if (other.GetType() == ASTEROID)
 // {
   // Deactivate();

    // Send message that a bullet has died
    // (The fragment class will need to know)
    //Event evt;
    //evt.position = m_position;
    //evt.pSource = this;
    //evt.type = EVENT_OBJECTDESTROYED;

    //Game::instance.NotifyEvent(evt);
  //}



}


//////////////////////////////////////////////
/////////UserInterface///////////////////////
/////////////////////////////////////////////
void userInterface::Intialise(Vector2D startPosition, Vector2D startVelocity, float timeDelay)
{
  m_drawDepth = 7;




}

void userInterface::Update(float frameTime)
{


}

IShape2D& userInterface::GetCollisionShape()
{

  return m_collider;
}

void userInterface::Draw()
{
  MyDrawEngine::GetInstance()->WriteText(200, 200, L"Fuel=", MyDrawEngine::WHITE);
  MyDrawEngine::GetInstance()->WriteInt(350, 200, global.fuel, MyDrawEngine::WHITE);

  //MyDrawEngine::GetInstance()->WriteText(700, 200, L"Lives:", MyDrawEngine::WHITE);
  //MyDrawEngine::GetInstance()->WriteInt(700, 220, lives, MyDrawEngine::WHITE);

}
void userInterface::ProcessCollision(GameObject& other)
{
  //nothing
}



userInterface::userInterface() :GameObject(UI)
{

}

//////////////////////////////////////////////
/////////Explosion///////////////////////
/////////////////////////////////////////////

Explosion::Explosion() : GameObject(EXPLOSION)
{

}

void Explosion::Initialise(Vector2D position, Vector2D velocity, float animationSpeed, float scale)
{
  m_drawDepth = 6;
  m_velocity = velocity;
  m_position = position;
  m_animationSpeed = 0;
  m_currentAnimation = 0.0f;
  m_imageScale = scale;       // Part of the superclass

  // Loading a sequence of images for animation
  LoadImage(L"explosion1.bmp");
  LoadImage(L"explosion2.bmp");
  LoadImage(L"explosion3.bmp");
  LoadImage(L"explosion4.bmp");
  LoadImage(L"explosion5.bmp");
  LoadImage(L"explosion6.bmp");
  LoadImage(L"explosion7.bmp");
  LoadImage(L"explosion8.bmp");
}

void Explosion::Update(float frametime)
{
  m_animationSpeed = m_animationSpeed + 0.6;
  
  m_position = m_position + m_velocity*frametime;

  if (m_animationSpeed >= 7)
  {
    m_animationSpeed = 7;
    m_imageNumber = 7;
  }
  else
  {
    m_imageNumber = m_animationSpeed;
  }

}

IShape2D& Explosion::GetCollisionShape()
{
  m_collider.PlaceAt(m_position, 32.0f* m_imageScale);
  return m_collider;
}

void Explosion::ProcessCollision(GameObject& other)
{
  // No-op
}