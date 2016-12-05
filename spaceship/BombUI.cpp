#include "BombUI.h"
#include "gamecode.h"

//////////////////////////////////////////////
////////////////BombUI///////////////////////
/////////////////////////////////////////////
void BombUI::Initialise(Spaceship *player, int offset)
{
  m_pPlayer = nullptr;

  if (m_pPlayer == nullptr)
  {
    m_pPlayer = player;
  }

  m_drawDepth = 11;   
  m_imageNumber = 0;
  m_position = Vector2D(0, 0);
  positionAlong = offset; //where the ui element is places relative to the player


  //m_objectSize = Vector2D(64, 64) * 100;
  LoadImage(L"bomb_bar.png");
  LoadImage(L"bomb_bar2.png");
  LoadImage(L"bomb_bar3.png");
  LoadImage(L"bomb_bar4.png");
  LoadImage(L"bomb_bar5.png");
  LoadImage(L"bomb_bar6.png");






}

void BombUI::Update(float frameTime)
{
  //updates position relative to player position
  m_position = m_pPlayer->GetPosition() + Vector2D(positionAlong, 900);


  //Set's the image number based on the players bomb counter
  if (m_pPlayer->getBombCounter() == 0)
  {
    m_imageNumber = 0;
  }
  else if (m_pPlayer->getBombCounter() == 1)
  {
    m_imageNumber = 1;

  }
  else if (m_pPlayer->getBombCounter() == 2)
  {
    m_imageNumber = 2;

  }
  else if (m_pPlayer->getBombCounter() == 3)
  {
    m_imageNumber = 3;

  }
  else if (m_pPlayer->getBombCounter() == 4)
  {
    m_imageNumber = 4;

  }
  else if (m_pPlayer->getBombCounter() == 5)
  {
    m_imageNumber = 5;

  }
  else if (m_pPlayer->getBombCounter() == 6)
  {
    m_imageNumber = 6;

  }

}

IShape2D& BombUI::GetCollisionShape()
{

  return m_collider;
}

void BombUI::Draw()
{
  GameObject::Draw();
  MyDrawEngine* pTheDrawEngine = MyDrawEngine::GetInstance();


}
void BombUI::ProcessCollision(GameObject& other)
{
  //nothing
}



BombUI::BombUI() :GameObject(UI)
{

}

