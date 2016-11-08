#pragma once

#include "Lander.h"
#include "GameObject.h"
#include "mysoundengine.h"
#include "GameObject.h"
#include "Spaceship.h"
#include "Building.h"
#include "userInterface.h"
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
  int changeDelay;

  Circle2D m_circle;
  Circle2D m_collider;
  float incrementFrame;
  int spawnedBuildings[10];
  Vector2D shipsPosition;
  int shipXValue;
  float fship;
  Spaceship *m_pPlayer;
  Building *m_pBuildings[NUMBER_OF_BUILDINGS];
  BuildingForeground *m_pForegroundBuildings[NUMBER_OF_BUILDINGS];
  BuildingBackground *m_pBackgroundBuildings[NUMBER_OF_BUILDINGS];
  Lander *pCollision[NUMBER_OF_BUILDINGS];
  Lander *pCollisionTop[NUMBER_OF_BUILDINGS];
  Lander *pCollisionRight[NUMBER_OF_BUILDINGS];

  FuelBox *pFuelBox[NUMBER_OF_BUILDINGS];
  
  int furthestLeft; //Building furthest to the left
  int furthestRight; //Building furthest to the right
  int middle;
  int lastIndex;

  int furthestLeftBG; //Building furthest to the left BG
  int furthestRightBG; //Building furthest to the right BG
  int middleBG;
  int lastIndexBG;

  int furthestLeftFG; //Building furthest to the left FG
  int furthestRightFG; //Building furthest to the right FG
  int middleFG;
  int lastIndexFG;

  BuildingType selectedBuilding = BuildingType::BUILDING0;
  int randomBuilding;

public:
  
  void Initialise(Spaceship *player);
  void spawnBuilding();
  void spawnBG();
  void spawnFG();

  void updateBuildings();
  void updateBuildingsBG();
  void updateBuildingsFG();

  void Update(float frameTime);
  IShape2D& GetCollisionShape();

  void ProcessCollision(GameObject& other);
  void addShipPosition(Vector2D pos);
  City();
};





class Bullet : public GameObject
{
private:
  Vector2D m_velocity;
  Point2D m_collider;
  float m_timer;  // Lifetime

  float m_animationSpeed;   // Frames of animation per second
  float m_currentAnimation; // Current animation frame

public:
  Bullet();
  void Initialise(Vector2D position, Vector2D velocity, float angl);
  void Update(float frametime);
  IShape2D& GetCollisionShape();
  void ProcessCollision(GameObject& other);
  
};


