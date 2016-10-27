#include "Building.h"
#include "BuildingTypes.h"

//Buildings are the main objects which you can land atop of


void Building::Initialise(Vector2D startPosition, BuildingType spawnBuilding)
{
  positionStart = startPosition;
  currentBuilding = spawnBuilding;
  m_drawDepth = 8;
  LoadImage(L"building.png");
  LoadImage(L"building1.png");
  LoadImage(L"building2.png");
  LoadImage(L"building3.png");
  LoadImage(L"building4.png");
  LoadImage(L"fuelbuilding.png");
  LoadImage(L"house.png");
  
  switch (currentBuilding)
  {
  case BuildingType::BUILDING0:
    m_imageNumber = 0;
    m_position = startPosition;
    m_objectSize = Vector2D(128, 414)*m_imageScale;
    break;
  case BuildingType::BUILDING1:
    m_imageNumber = 1;
    m_position = startPosition;
    m_objectSize = Vector2D(167, 284)*m_imageScale;
    break;
  case BuildingType::BUILDING2: 
    m_imageNumber = 2;
    m_position = startPosition;
    m_objectSize = Vector2D(167, 342)*m_imageScale;
    break;
  case BuildingType::BUILDING3:
    m_imageNumber = 3;
    m_position = startPosition + Vector2D(0, -300);
    m_objectSize = Vector2D(167, 284)*m_imageScale;
   break;
  case BuildingType::BUILDING4:
    m_imageNumber = 4;
    m_position = startPosition + Vector2D(0, 0);
    m_objectSize = Vector2D(167, 284)*m_imageScale;
    break;
  case BuildingType::FUELBUILDING:
    m_imageNumber = 5;
    m_position = startPosition + Vector2D(0, -300);
    m_objectSize = Vector2D(167, 150)*m_imageScale;
    break;
  case BuildingType::HOUSE:
    m_imageNumber = 6;
    m_position = startPosition + Vector2D(0, -280);
    m_objectSize = Vector2D(167, 284)*m_imageScale;
   break;
  }


  incrementFrame = 0;

  m_imageScale = 2;

}

void Building::Update(float frameTime)
{


  
  //collisionShape.PlaceAt(m_position.YValue + (m_objectSize.YValue), m_position.XValue - (m_objectSize.XValue), m_position.YValue - (m_objectSize.YValue), m_position.XValue + (m_objectSize.XValue));
  //MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();
  //pTheDrawEngine->FillRect(collisionShape, 65525);

}

void Building::Draw()
{
  GameObject::Draw();
  //MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();
  //pTheDrawEngine->FillRect(collisionShape, 65525);

}
IShape2D& Building::GetCollisionShape()
{
  collisionShape.PlaceAt(m_position.YValue + (m_objectSize.YValue), m_position.XValue - (m_objectSize.XValue), m_position.YValue - (m_objectSize.YValue), m_position.XValue + (m_objectSize.XValue));

  return collisionShape;
}


void Building::ProcessCollision(GameObject& other)
{

  //nothing

}

void Building::changePosition(Vector2D pos)
{
  m_position =  pos;
}

BuildingType Building::getBuildingType()
{
  return currentBuilding;
}


Vector2D Building::getPosition()
{
  return m_position;
}

void Building::changeBuilding(BuildingType spawnBuilding)
{
  currentBuilding = spawnBuilding;


  switch (currentBuilding)
  {
  case BuildingType::BUILDING0:
    m_imageNumber = 0;
    m_position = positionStart;
    m_objectSize = Vector2D(128, 414)*m_imageScale;
    break;
  case BuildingType::BUILDING1:
    m_imageNumber = 1;
    m_position = positionStart;
    m_objectSize = Vector2D(167, 284)*m_imageScale;
    break;
  case BuildingType::BUILDING2:
    m_imageNumber = 2;
    m_position = positionStart;
    m_objectSize = Vector2D(167, 342)*m_imageScale;
    break;
  case BuildingType::BUILDING3:
    m_imageNumber = 3;
    m_position = positionStart + Vector2D(0, -300);
    m_objectSize = Vector2D(167, 284)*m_imageScale;
    break;
  case BuildingType::BUILDING4:
    m_imageNumber = 4;
    m_position = positionStart + Vector2D(0, 0);
    m_objectSize = Vector2D(167, 284)*m_imageScale;
    break;
  case BuildingType::FUELBUILDING:
    m_imageNumber = 5;
    m_position = positionStart + Vector2D(0, -300);
    m_objectSize = Vector2D(167, 150)*m_imageScale;
    break;
  case BuildingType::HOUSE:
    m_imageNumber = 6;
    m_position = positionStart + Vector2D(0, -280);
    m_objectSize = Vector2D(167, 284)*m_imageScale;
    break;
  }


}

Rectangle2D Building::GetShape()
{
  return collisionShape;
}

Building::Building() :GameObject(BUILDING)
{

}