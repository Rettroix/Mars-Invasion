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
      //spawn that particular building
      spawnBuildingBlock(i);
      //spawn it's left wall collisions
      spawnCollisionBlockLeft(i, 260, 500, 260, -500, 0);
      //spawn it's top wall collisions
      spawnCollisionBlockTop(i, 260, -500, -260, -500, 0);
      //spawn it's right wall collisions
      spawnCollisionBlockRight(i, -260, 500, -260, -500, 0);
    }
    else if (selectedBuilding == BuildingType::BUILDING2)
    {
      //spawn that particular building
      spawnBuildingBlock(i);
      //spawn it's left wall collisions
      spawnCollisionBlockLeft(i, 260, 500, 260, -200, 0);
      //spawn it's top wall collisions
      spawnCollisionBlockTop(i, 260, -200, -260, -500, 0);
      //spawn it's right wall collisions
      spawnCollisionBlockRight(i, -260, 500, -260, -500, 0);
    }

    else if (selectedBuilding == BuildingType::BUILDING3)
    {
      //spawn that particular building
      spawnBuildingBlock(i);
      //spawn it's left wall collisions
      spawnCollisionBlockLeft(i, 260, 500, 260, -230, 0);
      //spawn it's top wall collisions
      spawnCollisionBlockTop(i, 260, -230, -260, -230, 0);
      //spawn it's right wall collisions
      spawnCollisionBlockRight(i, -260, 500, -260, -230, 0);

    }

    else if (selectedBuilding == BuildingType::BUILDING4)
    {
      //spawn that particular building
      spawnBuildingBlock(i);
      //spawn it's left wall collisions
      spawnCollisionBlockLeft(i, 260, 500, 260, -450, 0);
      //spawn it's top wall collisions
      spawnCollisionBlockTop(i, 260, -450, -260, -300, 0);
      //spawn it's right wall collisions
      spawnCollisionBlockRight(i, -260, 500, -260, -300, 0);


    }

    else if (selectedBuilding == BuildingType::HOUSE)
    {
      //spawn that particular building
      spawnBuildingBlock(i);
      //spawn it's left wall collisions
      spawnCollisionBlockLeft(i, 260, 500, 260, -100, 0);
      //spawn it's top wall collisions
      spawnCollisionBlockTop(i, 260, -100, -260, -100, 0);
      //spawn it's right wall collisions
      spawnCollisionBlockRight(i,-260, 500, -260, -100, 0);

    }

    else if (selectedBuilding == BuildingType::FUELBUILDING)
    {
      //spawn that particular building
      spawnBuildingBlock(i);
      //spawn it's left wall collisions
      spawnCollisionBlockLeft(i, 260, 500, 260, -100, 0);
      //spawn it's top wall collisions
      spawnCollisionBlockTop(i, 260, -100, -260, -100, 1);
      //spawn it's right wall collisions
      spawnCollisionBlockRight(i, -260, 500, -260, -100, 0);


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
      //and if the last indexed building is further left than the current furthest left building
      if (m_pBuildings[lastIndex]->getPosition().XValue <= m_pBuildings[furthestLeft]->getPosition().XValue)
      {
        furthestLeft = lastIndex; //Then the last index building is further left
      }
      else
      {
        furthestLeft = furthestLeft; //else furthest left is the same
      }

    }

    else
    {
      furthestLeft = i + (NUMBER_OF_BUILDINGS / 2); //Then the furthest left is current building

    }

    if (furthestLeft == 0) //when furthest left building is 0 it is set to 20
    {
      furthestRight = 20;
    }

    else
    {
      furthestRight = furthestLeft - 1; //otherwise furthest left is itself minus one
    }


    lastIndex = i + (NUMBER_OF_BUILDINGS / 2); //The last index is set to current loop
  }

}

void City::spawnBG()
{
  for (int i = -(NUMBER_OF_BUILDINGS / 2); i < (NUMBER_OF_BUILDINGS / 2); i++)
  {
    //spawn the background buildings
    if (m_pBackgroundBuildings[i + (NUMBER_OF_BUILDINGS / 2)] == nullptr)
    {
      m_pBackgroundBuildings[i + (NUMBER_OF_BUILDINGS / 2)] = new BuildingBackground;
      m_pBackgroundBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(Vector2D(i * 4000, 0), m_pPlayer);
      Game::instance.m_objects.AddItem(m_pBackgroundBuildings[i + (NUMBER_OF_BUILDINGS / 2)], true);
    }


    

    //If the last indexed building is further left than current building
    if (m_pBackgroundBuildings[lastIndexBG]->getInitialPosition().XValue <= m_pBackgroundBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->getInitialPosition().XValue) 
    {
      //and if the last indexed building is further left than the current furthest left building
      if (m_pBackgroundBuildings[lastIndexBG]->getInitialPosition().XValue <= m_pBackgroundBuildings[furthestLeftBG]->getInitialPosition().XValue)
      {
        furthestLeftBG = lastIndexBG; //Then the last index building is further left 
      }
      else
      {
        furthestLeftBG = furthestLeftBG;//else furthest left is the same
      }

    }

    else
    {
      furthestLeftBG = i + (NUMBER_OF_BUILDINGS / 2); //Then the furthest left is current building

    }

    if (furthestLeftBG == 0) //when furthest left building is 0 it is set to 20
    {
      furthestRightBG = 20;
    }

    else
    {
      furthestRightBG = furthestLeftBG - 1; // otherwise furthest left is itself minus one
    }


    lastIndexBG = i + (NUMBER_OF_BUILDINGS / 2); //The last index is set to current loop
  }

}

void City::spawnFG()
{
  for (int i = -(NUMBER_OF_BUILDINGS / 2); i < (NUMBER_OF_BUILDINGS / 2); i++)
  {
    //if it's null pointer spawn the buildings
    if (m_pForegroundBuildings[i + (NUMBER_OF_BUILDINGS / 2)] == nullptr)
    {
      m_pForegroundBuildings[i + (NUMBER_OF_BUILDINGS / 2)] = new BuildingForeground;
      m_pForegroundBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->Initialise(Vector2D(i * 4000, -470), m_pPlayer);

      Game::instance.m_objects.AddItem(m_pForegroundBuildings[i + (NUMBER_OF_BUILDINGS / 2)], true);
    }

    //If the last indexed building is further left than current building
    if (m_pForegroundBuildings[lastIndexFG]->getInitialPosition().XValue <= m_pForegroundBuildings[i + (NUMBER_OF_BUILDINGS / 2)]->getInitialPosition().XValue) 
    {//and if the last indexed building is further left than the current furthest left building
      if (m_pForegroundBuildings[lastIndexFG]->getInitialPosition().XValue <= m_pForegroundBuildings[furthestLeftFG]->getInitialPosition().XValue)
      {
        furthestLeftFG = lastIndexFG; //Then the last index building is further left 
      }
      else
      {
        furthestLeftFG = furthestLeftFG; //else furthest left is the same
      }

    }

    else
    {
      furthestLeftFG = i + (NUMBER_OF_BUILDINGS / 2); //Then the furthest left is current building

    }

    if (furthestLeftFG == 0) //when furthest left building is 0 it is set to 20
    {
      furthestRightFG = 20;
    }

    else
    {
      furthestRightFG = furthestLeftFG - 1; //otherwise furthest left is itself minus one
    }


    lastIndexFG = i + (NUMBER_OF_BUILDINGS / 2); //The last index is set to current loop
  }

}

void City::updateBuildings()
{
  selectedBuilding = static_cast<BuildingType>(rand() % 6 + 1); //randomize building again
  lastIndex = 0; //set last index back to 0
  furthestLeft = 0; //set furthest left back to 0

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

  //works out where the middle of the building array is
  middle = (m_pBuildings[furthestLeft]->getPosition().XValue + m_pBuildings[furthestRight]->getPosition().XValue) / 2;


  //if the players position is bigger than the middle
  if (m_pPlayer->getPosition().XValue > middle)
  {
    //then change the furthest left building to the position of the furthest right building
    m_pBuildings[furthestLeft]->changePosition(Vector2D((m_pBuildings[furthestRight]->getPosition().XValue + rand()%300), (m_pBuildings[furthestLeft]->getPosition().YValue)) + Vector2D(700, 0));

  }

  //if the players position is smaller than middle
  if (m_pPlayer->getPosition().XValue < middle)
  {
    //then change the furthest right building to furthest left
    m_pBuildings[furthestRight]->changePosition(Vector2D((m_pBuildings[furthestLeft]->getPosition().XValue + rand() % 300), (m_pBuildings[furthestRight]->getPosition().YValue)) - Vector2D(700, 0));
    //change the new furthest right building's building type
    m_pBuildings[furthestRight]->changeBuilding(selectedBuilding);
  }




  //MyDrawEngine::GetInstance()->WriteInt(700, 220, furthestLeft, MyDrawEngine::WHITE);

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
  //if the camera is less than this specified position
  if (MyDrawEngine::GetInstance()->theCamera.returnPosition().XValue < 11200)
  {
    //then there is only allowed to be 1 enemy at a time
    maxEnemyAmmount = 1;

  }
  //only 3 below this value
  else if (MyDrawEngine::GetInstance()->theCamera.returnPosition().XValue < 12000)
  {
    maxEnemyAmmount = 3;
  }
  //6 below this value
  else if (MyDrawEngine::GetInstance()->theCamera.returnPosition().XValue < 12500)
  {
    maxEnemyAmmount = 6;
  }
  //20 below this value
  else if (MyDrawEngine::GetInstance()->theCamera.returnPosition().XValue < 20000)
  {
    maxEnemyAmmount = 20;
  }

  //if the enemy cool down is below 0 and the random number generator hits a 7
  //and the enemy ammount on screen is less than the maximum allowed
  if (enemyOneCoolDown < 0 && rand() % 100 == 7 && enemyAmmount < maxEnemyAmmount)
  {
    //choose a random enemy out of three numbers
    int chooseEnemy;
    chooseEnemy = rand() % 3;
    //increase the enemy count on screen
    enemyAmmount++;
    //sets the cool down to 100
    enemyOneCoolDown = 100;
    //if the chosen enemy is 0
    if (chooseEnemy == 0)
    {
      //we spawn the enemy which follows you around
      Missile* pMissile = new Missile;
      pMissile->Initialise(m_pPlayer->GetPosition() + Vector2D(2000, 0), m_pPlayer, this);
      Game::instance.m_objects.AddItem(pMissile, true);

      EnemyOne* pEnemyOne = new EnemyOne;
      pEnemyOne->Initialise(m_pPlayer->GetPosition() + Vector2D(2000, 0), m_pPlayer, pMissile);
      Game::instance.m_objects.AddItem(pEnemyOne, true);

    }

    //if chosen enemy is 1
    else if (chooseEnemy == 1)
    {
      //then we spawn the spinning enemy that spins in place
      EnemyShip* pEnemyShip = new EnemyShip;
      pEnemyShip->Initialise(m_pPlayer->GetPosition() + Vector2D(2000, rand() % 1000), m_pPlayer, this);
      Game::instance.m_objects.AddItem(pEnemyShip, true);

    }

    //if we choose enemy 2
    else if (chooseEnemy == 2)
    {
      //then we spawn the enemy which flies left while aiming and shooting at the player
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

void City::spawnCollisionBlockLeft(int iteration, int pos1, int pos2, int pos3, int pos4, int coltype)
{
  if (pCollision[iteration + (NUMBER_OF_BUILDINGS / 2)] == nullptr)
  {
    //spawns the collision for the left side of the building
    pCollision[iteration + (NUMBER_OF_BUILDINGS / 2)] = new Lander;
    pCollision[iteration + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[iteration + (NUMBER_OF_BUILDINGS / 2)], pos1, pos2, pos3, -pos4, coltype, CollisionPosition::LEFT, CollisionType::BOUNCE);
    Game::instance.m_objects.AddItem(pCollision[iteration + (NUMBER_OF_BUILDINGS / 2)], true);
  }
}
void City::spawnCollisionBlockRight(int iteration, int pos1, int pos2, int pos3, int pos4, int coltype)
{
  if (pCollisionRight[iteration + (NUMBER_OF_BUILDINGS / 2)] == nullptr)
  {
    //spawns the collision for the right side of the building
    pCollisionRight[iteration + (NUMBER_OF_BUILDINGS / 2)] = new Lander;
    pCollisionRight[iteration + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[iteration + (NUMBER_OF_BUILDINGS / 2)], pos1, pos2, pos3, pos4, coltype, CollisionPosition::RIGHT, CollisionType::BOUNCE);
    Game::instance.m_objects.AddItem(pCollisionRight[iteration + (NUMBER_OF_BUILDINGS / 2)], true);
  }

}
void City::spawnCollisionBlockTop(int iteration, int pos1, int pos2, int pos3, int pos4, int coltype)
{
  if (pCollisionTop[iteration + (NUMBER_OF_BUILDINGS / 2)] == nullptr)
  {
    //spawns the collision for the top  of the building
    pCollisionTop[iteration + (NUMBER_OF_BUILDINGS / 2)] = new Lander;
    pCollisionTop[iteration + (NUMBER_OF_BUILDINGS / 2)]->Initialise(m_pBuildings[iteration + (NUMBER_OF_BUILDINGS / 2)], pos1, pos2, pos3, pos4, coltype, CollisionPosition::TOP, CollisionType::LANDER);
    Game::instance.m_objects.AddItem(pCollisionTop[iteration + (NUMBER_OF_BUILDINGS / 2)], true);
  }

}
void City::deincrementEnemyAmmount()
{
  //deincrement the ammount of enemies on screen
  enemyAmmount--;
}

int City::getMiddlePosition()
{
  //returns the middle of the building array
  return middle;
}

void City::StopMusic()
{ 
  //stop the background music
  pSoundEngine->Stop(BGM);
}

//object type is level since this just sets out the level
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


