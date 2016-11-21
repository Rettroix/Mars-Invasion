#include "BulletUI.h"
#include "gamecode.h"

//////////////////////////////////////////////
/////////BulletUI///////////////////////
/////////////////////////////////////////////
void BulletUI::Initialise(Spaceship *player)
{
  m_drawDepth = 11;
  m_pPlayer = player;
  m_imageNumber = 0;
  m_position = Vector2D(0, 0);
  maxBullets = m_pPlayer->getMaxBullets();
  m_objectSize = Vector2D(64, 64) * 100;
  LoadImage(L"UIbullets1.png");
  LoadImage(L"UIbullets2.png");
  LoadImage(L"UIbullets3.png");
  LoadImage(L"UIbullets4.png");
  LoadImage(L"UIbullets5.png");
  LoadImage(L"UIbullets6.png");
  LoadImage(L"UIbullets7.png");
  LoadImage(L"UIbullets8.png");
  LoadImage(L"UIbullets9.png");


}

void BulletUI::Update(float frameTime)
{
  m_position = m_pPlayer->GetPosition() + Vector2D(-2000, 900);
  bulletAmmount = m_pPlayer->getBullets();
  int a = maxBullets / 8;

  if (bulletAmmount <= 0)
  {
    m_imageNumber = 8;
  }

  else if (bulletAmmount < (a * 1))
  {
    m_imageNumber = 7;
  }

  else if (bulletAmmount < (a * 2))
  {
    m_imageNumber = 6;
  }

  else if (bulletAmmount < (a * 3))
  {
    m_imageNumber = 5;
  }

  else if (bulletAmmount < (a * 4))
  {
    m_imageNumber = 4;
  }

  else if (bulletAmmount < (a * 5))
  {
    m_imageNumber = 3;
  }

  else if (bulletAmmount < (a * 6))
  {
    m_imageNumber = 2;
  }

  else if (bulletAmmount < (a * 7))
  {
    m_imageNumber = 1;
  }

  else if (bulletAmmount < (a * 8))
  {
    m_imageNumber = 0;
  }
  

}

IShape2D& BulletUI::GetCollisionShape()
{

  return m_collider;
}

void BulletUI::Draw()
{
  GameObject::Draw();
  MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();


}
void BulletUI::ProcessCollision(GameObject& other)
{
  //nothing
}



BulletUI::BulletUI() :GameObject(UI)
{

}

