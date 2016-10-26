#include "collisionShaper.h"

//////////////////////////////////////////////////////
//////////////Collision Shaper////////////////////////////////
//////////////////////////////////////////////////////

void CollisionShaper::Initialise(Building *pBuilding, float pos1, float pos2, float pos3, float pos4, int coltype)
{
  m_pBuilding = pBuilding;
  position1 = pos1;
  position2 = pos2;
  position3 = pos3;
  position4 = pos4;
  selectedType = coltype;
  m_drawDepth = 2;

}

void CollisionShaper::Update(float frameTime)
{
  m_position = Vector2D(0, collisionShape.GetEnd().YValue);


}

IShape2D& CollisionShaper::GetCollisionShape()
{
  collisionShape.PlaceAt(Vector2D(m_pBuilding->getPosition().XValue - position1, m_pBuilding->getPosition().YValue - position2), Vector2D(m_pBuilding->getPosition().XValue - position3, m_pBuilding->getPosition().YValue - position4));

  return collisionShape;
}

void CollisionShaper::Draw()
{
  
  //GameObject::Draw();
  //MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();
  //pTheDrawEngine->DrawLine(collisionShape.GetStart(), collisionShape.GetEnd(), 65525);

}

float CollisionShaper::GetTop()
{
  return collisionShape.GetStart().YValue;
}

void CollisionShaper::ProcessCollision(GameObject& other)
{
  //nothing

}

CollisionShaper::CollisionShaper() :GameObject(COLLIDER)
{

}

Segment2D CollisionShaper::GetShape()
{
  return collisionShape;
}