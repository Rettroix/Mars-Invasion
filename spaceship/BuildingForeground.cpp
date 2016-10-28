#include "BuildingForeground.h"

//////////////////////////////////////////////////////
//////////////BuildingForeground////////////////////////////////
//////////////////////////////////////////////////////

void BuildingForeground::Initialise(Vector2D startPosition, Spaceship *player)
{
  m_pPlayer = player;
  m_drawDepth = 12;

  LoadImage(L"ground.png");

  m_position = startPosition;

  incrementFrame = 0;
  initialPosition = m_position;
  m_imageScale = 4;
}

void BuildingForeground::Update(float frameTime)
{
  m_imageNumber = 0;

  m_position = initialPosition + Vector2D(m_pPlayer->getPosition().XValue*0.25, 535);
  incrementFrame += 0.025 *frameTime;

}

IShape2D& BuildingForeground::GetCollisionShape()
{
  m_collider.PlaceAt(m_position, 96);
  return m_collider;


}

Vector2D BuildingForeground::getInitialPosition()
{
  return initialPosition;


}


void BuildingForeground::ProcessCollision(GameObject& other)
{
  //nothing

}

BuildingForeground::BuildingForeground() :GameObject(BUILDING)
{

}