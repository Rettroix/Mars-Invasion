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
  srand(time(NULL));
  //LoadImage(L"BG.png");
  m_pPlayer = player;
  m_imageScale = 9;
  lastIndex = 0; //Make last index equal the first value at first
  userInterface* puserInterface = new userInterface;
  puserInterface->Intialise(m_pPlayer);
  furthestLeft = 0;
  Game::instance.m_objects.AddItem(puserInterface, true);

  
  for (int i = -(NUMBER_OF_BUILDINGS / 2); i < (NUMBER_OF_BUILDINGS / 2); i++)
  {
    selectedBuilding = static_cast<BuildingType>(rand() % 6 +1);

    m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)] = new Building;
    m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(Vector2D(i * 700, -470), selectedBuilding);
    Game::instance.m_objects.AddItem(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], true);

    if (m_pBuildings[lastIndex]->getPosition().XValue <= m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->getPosition().XValue) //If the last indexed building is further left than current building
    {
      if (m_pBuildings[lastIndex]->getPosition().XValue <= m_pBuildings[furthestLeft]->getPosition().XValue)
      {
        furthestLeft = lastIndex; //Then the last index building is further left
      }
      else
      {
        furthestLeft = furthestLeft;
      }

    }

    else
    {
      furthestLeft = i + (NUMBER_OF_BUILDINGS / 2); //Then the furthest left is current building

    }

    if (furthestLeft == 0)
    {
      furthestRight = 20;
    }

    else
    {
      furthestRight = furthestLeft - 1;
    }


    lastIndex = i + (NUMBER_OF_BUILDINGS / 2); //The last index is set to current loop
  }

   
  //for (int i = -(NUMBER_OF_BUILDINGS / 2); i < (NUMBER_OF_BUILDINGS/2); i++)  
  //{
  //  m_pForegroundBuildings[i + (NUMBER_OF_BUILDINGS / 2)] = new BuildingForeground;
  //  m_pForegroundBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(Vector2D(i * 4000, -470), m_pPlayer);

  //  Game::instance.m_objects.AddItem(m_pForegroundBuildings[i + (NUMBER_OF_BUILDINGS / 2)], false);
  //}


  for (int i = -(NUMBER_OF_BUILDINGS / 2); i < (NUMBER_OF_BUILDINGS / 2); i++)
  {
    m_pBackgroundBuildings[i + (NUMBER_OF_BUILDINGS/2)] = new BuildingBackground;
    m_pBackgroundBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(Vector2D(i * 4000, 0), m_pPlayer);

    Game::instance.m_objects.AddItem(m_pBackgroundBuildings[i + (NUMBER_OF_BUILDINGS / 2)], false);
  }


}


void City::Update(float frameTime)
{
  //shipXValue = global.shipPosition.XValue;
  //fship = global.shipPosition.XValue;
  //global.value[0] = shipXValue;


  lastIndex = 0;
  furthestLeft = 0;
  
  for (int i = -(NUMBER_OF_BUILDINGS / 2); i < (NUMBER_OF_BUILDINGS / 2); i++)
  {

    if (m_pBuildings[lastIndex]->getPosition().XValue < m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->getPosition().XValue) //If the last indexed building is further left than current building
    {
      if (m_pBuildings[lastIndex]->getPosition().XValue <= m_pBuildings[furthestLeft]->getPosition().XValue)
      {
        furthestLeft = lastIndex; //Then the last index building is further left
      }
      else
      {
        furthestLeft = furthestLeft;
      }
      
    }

    else
    {
      furthestLeft = i + (NUMBER_OF_BUILDINGS / 2); //Then the furthest left is current building

    }


    lastIndex = i + (NUMBER_OF_BUILDINGS / 2); //The last index is set to current loop

  }
  if (furthestLeft == 0)
  {
    furthestRight = 19;
    
  }

  else
  {
    furthestRight = furthestLeft - 1;
  }

  middle = (m_pBuildings[furthestLeft]->getPosition().XValue + m_pBuildings[furthestRight]->getPosition().XValue)/2;

  if (m_pPlayer->getPosition().XValue > middle)
  {
    m_pBuildings[furthestLeft]->changePosition(Vector2D((m_pBuildings[furthestRight]->getPosition().XValue), (m_pBuildings[furthestLeft]->getPosition().YValue)) + Vector2D(700, 0));
  }

  if (m_pPlayer->getPosition().XValue < middle)
  {
    m_pBuildings[furthestRight]->changePosition(Vector2D((m_pBuildings[furthestLeft]->getPosition().XValue), (m_pBuildings[furthestRight]->getPosition().YValue)) - Vector2D(700, 0));
  }
  
  MyDrawEngine::GetInstance()->WriteInt(700, 220, furthestLeft, MyDrawEngine::WHITE);
  

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


