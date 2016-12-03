#pragma once

#include "Lander.h"
#include "GameObject.h"
#include "mysoundengine.h"
#include "Spaceship.h"
#include "Building.h"

#include "BuildingForeground.h"
#include "BuildingBackground.h"
#include "BuildingTypes.h"
#include "collisionShaper.h"
#include "FuelBox.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

// Create your game entity classes here
const int NUMBER_OF_BUILDINGS = 20;





class City : public GameObject
{
private:   
  MySoundEngine* pSoundEngine = MySoundEngine::GetInstance(); //Calling a pointer to an instance of sound engine
  SoundIndex BGM = pSoundEngine->LoadWav(L"BGM.wav"); //Loading Background Music

  bool gameStarted; //is the game started
  Circle2D m_circle;
  Circle2D m_collider;
  float incrementFrame;
  int spawnedBuildings[10];
  Vector2D shipsPosition;
  int shipXValue;
  float fship;
  Spaceship *m_pPlayer = nullptr;
  Building *m_pBuildings[NUMBER_OF_BUILDINGS];
  BuildingForeground *m_pForegroundBuildings[NUMBER_OF_BUILDINGS];
  BuildingBackground *m_pBackgroundBuildings[NUMBER_OF_BUILDINGS];
  Lander *pCollision[NUMBER_OF_BUILDINGS];
  Lander *pCollisionTop[NUMBER_OF_BUILDINGS];
  Lander *pCollisionRight[NUMBER_OF_BUILDINGS];

  FuelBox *pFuelBox[NUMBER_OF_BUILDINGS];
  
  int furthestLeft; //Building furthest to the left
  int furthestRight; //Building furthest to the right
  int middle; //middle building
  int lastIndex;

  int furthestLeftBG; //Building furthest to the left BG
  int furthestRightBG; //Building furthest to the right BG
  int middleBG;
  int lastIndexBG;

  int furthestLeftFG; //Building furthest to the left FG
  int furthestRightFG; //Building furthest to the right FG
  int middleFG;
  int lastIndexFG;

  int enemyOneCoolDown;   //Enemies can't spawn when this is above 0
  int enemyAmmount;   //how many enemies are spawned
  int maxEnemyAmmount;  //The max ammount of ennemies allowed

  BuildingType selectedBuilding = BuildingType::BUILDING0;
  int randomBuilding;

  bool m_musicPlaying;
public:
  
  void Initialise(Spaceship *player);
  void Update(float frameTime);
  void spawnBuilding(); //spawn buildings
  void spawnBG(); //spawn background buildings
  void spawnFG(); //spawn foreground buildings
  void spawnEnemies();  //Spawn enemies
  void updateBuildings(); //Update Buildings
  void updateBuildingsBG(); //Update background buildings
  void updateBuildingsFG(); //Update foreground buildings
  void StopMusic(); //Stop the backgroud music
  IShape2D& GetCollisionShape();  //Get collision shape
  void ProcessCollision(GameObject& other); //Process collisions
  int getMiddlePosition();
  void deincrementEnemyAmmount();
  void spawnBuildingBlock(int interation);
  void spawnCollisionBlockLeft();
  void spawnCollisionBlockRight();
  void spawnCollisionBlockTop();
  City();
};





class Bullet : public GameObject
{
private:
  Vector2D m_velocity;
  Circle2D collisionShape;
  float m_acceleration;
  float m_timer;  // Lifetime
  Spaceship *m_pPlayer;

  float m_animationSpeed;   // Frames of animation per second
  float m_currentAnimation; // Current animation frame

  //sound
  MySoundEngine* pSoundEngine = MySoundEngine::GetInstance();
  SoundIndex hit = pSoundEngine->LoadWav(L"hit.wav");
public:
  Bullet();
  void Initialise(Vector2D position, Vector2D velocity, float angl);
  void Update(float frametime);
  IShape2D& GetCollisionShape();
  void ProcessCollision(GameObject& other);
  
};


