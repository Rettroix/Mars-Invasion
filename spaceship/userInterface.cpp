#include "userInterface.h"

//////////////////////////////////////////////
/////////UserInterface///////////////////////
/////////////////////////////////////////////
void userInterface::Intialise(Spaceship *player)
{
  m_drawDepth = 7;
  m_pPlayer = player;



}

void userInterface::Update(float frameTime)
{


}

IShape2D& userInterface::GetCollisionShape()
{

  return m_collider;
}

void userInterface::Draw()
{
  MyDrawEngine::GetInstance()->WriteText(200, 200, L"Fuel=", MyDrawEngine::WHITE);
  MyDrawEngine::GetInstance()->WriteInt(350, 200, m_pPlayer->getFuel(), MyDrawEngine::WHITE);

  //MyDrawEngine::GetInstance()->WriteText(700, 200, L"Lives:", MyDrawEngine::WHITE);
  /*MyDrawEngine::GetInstance()->WriteDouble(700, 220, global.value[0], MyDrawEngine::WHITE);*/

}
void userInterface::ProcessCollision(GameObject& other)
{
  //nothing
}



userInterface::userInterface() :GameObject(UI)
{

}
