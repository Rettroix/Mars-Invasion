//Title     : BUlletUI.cpp
//Purpose   : Can be used as an interface for anything not
//            just bullets
//Author    : Elliot Anderson
//Date      : 5/12/16

#include "BulletUI.h"
#include "gamecode.h"

void BulletUI::Initialise(Spaceship *player, int startingFrame, int selected, int selectUI)
{
  //pointer to player
  m_pPlayer = nullptr;

  //draw depth 11 since it needs to be high up on screen
  m_drawDepth = 11;
  //set the ui to selected ui type
  m_uiType = selectUI;
  //check if player is null pointer
  if (m_pPlayer == nullptr)
  {
    //set pointer to player
    m_pPlayer = player;
  }
  //the image number is set to the starting frame which tells
  //which user interface to use,0 for bullets, 9 for health and
  //18 for fuel
  m_imageNumber = startingFrame;
  //Set's the first frame to the starting frame
  m_firstFrame = startingFrame;
  //set position to 0
  m_position = Vector2D(0, 0);

  //If the UI type is 0 it means we are using the bullet user
  //interface
  if (m_uiType == 0)
  {
    //max bullets is set to the players max bullets
    m_maxBullets = m_pPlayer->getMaxBullets();
  }

  //If the UI type is 1 it means we are using the health user
  //interface
  if (m_uiType == 1)
  {
    //max health is set to the players max bullets
    m_maxHealth = m_pPlayer->getMaxHealth();
  }


  //If the UI type is 2 it means we are using the fuel user
  //fuel 
  if (m_uiType == 2)
  {
    //max fuel is set to the players max fuel
    m_maxFuel = m_pPlayer->getMaxFuel();
  }
  
  //set the size of the object
  m_objectSize = Vector2D(64, 64) * 100;

  //selected is how far along the screen the user interface is drawn
  m_positionAlong = selected;
  
  //Load all the bullet images
  LoadImage(L"UIbullets1.png");
  LoadImage(L"UIbullets2.png");
  LoadImage(L"UIbullets3.png");
  LoadImage(L"UIbullets4.png");
  LoadImage(L"UIbullets5.png");
  LoadImage(L"UIbullets6.png");
  LoadImage(L"UIbullets7.png");
  LoadImage(L"UIbullets8.png");
  LoadImage(L"UIbullets9.png");
  //Load all the health images
  LoadImage(L"UIhealth1.png");
  LoadImage(L"UIhealth2.png");
  LoadImage(L"UIhealth3.png");
  LoadImage(L"UIhealth4.png");
  LoadImage(L"UIhealth5.png");
  LoadImage(L"UIhealth6.png");
  LoadImage(L"UIhealth7.png");
  LoadImage(L"UIhealth8.png");
  LoadImage(L"UIhealth9.png");
  //Load all the fuel images
  LoadImage(L"UIFuel001.png");
  LoadImage(L"UIFuel002.png");
  LoadImage(L"UIFuel003.png");
  LoadImage(L"UIFuel004.png");
  LoadImage(L"UIFuel005.png");
  LoadImage(L"UIFuel006.png");
  LoadImage(L"UIFuel007.png");
  LoadImage(L"UIFuel008.png");
  LoadImage(L"UIFuel009.png");



}//end Initialise

void BulletUI::Update(float frameTime)
{
  //position is set to the players position plus how far along it is set
  m_position = m_pPlayer->GetPosition() + Vector2D(m_positionAlong, 900);
  //Bullet ammount is set
  if (m_uiType == 0)
  {
    m_bulletAmmount = m_pPlayer->getBullets();
  }

  //health ammount is set
  if (m_uiType == 1)
  {
    m_healthAmmount = m_pPlayer->getHealth();
  }

  //fuel ammount is set
  if (m_uiType == 2)
  {
    m_fuelAmmount = m_pPlayer->getFuel();
  }
  
  //max values are always divided by 8 as there are 8 segments in
  //the circle
  int a = m_maxBullets / 8;
  int b = m_maxHealth / 8;
  int c = m_maxFuel / 8;

  //increments the ui's image frame based on the ammount of bullets
  //and max bullets
  if (m_uiType == 0)
  {
    frameIncrementer(m_bulletAmmount, a);
  }
  //increments the ui's image frame based on the ammount of health
  //and max health
  if (m_uiType == 1)
  {
    frameIncrementer(m_healthAmmount, b);
  }
  //increments the ui's image frame based on the ammount of fuel
  //and max fuel
  if (m_uiType == 2)
  {
    frameIncrementer(m_fuelAmmount, c);
  }

}//end update

IShape2D& BulletUI::GetCollisionShape()
{

  return m_collider;
}//end GetCollisionShape

void BulletUI::Draw()
{
  GameObject::Draw();
  MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();


}// end Draw
void BulletUI::ProcessCollision(GameObject& other)
{
  //nothing
}//end ProcessCollision

void BulletUI::frameIncrementer(int ammount, int a)
{
  //sets the image number based on first frame added + specific ammount
  //
  //a is max value /8 so multiplying it by how many segments are filled
  //should give the right ammount of filled segments
  if (ammount <= 0)
  {
    m_imageNumber = m_firstFrame + 8;
  }

  else if (ammount < (a * 1))
  {
    m_imageNumber = m_firstFrame + 7;
  }

  else if (ammount < (a * 2))
  {
    m_imageNumber = m_firstFrame + 6;
  }

  else if (ammount < (a * 3))
  {
    m_imageNumber = m_firstFrame + 5;
  }

  else if (ammount < (a * 4))
  {
    m_imageNumber = m_firstFrame + 4;
  }

  else if (ammount < (a * 5))
  {
    m_imageNumber = m_firstFrame + 3;
  }

  else if (ammount < (a * 6))
  {
    m_imageNumber = m_firstFrame + 2;
  }

  else if (ammount < (a * 7))
  {
    m_imageNumber = m_firstFrame + 1;
  }

  else if (ammount < (a * 8))
  {
    m_imageNumber = m_firstFrame;
  }
}//end frameIncrementer

BulletUI::BulletUI() :GameObject(UI)
{

}//end BulletUI

