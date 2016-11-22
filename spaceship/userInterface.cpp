#include "userInterface.h"
#include "gamecode.h"
#include "BulletUI.h"

//////////////////////////////////////////////
/////////UserInterface///////////////////////
/////////////////////////////////////////////
void userInterface::Intialise(Spaceship *player)
{
  m_drawDepth = 20;
  m_pPlayer = player;

  BulletUI* pBulletUI = new BulletUI;
  pBulletUI->Initialise(m_pPlayer, 0, -1500, 0);
  Game::instance.m_objects.AddItem(pBulletUI, true);

  BulletUI* pHealthUI = new BulletUI;
  pHealthUI->Initialise(m_pPlayer, 9, -2000, 1);
  Game::instance.m_objects.AddItem(pHealthUI, true);

  BulletUI* pFuelUI = new BulletUI;
  pFuelUI->Initialise(m_pPlayer, 18, -1700, 2);
  Game::instance.m_objects.AddItem(pFuelUI, true);

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

  if (m_pPlayer->isGameOver() == false)
  {
    MyDrawEngine::GetInstance()->WriteText(200, 200, L"Score=", MyDrawEngine::WHITE);
    MyDrawEngine::GetInstance()->WriteInt(350, 200, m_pPlayer->getScore(), MyDrawEngine::WHITE);

  }

  if (m_pPlayer->isGameOver() == true)
  {
    MyDrawEngine::GetInstance()->WriteText(800, 500, L"Game Over", MyDrawEngine::WHITE);
    MyDrawEngine::GetInstance()->WriteInt(800, 600, m_pPlayer->getScore(), MyDrawEngine::WHITE);


  }
  //MyDrawEngine::GetInstance()->WriteDouble(1000, 200, m_pPlayer->getPosition().XValue, MyDrawEngine::WHITE);
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

