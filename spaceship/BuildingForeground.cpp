#include "BuildingForeground.h"

//////////////////////////////////////////////////////
//////////////BuildingForeground////////////////////////////////
//////////////////////////////////////////////////////

void BuildingForeground::Initialise(Vector2D startPosition, Spaceship *player)
{
  m_pPlayer = player;
  m_drawDepth = 8;

  LoadImage(L"buildingfore.png");

  m_position = startPosition;

  incrementFrame = 0;
  initialPosition = m_position;
  m_imageScale = 3;
}

void BuildingForeground::Update(float frameTime)
{
  m_imageNumber = 0;

  m_position = initialPosition + Vector2D(m_pPlayer->getPosition().XValue*0.5, 0);
  incrementFrame += 0.025 *frameTime;

}

IShape2D& BuildingForeground::GetCollisionShape()
{
  m_collider.PlaceAt(m_position, 96);
  return m_collider;


}


void BuildingForeground::ProcessCollision(GameObject& other)
{
  //nothing

}

BuildingForeground::BuildingForeground() :GameObject(BUILDING)
{

}