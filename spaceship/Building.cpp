#include "Building.h"
#include "BuildingTypes.h"

//Buildings are the main objects which you can land atop of


void Building::Initialise(Vector2D startPosition, BuildingType spawnBuilding)
{
  currentBuilding = spawnBuilding;
  m_drawDepth = 5;
  switch (currentBuilding)
  {
  case BuildingType::BUILDING0:
  {
    
    LoadImage(L"building.png");
    m_position = startPosition;
  }  
  break;

  case BuildingType::BUILDING1:
  {
    LoadImage(L"building1.png");
    m_position = startPosition;
  }
  break;

  case BuildingType::BUILDING2:
  {
    LoadImage(L"building2.png");
    m_position = startPosition;
  }
  break;

  case BuildingType::BUILDING3:
  {
    
    LoadImage(L"building3.png");
    m_position = startPosition;
    
  }
  break;
  
  case BuildingType::BUILDING4:
  {
    LoadImage(L"building4.png");
    m_position = startPosition + Vector2D(0, 0);
  }
  break;

  case BuildingType::FUELBUILDING:
  {
    LoadImage(L"fuelbuilding.png");
    m_position = startPosition + Vector2D(0, 0);
  }
  break;

  case BuildingType::HOUSE:
  {
    LoadImage(L"house.png");
    m_position = startPosition + Vector2D(0, -500);
  }
  break;


  }


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

void Building::changePosition(Vector2D pos)
{
  m_position =  pos;
}

Vector2D Building::getPosition()
{
  return m_position;
}

Building::Building() :GameObject(BUILDING)
{

}