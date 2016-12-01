

#include "userInterface.h"
#include "gamecode.h"
#include "BulletUI.h"
#include "BombUI.h"

//////////////////////////////////////////////
/////////UserInterface///////////////////////
/////////////////////////////////////////////
void userInterface::Intialise(Spaceship *player)
{

  scoreAdded = false;
  m_drawDepth = 20;
  m_pPlayer = player;

  ifstream myfile("scores.sav");
  if (myfile.is_open())
  {
    myfile >> score[0] >> score[1] >> score[2] >> score[3] >> score[4];
    myfile.close();
  }

  for (int i = 0; i < 5; i++)
  {
 
    scores.push_back(std::stoi(score[i]));
  }
  
  BulletUI* pBulletUI = new BulletUI;
  pBulletUI->Initialise(m_pPlayer, 0, -1500, 0);
  Game::instance.m_objects.AddItem(pBulletUI, true);

  BulletUI* pHealthUI = new BulletUI;
  pHealthUI->Initialise(m_pPlayer, 9, -2000, 1);
  Game::instance.m_objects.AddItem(pHealthUI, true);

  BulletUI* pFuelUI = new BulletUI;
  pFuelUI->Initialise(m_pPlayer, 18, -1700, 2);
  Game::instance.m_objects.AddItem(pFuelUI, true);

  BombUI* pBombUI = new BombUI;
  pBombUI->Initialise(m_pPlayer,-1000);
  Game::instance.m_objects.AddItem(pBombUI, true);
}

void userInterface::Update(float frameTime)
{
  if (m_pPlayer->isGameOver() == false)
  {
    scoreAdded = false;
  }



}

IShape2D& userInterface::GetCollisionShape()
{

  return m_collider;
}

void userInterface::Draw()
{


  if (m_pPlayer->isGameOver() == false)
  {
    MyDrawEngine::GetInstance()->WriteText(800, 0, L"Score=", MyDrawEngine::WHITE);
    MyDrawEngine::GetInstance()->WriteInt(1250, 0, m_pPlayer->getScore(), MyDrawEngine::WHITE);
  }




    //}
    //MyDrawEngine::GetInstance()->WriteDouble(350, 400, m_pPlayer->getAngle(), MyDrawEngine::WHITE);



    if (m_pPlayer->isGameOver() == true)
    {
      if (scoreAdded == false)
      {
        bool inserted = false;

        for (int i = 0; i < 5; i++)
        {
          newestScore = m_pPlayer->getScore();
          if (!inserted)
          {
            if (scores[i] <= newestScore)
            {
              scores.insert(scores.begin()+ i, newestScore);
              inserted = true;
              scores.pop_back();
            }
          }
        }
        scoreAdded = true;
        remove("scores.txt");

      }

      MyDrawEngine::GetInstance()->WriteText(800, 500, L"Game Over", MyDrawEngine::WHITE);
      //MyDrawEngine::GetInstance()->WriteInt(800, 600, m_pPlayer->getScore(), MyDrawEngine::WHITE);
      MyDrawEngine::GetInstance()->WriteInt(800, 300, scores[0], MyDrawEngine::WHITE);
      MyDrawEngine::GetInstance()->WriteInt(800, 400, scores[1], MyDrawEngine::WHITE);
      MyDrawEngine::GetInstance()->WriteInt(800, 600, scores[2], MyDrawEngine::WHITE);
      MyDrawEngine::GetInstance()->WriteInt(800, 700, scores[3], MyDrawEngine::WHITE);
      MyDrawEngine::GetInstance()->WriteInt(800, 800, scores[4], MyDrawEngine::WHITE);

      ofstream outFile("scores.sav");
      if (outFile.is_open())
      {
        outFile << scores[0] << "\n" << scores[1] << "\n" << scores[2] << "\n" << scores[3] << "\n"
          << scores[4] << "\n";
        outFile.close();
      }
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

