#include "entities.h"
#include "gamecode.h"
#include "myinputs.h"
#include "BuildingForeground.h"
#include "BuildingBackground.h"
#include "Explosion.h"

const float BULLETSPEED = 800.0f;
const float TURNSPEED = 3.0f;     // Radians per second
const float ACCELERATION = 1600.0f; // Units per second^2
const float FRICTION = 1.5f;    // Fraction of speed to lose per deltaT
const float SHOOTDELAY = 0.5f;	// Time between each spaceship bullet
const float BASEASTEROIDSIZE = 100.0f;	// Diameter of the basic asteroid
const float SHIPSIZE = 64.0f;			// Diameter of the ship
const Vector2D GRAVITY = Vector2D(0.0f, 400.0f);








///////////////////////////////////////////////////
//===============City================================
///////////////////////////////////////////////////

void City::Initialise(Spaceship *player)
{
  //LoadImage(L"BG.png");
  m_pPlayer = player;
  m_imageScale = 9;
  lastIndex = -(NUMBER_OF_BUILDINGS / 2); //Make last index equal the first value at first
  userInterface* puserInterface = new userInterface;
  puserInterface->Intialise(m_pPlayer);
  furthestLeft = -(NUMBER_OF_BUILDINGS / 2);
  Game::instance.m_objects.AddItem(puserInterface, true);


  for (int i = -(NUMBER_OF_BUILDINGS / 2); i < (NUMBER_OF_BUILDINGS / 2); i++)
  {
    m_pBuildings[i] = new Building;
    m_pBuildings[i]->Initialise(Vector2D(i * 300, -470), m_pPlayer);    
    Game::instance.m_objects.AddItem(m_pBuildings[i], false);

    if (m_pBuildings[lastIndex]->getPosition().XValue <= m_pBuildings[i]->getPosition().XValue) //If the last indexed building is further left than current building
    {
      
      furthestLeft = furthestLeft; //Then the last index building is further left
    }

    else
    {
      furthestLeft = i; //Then the furthest left is current building

    }
    

    lastIndex = i; //The last index is set to current loop
  }

   
  for (int i = -(NUMBER_OF_BUILDINGS / 2); i < (NUMBER_OF_BUILDINGS / 2); i++)
  {
    BuildingForeground* pBuildingForeground = new BuildingForeground;
    pBuildingForeground->Initialise(Vector2D(i * 1000, -470), m_pPlayer);

    Game::instance.m_objects.AddItem(pBuildingForeground, false);
  }

  for (int i = -(NUMBER_OF_BUILDINGS / 2); i < (NUMBER_OF_BUILDINGS / 2); i++)
  {
    BuildingBackground* pBuildingBackground = new BuildingBackground;
    pBuildingBackground->Initialise(Vector2D(i * 4000, 0), m_pPlayer);

    Game::instance.m_objects.AddItem(pBuildingBackground, false);
  }


}


void City::Update(float frameTime)
{
  //shipXValue = global.shipPosition.XValue;
  //fship = global.shipPosition.XValue;
  //global.value[0] = shipXValue;

  //if (shipXValue % 30 == 0)
  //{
  //  Building* pBuilding = new Building;
  //  pBuilding->Initialise(Vector2D(shipXValue+1600, -470));

  //  Game::instance.m_objects.AddItem(pBuilding, false);
  //}
  //lastIndex = -10;
  //for (int i = -(NUMBER_OF_BUILDINGS / 2); i < (NUMBER_OF_BUILDINGS / 2); i++)
  //{
  //  if (m_pBuildings[lastIndex]->getPosition().XValue <= m_pBuildings[i]->getPosition().XValue) //If the last indexed building is further left than current building
  //  {

  //    furthestLeft = furthestLeft; //Then the last index building is further left
  //  }

  //  else
  //  {
  //    furthestLeft = i; //Then the furthest left is current building

  //  }


  //  lastIndex = i; //The last index is set to current loop
  //}
  //m_pBuildings[furthestLeft]->changePosition(Vector2D(5, 0));
  //MyDrawEngine::GetInstance()->WriteInt(700, 220, furthestLeft, MyDrawEngine::WHITE);

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

void City::addShipPosition(Vector2D pos)
{
  shipsPosition = pos;
}

City::City() :GameObject(LEVEL)
{

}





Bullet::Bullet() : GameObject(BULLET)
{

}

void Bullet::Initialise(Vector2D position, Vector2D velocity, float angl)
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
  m_angle = angl - 1.4;
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


