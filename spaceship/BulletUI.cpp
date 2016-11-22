#include "BulletUI.h"
#include "gamecode.h"

//////////////////////////////////////////////
/////////BulletUI///////////////////////
/////////////////////////////////////////////
void BulletUI::Initialise(Spaceship *player, int startingFrame, int selected, int selectUI)
{
  ////CHECK POINTERS NULL
  m_drawDepth = 11;
  uiType = selectUI;
  m_pPlayer = player;
  m_imageNumber = startingFrame;
  m_position = Vector2D(0, 0);

  //Bullets
  if (uiType == 0)
  {
    maxBullets = m_pPlayer->getMaxBullets();
  }

  //Health
  if (uiType == 1)
  {
    maxHealth = m_pPlayer->getMaxHealth();
  }


  //Fuel
  if (uiType == 2)
  {
    maxFuel = m_pPlayer->getMaxFuel();
  }
  
  m_objectSize = Vector2D(64, 64) * 100;
  firstFrame = startingFrame;
  positionAlong = selected;
  LoadImage(L"UIbullets1.png");
  LoadImage(L"UIbullets2.png");
  LoadImage(L"UIbullets3.png");
  LoadImage(L"UIbullets4.png");
  LoadImage(L"UIbullets5.png");
  LoadImage(L"UIbullets6.png");
  LoadImage(L"UIbullets7.png");
  LoadImage(L"UIbullets8.png");
  LoadImage(L"UIbullets9.png");

  LoadImage(L"UIhealth1.png");
  LoadImage(L"UIhealth2.png");
  LoadImage(L"UIhealth3.png");
  LoadImage(L"UIhealth4.png");
  LoadImage(L"UIhealth5.png");
  LoadImage(L"UIhealth6.png");
  LoadImage(L"UIhealth7.png");
  LoadImage(L"UIhealth8.png");
  LoadImage(L"UIhealth9.png");

  LoadImage(L"UIFuel001.png");
  LoadImage(L"UIFuel002.png");
  LoadImage(L"UIFuel003.png");
  LoadImage(L"UIFuel004.png");
  LoadImage(L"UIFuel005.png");
  LoadImage(L"UIFuel006.png");
  LoadImage(L"UIFuel007.png");
  LoadImage(L"UIFuel008.png");
  LoadImage(L"UIFuel009.png");



}

void BulletUI::Update(float frameTime)
{
  m_position = m_pPlayer->GetPosition() + Vector2D(positionAlong, 900);
  //Bullets
  if (uiType == 0)
  {
    bulletAmmount = m_pPlayer->getBullets();
  }

  //health
  if (uiType == 1)
  {
    healthAmmount = m_pPlayer->getHealth();
  }

  if (uiType == 2)
  {
    fuelAmmount = m_pPlayer->getFuel();
  }
  
  int a = maxBullets / 8;
  int b = maxHealth / 8;
  int c = maxFuel / 8;
  if (uiType == 0)
  {
    frameIncrementer(bulletAmmount, a);
  }

  if (uiType == 1)
  {
    frameIncrementer(healthAmmount, b);
  }
  
  if (uiType == 2)
  {
    frameIncrementer(fuelAmmount, c);
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

void BulletUI::frameIncrementer(int ammount, int a)
{
  if (ammount <= 0)
  {
    m_imageNumber = firstFrame + 8;
  }

  else if (ammount < (a * 1))
  {
    m_imageNumber = firstFrame + 7;
  }

  else if (ammount < (a * 2))
  {
    m_imageNumber = firstFrame + 6;
  }

  else if (ammount < (a * 3))
  {
    m_imageNumber = firstFrame + 5;
  }

  else if (ammount < (a * 4))
  {
    m_imageNumber = firstFrame + 4;
  }

  else if (ammount < (a * 5))
  {
    m_imageNumber = firstFrame + 3;
  }

  else if (ammount < (a * 6))
  {
    m_imageNumber = firstFrame + 2;
  }

  else if (ammount < (a * 7))
  {
    m_imageNumber = firstFrame + 1;
  }

  else if (ammount < (a * 8))
  {
    m_imageNumber = firstFrame;
  }
}

BulletUI::BulletUI() :GameObject(UI)
{

}

