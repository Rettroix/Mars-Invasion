//Title     : Building.h
//Purpose   : Creates a specific building and can change the building type
//Author    : Elliot Anderson
//Date      : 5/12/16
#pragma once

#include "GameObject.h"
#include "mysoundengine.h"
#include "GameObject.h"
#include "Spaceship.h"
#include "BuildingTypes.h"

class Building : public GameObject
{
private:
  Rectangle2D collisionShape; //The collision shape
  Vector2D positionStart; //the initial position of the building
  BuildingType currentBuilding = BuildingType::BUILDING0;
  Spaceship *m_pPlayer; //pointer to player

public:

  void Initialise(Vector2D startPosition, BuildingType spawnBuilding, Spaceship *player);
  void changeBuilding(BuildingType spawnBuilding);  //Changes the building type
  void Draw();
  void Update(float frameTime);
  IShape2D& GetCollisionShape();
  void changePosition(Vector2D pos); // Change position of the building
  Vector2D getPosition(); //Get the position of the building
  void ProcessCollision(GameObject& other);
  BuildingType getBuildingType(); //Get's the current building type
  Rectangle2D GetShape();
  Building();
};
