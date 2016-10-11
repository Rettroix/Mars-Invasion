#include "BuildingBackground.h"

//////////////////////////////////////////////////////
//////////////BuildingBackground//////////////////////
//////////////////////////////////////////////////////

void BuildingBackground::Initialise(Vector2D startPosition, Spaceship *player)
{
  m_pPlayer = player;
  m_drawDepth = 1;

  LoadImage(L"city.png");

  m_position = startPosition;

  incrementFrame = 0;
  initialPosition = m_position;
  m_imageScale = 9;
}

void BuildingBackground::Update(float frameTime)
{
  m_imageNumber = 0;

  m_position = initialPosition - Vector2D(m_pPlayer->getPosition().XValue*0.5, 0);
  incrementFrame += 0.025 *frameTime;

}

IShape2D& BuildingBackground::GetCollisionShape()
{
  m_collider.PlaceAt(m_position, 96);
  return m_collider;


}


void BuildingBackground::ProcessCollision(GameObject& other)
{
  //nothing

}

BuildingBackground::BuildingBackground() :GameObject(BUILDING)
{

}