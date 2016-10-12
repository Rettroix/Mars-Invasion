#include "BuildingBackground.h"

//////////////////////////////////////////////////////
//////////////BuildingBackground//////////////////////
//////////////////////////////////////////////////////

void BuildingBackground::Initialise(Vector2D startPosition, Spaceship *player)
{
  m_pPlayer = player; //Stores a pointer to the player
  m_drawDepth = 1; //Buildings are in the background thus have a low draw depth

  LoadImage(L"city.png"); //The image for the background

  m_position = startPosition; //m_position becomes the specified starting position

  incrementFrame = 0; //uneeded
  initialPosition = m_position; //Stores the original position for paralax scrolling
  m_imageScale = 9; //scales image up since it needs to be big
}

void BuildingBackground::Update(float frameTime)
{
  m_imageNumber = 0;

  m_position = initialPosition - Vector2D(m_pPlayer->getPosition().XValue*0.5, 0); //The position is always the initial position minus the player's position times the value needed for scrolling
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

Vector2D BuildingBackground::getInitialPosition()
{
  return initialPosition;
  

}

BuildingBackground::BuildingBackground() :GameObject(BUILDING)
{

}