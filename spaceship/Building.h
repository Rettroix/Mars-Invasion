#pragma once

#include "GameObject.h"
#include "mysoundengine.h"
#include "GameObject.h"
#include "Spaceship.h"
#include "BuildingTypes.h"

class Building : public GameObject
{
private:
  Rectangle2D collisionShape;
  Vector2D m_velocity;
  float m_time;
  float incrementFrame;
  BuildingType currentBuilding = BuildingType::BUILDING0;

public:

  void Initialise(Vector2D startPosition, BuildingType spawnBuilding);
  void Draw();
  void Update(float frameTime);
  IShape2D& GetCollisionShape();
  void changePosition(Vector2D pos); // Change position of the building
  Vector2D getPosition(); //Get the position of the building
  void ProcessCollision(GameObject& other);
  //IShape2D& GetCollisionShape();
  Rectangle2D GetShape();
  Building();
};
