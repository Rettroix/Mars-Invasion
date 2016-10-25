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
    LoadImage(L"building.png");
    m_position = startPosition;
    m_objectSize = Vector2D(128, 414)*m_imageScale;
    break;
  case BuildingType::BUILDING1:
    LoadImage(L"building1.png");
    m_position = startPosition;
    m_objectSize = Vector2D(167, 284)*m_imageScale;
    break;
  case BuildingType::BUILDING2: 
    LoadImage(L"building2.png");
    m_position = startPosition;
    m_objectSize = Vector2D(167, 342)*m_imageScale;
    break;
  case BuildingType::BUILDING3:
    LoadImage(L"building3.png");
    m_position = startPosition + Vector2D(0, -300);
    m_objectSize = Vector2D(167, 284)*m_imageScale;
   break;
  case BuildingType::BUILDING4:
    LoadImage(L"building4.png");
    m_position = startPosition + Vector2D(0, 0);
    m_objectSize = Vector2D(167, 284)*m_imageScale;
    break;
  case BuildingType::FUELBUILDING:
    LoadImage(L"fuelbuilding.png");
    m_position = startPosition + Vector2D(0, -300);
    m_objectSize = Vector2D(167, 284)*m_imageScale;
    break;
  case BuildingType::HOUSE:
    LoadImage(L"house.png");
    m_position = startPosition + Vector2D(0, -280);
    m_objectSize = Vector2D(167, 284)*m_imageScale;
   break;
  }


  incrementFrame = 0;

  m_imageScale = 2;

}

void Building::Update(float frameTime)
{


  m_imageNumber = 0;
  //collisionShape.PlaceAt(m_position.YValue + (m_objectSize.YValue), m_position.XValue - (m_objectSize.XValue), m_position.YValue - (m_objectSize.YValue), m_position.XValue + (m_objectSize.XValue));
  //MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();
  //pTheDrawEngine->FillRect(collisionShape, 65525);

}

void Building::Draw()
{
  GameObject::Draw();
  MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();
  //pTheDrawEngine->FillCircle(m_position, collisionShape.GetRadius(), 65525);
  pTheDrawEngine->FillRect(collisionShape, 65525);

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

Vector2D Building::getPosition()
{
  return m_position;
}

Rectangle2D Building::GetShape()
{
  return collisionShape;
}

Building::Building() :GameObject(BUILDING)
{

}