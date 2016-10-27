#include "FuelBox.h"

//Buildings are the main objects which you can land atop of


void FuelBox::Initialise(Vector2D startPosition)
{
  LoadImage(L"crate.png");
  m_drawDepth = 11;
  m_position = startPosition;
  m_objectSize = Vector2D(64, 64);
}

void FuelBox::Update(float frameTime)
{


}

void FuelBox::Draw()
{
  GameObject::Draw();
  MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();
  pTheDrawEngine->FillRect(collisionShape, 65525);

}
IShape2D& FuelBox::GetCollisionShape()
{
  collisionShape.PlaceAt(m_position.YValue + (m_objectSize.YValue), m_position.XValue - (m_objectSize.XValue), m_position.YValue - (m_objectSize.YValue), m_position.XValue + (m_objectSize.XValue));

  return collisionShape;
}


void FuelBox::ProcessCollision(GameObject& other)
{

  //nothing

}



Vector2D FuelBox::getPosition()
{
  return m_position;
}

Rectangle2D FuelBox::GetShape()
{
  return collisionShape;
}

FuelBox::FuelBox() :GameObject(BUILDING)
{

}