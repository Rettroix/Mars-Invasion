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

  m_position = initialPosition + Vector2D(m_pPlayer->getPosition().XValue*-2, 535);
  incrementFrame += 0.025 *frameTime;

}

IShape2D& BuildingForeground::GetCollisionShape()
{
  collisionShape.PlaceAt(Vector2D(m_position.XValue - 2000, -1020), Vector2D(m_position.XValue + 2000, -1020));
  return collisionShape;


}

void BuildingForeground::Draw()
{

  GameObject::Draw();
  //MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();
  //pTheDrawEngine->DrawLine(collisionShape.GetStart(), collisionShape.GetEnd(), 65525);

}

Vector2D BuildingForeground::getPosition()
{
  return m_position;
}

Vector2D BuildingForeground::getInitialPosition()
{
  return initialPosition;


}

void BuildingForeground::changeInitialPosition(Vector2D pos)
{
  initialPosition = pos;
}


void BuildingForeground::ProcessCollision(GameObject& other)
{

}

BuildingForeground::BuildingForeground() :GameObject(FLOOR)
{
}