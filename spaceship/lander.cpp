#include "lander.h"

//////////////////////////////////////////////////////
//////////////Collision Shaper////////////////////////////////
//////////////////////////////////////////////////////

void Lander::Initialise(Building *pBuilding, float pos1, float pos2, float pos3, float pos4, int coltype, CollisionPosition colpos, CollisionType colTyp)
{
  collisionReaction = colTyp;
  currentPosition = colpos;
  m_pBuilding = pBuilding;
  position1 = pos1;
  position2 = pos2;
  position3 = pos3;
  position4 = pos4;
  selectedType = coltype; //Gives you fuel or not
  m_drawDepth = 2;
  collisionShape.PlaceAt(Vector2D(m_pBuilding->getPosition().XValue - position1, m_pBuilding->getPosition().YValue - position2), Vector2D(m_pBuilding->getPosition().XValue - position3, m_pBuilding->getPosition().YValue - position4));

}

void Lander::Update(float frameTime)
{
  becomeBuilding();
  m_position = Vector2D(0, collisionShape.GetEnd().YValue);

  collisionShape.PlaceAt(Vector2D(m_pBuilding->getPosition().XValue - position1, m_pBuilding->getPosition().YValue - position2), Vector2D(m_pBuilding->getPosition().XValue - position3, m_pBuilding->getPosition().YValue - position4));

}

IShape2D& Lander::GetCollisionShape()
{

  return collisionShape;
}

void Lander::Draw()
{

  //GameObject::Draw();
  //MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();
  //pTheDrawEngine->DrawLine(collisionShape.GetStart(), collisionShape.GetEnd(), 65525);

}

float Lander::GetTop()
{
  return collisionShape.GetStart().YValue;
}

void Lander::ProcessCollision(GameObject& other)
{
  //nothing

}



int Lander::GetColType()
{
  return selectedType;
}

Lander::Lander() :GameObject(LANDER)
{

}

Segment2D Lander::GetShape()
{
  return collisionShape;
}

CollisionType Lander::getCollisionReaction()
{
  return collisionReaction;

}

void Lander::becomeBuilding()
{
  //If it's used for top collisions
  if (currentPosition == CollisionPosition::TOP)
  {
    if (m_pBuilding->getBuildingType() == BuildingType::BUILDING1)
    {

      position1 = 260;
      position2 = -500;
      position3 = -260;
      position4 = -500;
      selectedType = 0;
      collisionReaction = CollisionType::LANDER;
    }

    else if (m_pBuilding->getBuildingType() == BuildingType::BUILDING2)
    {
      position1 = 260;
      position2 = -200;
      position3 = -260;
      position4 = -500;
      selectedType = 0;
      collisionReaction = CollisionType::BOUNCE;

    }

    else if (m_pBuilding->getBuildingType() == BuildingType::BUILDING3)
    {
      position1 = 260;
      position2 = -230;
      position3 = -260;
      position4 = -230;
      selectedType = 0;
      collisionReaction = CollisionType::LANDER;

    }

    else if (m_pBuilding->getBuildingType() == BuildingType::BUILDING4)
    {
      position1 = 260;
      position2 = -450;
      position3 = -260;
      position4 = -300;
      selectedType = 0;
      collisionReaction = CollisionType::BOUNCE;

    }

    else if (m_pBuilding->getBuildingType() == BuildingType::HOUSE)
    {
      position1 = 260;
      position2 = -100;
      position3 = -260;
      position4 = -100;
      selectedType = 0;
      collisionReaction = CollisionType::LANDER;

    }

    else if (m_pBuilding->getBuildingType() == BuildingType::FUELBUILDING)
    {
      position1 = 260;
      position2 = -100;
      position3 = -260;
      position4 = -100;
      selectedType = 1;
      collisionReaction = CollisionType::LANDER;

    }
  }

  //If it's used for left collisions
  else if (currentPosition == CollisionPosition::LEFT)
  {
    if (m_pBuilding->getBuildingType() == BuildingType::BUILDING1)
    {

      position1 = 260;
      position2 = 500;
      position3 = 260;
      position4 = -500;
      selectedType = 0;
      collisionReaction = CollisionType::BOUNCE;

    }

    else if (m_pBuilding->getBuildingType() == BuildingType::BUILDING2)
    {
      position1 = 260;
      position2 = 500;
      position3 = 260;
      position4 = -200;
      selectedType = 0;
      collisionReaction = CollisionType::BOUNCE;

    }

    else if (m_pBuilding->getBuildingType() == BuildingType::BUILDING3)
    {
      position1 = 260;
      position2 = 500;
      position3 = 260;
      position4 = -230;
      selectedType = 0;
      collisionReaction = CollisionType::BOUNCE;

    }

    else if (m_pBuilding->getBuildingType() == BuildingType::BUILDING4)
    {
      position1 = 260;
      position2 = 500;
      position3 = 260;
      position4 = -450;
      selectedType = 0;
      collisionReaction = CollisionType::BOUNCE;

    }

    else if (m_pBuilding->getBuildingType() == BuildingType::HOUSE)
    {
      position1 = 260;
      position2 = 500;
      position3 = 260;
      position4 = -100;
      selectedType = 0;
      collisionReaction = CollisionType::BOUNCE;

    }

    else if (m_pBuilding->getBuildingType() == BuildingType::FUELBUILDING)
    {
      position1 = 260;
      position2 = 500;
      position3 = 260;
      position4 = -100;
      selectedType = 1;
      collisionReaction = CollisionType::BOUNCE;

    }
  }
  //used for right collisions
  else if (currentPosition == CollisionPosition::RIGHT)
  {
    if (m_pBuilding->getBuildingType() == BuildingType::BUILDING1)
    {

      position1 = -260;
      position2 = 500;
      position3 = -260;
      position4 = -500;
      selectedType = 0;
      collisionReaction = CollisionType::BOUNCE;

    }

    else if (m_pBuilding->getBuildingType() == BuildingType::BUILDING2)
    {
      position1 = -260;
      position2 = 500;
      position3 = -260;
      position4 = -500;
      selectedType = 0;
      collisionReaction = CollisionType::BOUNCE;

    }

    else if (m_pBuilding->getBuildingType() == BuildingType::BUILDING3)
    {
      position1 = -260;
      position2 = 500;
      position3 = -260;
      position4 = -230;
      selectedType = 0;
      collisionReaction = CollisionType::BOUNCE;

    }

    else if (m_pBuilding->getBuildingType() == BuildingType::BUILDING4)
    {
      position1 = -260;
      position2 = 500;
      position3 = -260;
      position4 = -300;
      selectedType = 0;
      collisionReaction = CollisionType::BOUNCE;

    }

    else if (m_pBuilding->getBuildingType() == BuildingType::HOUSE)
    {
      position1 = -260;
      position2 = 500;
      position3 = -260;
      position4 = -100;
      selectedType = 0;
      collisionReaction = CollisionType::BOUNCE;

    }

    else if (m_pBuilding->getBuildingType() == BuildingType::FUELBUILDING)
    {
      position1 = -260;
      position2 = 500;
      position3 = -260;
      position4 = -100;
      selectedType = 1;
      collisionReaction = CollisionType::BOUNCE;

    }
  }

}