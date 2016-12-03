#include "entities.h"
#include "gamecode.h"
#include "myinputs.h"
#include "BuildingForeground.h"
#include "BuildingBackground.h"
#include "Explosion.h"
#include "missile.h"
#include "EnemyOne.h"
#include "Particles.h"
#include "EnemyShip.h"
#include "BulletFlyer.h"
#include "userInterface.h"


const float SHOOTDELAY = 0.5f;	// Time between each spaceship bullet
const float BASEASTEROIDSIZE = 100.0f;	// Diameter of the basic asteroid
const float SHIPSIZE = 64.0f;			// Diameter of the ship
const Vector2D GRAVITY = Vector2D(0.0f, 1000.0f);







///////////////////////////////////////////////////////
//===============City================================//
///////////////////////////////////////////////////////

void City::Initialise(Spaceship *player)
{
  gameStarted = true; //The Game has started
  m_musicPlaying = false; //Check if the music is playing

  if (m_musicPlaying == false) //if it's not
  {
    pSoundEngine->Play(BGM, true);  //Play Background Music
    m_musicPlaying = true;  //music is plying
  }


  enemyOneCoolDown = 0; //Sets it to 0
  enemyAmmount = 0; //There are no enemies spawned
  maxEnemyAmmount = 1; //Only one enemy allowed at once
  srand(time(NULL)); //Seeds random
  //LoadImage(L"BG.png");

  //setting buildings to nullptr
  for (int i = 0; i < NUMBER_OF_BUILDINGS; i++)
  {
     m_pBuildings[i] = nullptr;
     m_pForegroundBuildings[i] = nullptr;
     m_pBackgroundBuildings[i] = nullptr;
     pCollision[i] = nullptr;
     pCollisionTop[i] = nullptr;
     pCollisionRight[i] = nullptr;
     pFuelBox[i] = nullptr;
  }
  if (m_pPlayer == nullptr)
  {
    m_pPlayer = player; //pointer to player
  }
  m_imageScale = 9; //setting scale
  furthestLeft = 0; //set furthest left to 0
  lastIndex = 0; //set last index to 0

  //Spawn the user interface
  userInterface* puserInterface = new userInterface;
  puserInterface->Intialise(m_pPlayer, this);
  Game::instance.m_objects.AddItem(puserInterface, true);

  
  spawnBuilding(); //Spawn buildings

  spawnBG();//spawn background buildings
   
  spawnFG(); //spawn foreground buildings





}


void City::Update(float frameTime)
{
  enemyOneCoolDown -= 1; //Every frame the cool down decreases

  updateBuildings();  //Update the buildings every frame
  updateBuildingsBG(); //update the background buildings
  updateBuildingsFG();  //update the foreground buildings

  spawnEnemies(); //spawn enemies
    




  
  
}

IShape2D& City::GetCollisionShape()
{
  m_collider.PlaceAt(m_position, 96); //places collision shape
  return m_collider;


}


void City::ProcessCollision(GameObject& other)
{
  //nothing happens

}



void City::spawnBuilding()
{
  //The  for loops runs the ammount of buildings available spanning from the minus's
  for (int i = -(NUMBER_OF_BUILDINGS / 2); i < (NUMBER_OF_BUILDINGS / 2); i++) 
  {
    selectedBuilding = static_cast<BuildingType>(rand() % 6 + 1); // the selected building is chosen
                                                                  //at random


    if (selectedBuilding == BuildingType::BUILDING1)  //if selected building is building one
    {

      spawnBuildingBlock(i);

      if (pCollision[i + (NUMBER_OF_BUILDINGS / 2)] == nullptr)
      {
        //colision left side
        pCollision[i + (NUMBER_OF_BUILDINGS / 2)] = new Lander;
        pCollision[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], 260, 500, 260, -500, 0, CollisionPosition::LEFT, CollisionType::BOUNCE);
        Game::instance.m_objects.AddItem(pCollision[i + (NUMBER_OF_BUILDINGS / 2)], true);
      }


      if (pCollisionTop[i + (NUMBER_OF_BUILDINGS / 2)] == nullptr)
      {
        //colision top
        pCollisionTop[i + (NUMBER_OF_BUILDINGS / 2)] = new Lander;
        pCollisionTop[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], 260, -500, -260, -500, 0, CollisionPosition::TOP, CollisionType::LANDER);
        Game::instance.m_objects.AddItem(pCollisionTop[i + (NUMBER_OF_BUILDINGS / 2)], true);
      }


      if (pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)] == nullptr)
      {
        //colision right
        pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)] = new Lander;
        pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], -260, 500, -260, -500, 0, CollisionPosition::RIGHT, CollisionType::BOUNCE);
        Game::instance.m_objects.AddItem(pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)], true);
      }

    }
    else if (selectedBuilding == BuildingType::BUILDING2)
    {
      //building2
      m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)] = new Building;
      m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(Vector2D(i * 700 + rand() % 300, -470), selectedBuilding, m_pPlayer);
      Game::instance.m_objects.AddItem(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], false);

      //colision left side
      pCollision[i + (NUMBER_OF_BUILDINGS / 2)] = new Lander;
      pCollision[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], 260, 500, 260, -200, 0, CollisionPosition::LEFT, CollisionType::BOUNCE);
      Game::instance.m_objects.AddItem(pCollision[i + (NUMBER_OF_BUILDINGS / 2)], true);

      //colision top
      pCollisionTop[i + (NUMBER_OF_BUILDINGS / 2)] = new Lander;
      pCollisionTop[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], 260, -200, -260, -500, 0, CollisionPosition::TOP, CollisionType::BOUNCE);
      Game::instance.m_objects.AddItem(pCollisionTop[i + (NUMBER_OF_BUILDINGS / 2)], true);

      //colision right
      pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)] = new Lander;
      pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], -260, 500, -260, -500, 0, CollisionPosition::RIGHT, CollisionType::BOUNCE);
      Game::instance.m_objects.AddItem(pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)], true);


    }

    else if (selectedBuilding == BuildingType::BUILDING3)
    {
      //building3
      m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)] = new Building;
      m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(Vector2D(i * 700 + rand() % 300, -470), selectedBuilding, m_pPlayer);
      Game::instance.m_objects.AddItem(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], false);

      //colision left side
      pCollision[i + (NUMBER_OF_BUILDINGS / 2)] = new Lander;
      pCollision[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], 260, 500, 260, -230, 0, CollisionPosition::LEFT, CollisionType::BOUNCE);
      Game::instance.m_objects.AddItem(pCollision[i + (NUMBER_OF_BUILDINGS / 2)], true);

      //colision top
      pCollisionTop[i + (NUMBER_OF_BUILDINGS / 2)] = new Lander;
      pCollisionTop[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], 260, -230, -260, -230, 0, CollisionPosition::TOP, CollisionType::LANDER);
      Game::instance.m_objects.AddItem(pCollisionTop[i + (NUMBER_OF_BUILDINGS / 2)], true);

      //colision right
      pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)] = new Lander;
      pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], -260, 500, -260, -230, 0,CollisionPosition::RIGHT, CollisionType::BOUNCE);
      Game::instance.m_objects.AddItem(pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)], true);


    }

    else if (selectedBuilding == BuildingType::BUILDING4)
    {
      //building4
      m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)] = new Building;
      m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(Vector2D(i * 700 + rand() % 300, -470), selectedBuilding, m_pPlayer);
      Game::instance.m_objects.AddItem(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], false);

      //colision left side
      pCollision[i + (NUMBER_OF_BUILDINGS / 2)] = new Lander;
      pCollision[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], 260, 500, 260, -450, 0, CollisionPosition::LEFT, CollisionType::BOUNCE);
      Game::instance.m_objects.AddItem(pCollision[i + (NUMBER_OF_BUILDINGS / 2)], true);

      //colision top
      pCollisionTop[i + (NUMBER_OF_BUILDINGS / 2)] = new Lander;
      pCollisionTop[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], 260, -450, -260, -300, 0, CollisionPosition::TOP, CollisionType::LANDER);
      Game::instance.m_objects.AddItem(pCollisionTop[i + (NUMBER_OF_BUILDINGS / 2)], true);

      //colision right
      pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)] = new Lander;
      pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], -260, 500, -260, -300, 0, CollisionPosition::RIGHT, CollisionType::BOUNCE);
      Game::instance.m_objects.AddItem(pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)], true);


    }

    else if (selectedBuilding == BuildingType::HOUSE)
    {
      //HOUSE
      m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)] = new Building;
      m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(Vector2D(i * 700 + rand() % 300, -470), selectedBuilding, m_pPlayer);
      Game::instance.m_objects.AddItem(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], false);

      //colision left side
      pCollision[i + (NUMBER_OF_BUILDINGS / 2)] = new Lander;
      pCollision[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], 260, 500, 260, -100, 0, CollisionPosition::LEFT, CollisionType::BOUNCE);
      Game::instance.m_objects.AddItem(pCollision[i + (NUMBER_OF_BUILDINGS / 2)], true);

      //colision top
      pCollisionTop[i + (NUMBER_OF_BUILDINGS / 2)] = new Lander;
      pCollisionTop[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], 260, -100, -260, -100, 0, CollisionPosition::TOP, CollisionType::LANDER);
      Game::instance.m_objects.AddItem(pCollisionTop[i + (NUMBER_OF_BUILDINGS / 2)], true);

      //colision right
      pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)] = new Lander;
      pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], -260, 500, -260, -100, 0, CollisionPosition::RIGHT, CollisionType::BOUNCE);
      Game::instance.m_objects.AddItem(pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)], true);


    }

    else if (selectedBuilding == BuildingType::FUELBUILDING)
    {
      //HOUSE
      m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)] = new Building;
      m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(Vector2D(i * 700 + rand() % 300, -470), selectedBuilding, m_pPlayer);
      Game::instance.m_objects.AddItem(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], false);


      //colision left side
      pCollision[i + (NUMBER_OF_BUILDINGS / 2)] = new Lander;
      pCollision[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], 260, 500, 260, -100, 0, CollisionPosition::LEFT, CollisionType::BOUNCE);
      Game::instance.m_objects.AddItem(pCollision[i + (NUMBER_OF_BUILDINGS / 2)], true);

      //colision top
      pCollisionTop[i + (NUMBER_OF_BUILDINGS / 2)] = new Lander;
      pCollisionTop[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], 260, -100, -260, -100, 1, CollisionPosition::TOP, CollisionType::LANDER);
      Game::instance.m_objects.AddItem(pCollisionTop[i + (NUMBER_OF_BUILDINGS / 2)], true);

      //colision right
      pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)] = new Lander;
      pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], -260, 500, -260, -100, 0, CollisionPosition::RIGHT, CollisionType::BOUNCE);
      Game::instance.m_objects.AddItem(pCollisionRight[i + (NUMBER_OF_BUILDINGS / 2)], true);


    }
    else
    {
      m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)] = new Building;
      m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(Vector2D(i * 700, -470), selectedBuilding, m_pPlayer);
      Game::instance.m_objects.AddItem(m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)], true);

    }

    // If the last indexed building is further left than current building
    if (m_pBuildings[lastIndex]->getPosition().XValue <= m_pBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->getPosition().XValue) 
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

}

void City::spawnBG()
{
  for (int i = -(NUMBER_OF_BUILDINGS / 2); i < (NUMBER_OF_BUILDINGS / 2); i++)
  {
    
    
    m_pBackgroundBuildings[i + (NUMBER_OF_BUILDINGS / 2)] = new BuildingBackground;
    m_pBackgroundBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(Vector2D(i * 4000, 0), m_pPlayer);
    Game::instance.m_objects.AddItem(m_pBackgroundBuildings[i + (NUMBER_OF_BUILDINGS / 2)], true);

    


    if (m_pBackgroundBuildings[lastIndexBG]->getInitialPosition().XValue <= m_pBackgroundBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->getInitialPosition().XValue) //If the last indexed building is further left than current building
    {
      if (m_pBackgroundBuildings[lastIndexBG]->getInitialPosition().XValue <= m_pBackgroundBuildings[furthestLeftBG]->getInitialPosition().XValue)
      {
        furthestLeftBG = lastIndexBG; //Then the last index building is further left 
      }
      else
      {
        furthestLeftBG = furthestLeftBG;
      }

    }

    else
    {
      furthestLeftBG = i + (NUMBER_OF_BUILDINGS / 2); //Then the furthest left is current building

    }

    if (furthestLeftBG == 0)
    {
      furthestRightBG = 20;
    }

    else
    {
      furthestRightBG = furthestLeftBG - 1;
    }


    lastIndexBG = i + (NUMBER_OF_BUILDINGS / 2); //The last index is set to current loop
  }

}

void City::spawnFG()
{
  for (int i = -(NUMBER_OF_BUILDINGS / 2); i < (NUMBER_OF_BUILDINGS / 2); i++)
  {


    m_pForegroundBuildings[i + (NUMBER_OF_BUILDINGS / 2)] = new BuildingForeground;
    m_pForegroundBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(Vector2D(i * 4000, -470), m_pPlayer);

    Game::instance.m_objects.AddItem(m_pForegroundBuildings[i + (NUMBER_OF_BUILDINGS / 2)], true);




    if (m_pForegroundBuildings[lastIndexFG]->getInitialPosition().XValue <= m_pForegroundBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->getInitialPosition().XValue) //If the last indexed building is further left than current building
    {
      if (m_pForegroundBuildings[lastIndexFG]->getInitialPosition().XValue <= m_pForegroundBuildings[furthestLeftFG]->getInitialPosition().XValue)
      {
        furthestLeftFG = lastIndexFG; //Then the last index building is further left 
      }
      else
      {
        furthestLeftFG = furthestLeftFG;
      }

    }

    else
    {
      furthestLeftFG = i + (NUMBER_OF_BUILDINGS / 2); //Then the furthest left is current building

    }

    if (furthestLeftFG == 0)
    {
      furthestRightFG = 20;
    }

    else
    {
      furthestRightFG = furthestLeftFG - 1;
    }


    lastIndexFG = i + (NUMBER_OF_BUILDINGS / 2); //The last index is set to current loop
  }

}

void City::updateBuildings()
{
  selectedBuilding = static_cast<BuildingType>(rand() % 6 + 1);
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

  middle = (m_pBuildings[furthestLeft]->getPosition().XValue + m_pBuildings[furthestRight]->getPosition().XValue) / 2;

  //if time is ready furthest left building changes


  if (m_pPlayer->getPosition().XValue > middle)
  {
    m_pBuildings[furthestLeft]->changePosition(Vector2D((m_pBuildings[furthestRight]->getPosition().XValue + rand()%300), (m_pBuildings[furthestLeft]->getPosition().YValue)) + Vector2D(700, 0));
    //m_pBuildings[furthestLeft]->changeBuilding(selectedBuilding);
  }

  if (m_pPlayer->getPosition().XValue < middle)
  {
    m_pBuildings[furthestRight]->changePosition(Vector2D((m_pBuildings[furthestLeft]->getPosition().XValue + rand() % 300), (m_pBuildings[furthestRight]->getPosition().YValue)) - Vector2D(700, 0));
    m_pBuildings[furthestRight]->changeBuilding(selectedBuilding);
  }




  MyDrawEngine::GetInstance()->WriteInt(700, 220, furthestLeft, MyDrawEngine::WHITE);

}


void City::updateBuildingsBG()
{
  lastIndexBG = 0;
  furthestLeftBG = 0;

  for (int i = -(NUMBER_OF_BUILDINGS / 2); i < (NUMBER_OF_BUILDINGS / 2); i++)
  {

    if (m_pBackgroundBuildings[lastIndexBG]->getInitialPosition().XValue < m_pBackgroundBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->getInitialPosition().XValue) //If the last indexed building is further left than current building
    {
      if (m_pBackgroundBuildings[lastIndexBG]->getInitialPosition().XValue <= m_pBackgroundBuildings[furthestLeftBG]->getInitialPosition().XValue)
      {
        furthestLeftBG = lastIndexBG; //Then the last index building is further left
      }
      else
      {
        furthestLeftBG = furthestLeftBG;
      }

    }

    else
    {
      furthestLeftBG = i + (NUMBER_OF_BUILDINGS / 2); //Then the furthest left is current building

    }


    lastIndexBG = i + (NUMBER_OF_BUILDINGS / 2); //The last index is set to current loop

  }
  if (furthestLeftBG == 0)
  {
    furthestRightBG = 19;

  }

  else
  {
    furthestRightBG = furthestLeftBG - 1;
  }

  middleBG = (m_pBackgroundBuildings[furthestLeftBG]->getPosition().XValue + m_pBackgroundBuildings[furthestRightBG]->getPosition().XValue) / 2;

  if (m_pPlayer->getPosition().XValue > middleBG)
  {
    m_pBackgroundBuildings[furthestLeftBG]->changeInitialPosition(Vector2D((m_pBackgroundBuildings[furthestRightBG]->getInitialPosition().XValue), (m_pBackgroundBuildings[furthestLeftBG]->getInitialPosition().YValue)) + Vector2D(4000, 0));
  }

  if (m_pPlayer->getPosition().XValue < middleBG)
  {
    m_pBackgroundBuildings[furthestRightBG]->changeInitialPosition(Vector2D((m_pBackgroundBuildings[furthestLeftBG]->getInitialPosition().XValue), (m_pBackgroundBuildings[furthestRightBG]->getInitialPosition().YValue)) - Vector2D(4000, 0));
  }


}


void City::updateBuildingsFG()
{
  lastIndexFG = 0;
  furthestLeftFG = 0;

  for (int i = -(NUMBER_OF_BUILDINGS / 2); i < (NUMBER_OF_BUILDINGS / 2); i++)
  {

    if (m_pForegroundBuildings[lastIndexFG]->getInitialPosition().XValue < m_pForegroundBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->getInitialPosition().XValue) //If the last indexed building is further left than current building
    {
      if (m_pForegroundBuildings[lastIndexFG]->getInitialPosition().XValue <= m_pForegroundBuildings[furthestLeftFG]->getInitialPosition().XValue)
      {
        furthestLeftFG = lastIndexFG; //Then the last index building is further left
      }
      else
      {
        furthestLeftBG = furthestLeftBG;
      }

    }

    else
    {
      furthestLeftFG = i + (NUMBER_OF_BUILDINGS / 2); //Then the furthest left is current building

    }


    lastIndexFG = i + (NUMBER_OF_BUILDINGS / 2); //The last index is set to current loop

  }
  if (furthestLeftFG == 0)
  {
    furthestRightFG = 19;

  }

  else
  {
    furthestRightFG = furthestLeftFG - 1;
  }

  middleFG = (m_pForegroundBuildings[furthestLeftFG]->getPosition().XValue + m_pForegroundBuildings[furthestRightFG]->getPosition().XValue) / 2;

  if (m_pPlayer->getPosition().XValue > middleFG)
  {
    m_pForegroundBuildings[furthestLeftFG]->changeInitialPosition(Vector2D((m_pForegroundBuildings[furthestRightFG]->getInitialPosition().XValue), (m_pForegroundBuildings[furthestLeftFG]->getInitialPosition().YValue)) + Vector2D(4000, 0));
  }

  if (m_pPlayer->getPosition().XValue < middleFG)
  {
    m_pForegroundBuildings[furthestRightFG]->changeInitialPosition(Vector2D((m_pForegroundBuildings[furthestLeftFG]->getInitialPosition().XValue), (m_pForegroundBuildings[furthestRightFG]->getInitialPosition().YValue)) - Vector2D(4000, 0));
  }


}

void City::spawnEnemies()
{
  if (MyDrawEngine::GetInstance()->theCamera.returnPosition().XValue < 11200)
  {
    maxEnemyAmmount = 1;

  }
  else if (MyDrawEngine::GetInstance()->theCamera.returnPosition().XValue < 12000)
  {
    maxEnemyAmmount = 3;
  }

  else if (MyDrawEngine::GetInstance()->theCamera.returnPosition().XValue < 12500)
  {
    maxEnemyAmmount = 6;
  }

  else if (MyDrawEngine::GetInstance()->theCamera.returnPosition().XValue < 20000)
  {
    maxEnemyAmmount = 20;
  }

  if (enemyOneCoolDown < 0 && rand() % 100 == 7 && enemyAmmount < maxEnemyAmmount)
  {
    int chooseEnemy;
    chooseEnemy = rand() % 3;
    enemyAmmount++;
    enemyOneCoolDown = 100;
    if (chooseEnemy == 0)
    {
      Missile* pMissile = new Missile;
      pMissile->Initialise(m_pPlayer->GetPosition() + Vector2D(2000, 0), m_pPlayer, this);
      Game::instance.m_objects.AddItem(pMissile, true);

      EnemyOne* pEnemyOne = new EnemyOne;
      pEnemyOne->Initialise(m_pPlayer->GetPosition() + Vector2D(2000, 0), m_pPlayer, pMissile);
      Game::instance.m_objects.AddItem(pEnemyOne, true);

    }

    else if (chooseEnemy == 1)
    {
      EnemyShip* pEnemyShip = new EnemyShip;
      pEnemyShip->Initialise(m_pPlayer->GetPosition() + Vector2D(2000, rand() % 1000), m_pPlayer, this);
      Game::instance.m_objects.AddItem(pEnemyShip, true);

    }

    else if (chooseEnemy == 2)
    {
      BulletFlyer* pBulletFlyer = new BulletFlyer;
      pBulletFlyer->Initialise(m_pPlayer->GetPosition() + Vector2D(2000, 0), m_pPlayer, this);
      Game::instance.m_objects.AddItem(pBulletFlyer, true);

    }
  }
}

void City::spawnBuildingBlock(int interation)
{
  if (m_pBuildings[interation + (NUMBER_OF_BUILDINGS / 2)] == nullptr) //if it's null pointer
  {
    m_pBuildings[interation + (NUMBER_OF_BUILDINGS / 2)] = new Building; //set building to building 
    //initialise with random start position, it's building type and a pointer to the player
    m_pBuildings[interation + (NUMBER_OF_BUILDINGS / 2)]->Initialise(Vector2D(interation * 700 + rand() % 300, -470), selectedBuilding, m_pPlayer);

    Game::instance.m_objects.AddItem(m_pBuildings[interation + (NUMBER_OF_BUILDINGS / 2)], false);
  }
}

void City::spawnCollisionBlockLeft()
{

}
void City::spawnCollisionBlockRight()
{

}
void City::spawnCollisionBlockTop()
{

}
void City::deincrementEnemyAmmount()
{
  enemyAmmount--;
}

int City::getMiddlePosition()
{
  return middle;
}

void City::StopMusic()
{ 
  pSoundEngine->Stop(BGM);
}

City::City() :GameObject(LEVEL)
{

}





Bullet::Bullet() : GameObject(BULLET)
{

}

void Bullet::Initialise(Vector2D position, Vector2D velocity, float angl)
{
  m_acceleration = 700;
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
  /*Vector2D acc;
  acc.setBearing(m_angle, m_acceleration);
  m_velocity = m_velocity + acc*frametime;*/
  m_velocity = m_velocity + Vector2D(0, -20);

  m_animationSpeed = m_animationSpeed + 0.15;
  m_timer -= frametime;
  m_position = m_position + m_velocity*frametime;
  
  //m_position = m_position + Vector2D(0, -20);
  if (m_animationSpeed >= 5)
  {
    m_animationSpeed = 5;
    m_imageNumber = 5;
  }
  else
  {
    m_imageNumber = m_animationSpeed;
  }

  if (MyDrawEngine::GetInstance()->theCamera.returnPosition().XValue + 2000 < m_position.XValue ||
    MyDrawEngine::GetInstance()->theCamera.returnPosition().XValue - 2000 > m_position.XValue ||
    m_position.YValue > 2000)
  {
    Deactivate();
  }
  
}

  IShape2D& Bullet::GetCollisionShape()
{
  collisionShape.PlaceAt(m_position, 70);
  return collisionShape;
}

void Bullet::ProcessCollision(GameObject& other)
{
  if (other.GetType() != SPACESHIP && other.GetPosition().YValue < 440 || other.GetType() == ENEMY)
  {
    pSoundEngine->Play(hit, false);
    Particles* pParticles = new Particles;
    pParticles->Initialise(m_position, Vector2D(0, 0), 4.5f, 2.0f);
    Game::instance.m_objects.AddItem(pParticles, false);
    Deactivate();
  }
  





}


