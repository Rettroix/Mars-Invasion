#include "Building.h"


//Buildings are the main objects which you can land atop of


void Building::Initialise(Vector2D startPosition, Spaceship *player)
{
  m_drawDepth = 5;

  LoadImage(L"building.png");

  m_position = startPosition;

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

Building::Building() :GameObject(BUILDING)
{

}