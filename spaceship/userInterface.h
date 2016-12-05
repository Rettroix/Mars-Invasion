#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "GameObject.h"
#include "mysoundengine.h"
#include "GameObject.h"
#include "Spaceship.h"
#include "entities.h"


class userInterface : public GameObject
{
private:
  int newestScore;
  bool scoreAdded;
  vector<int> scores;
  string score[5];
  Vector2D m_velocity;
  float m_time;
  Circle2D m_circle;
  Circle2D m_collider;
  float m_fuel;
  Spaceship *m_pPlayer;
  City *m_pCity;
public:

  void Intialise(Spaceship *player, City *city);

  void Update(float frameTime);
  IShape2D& GetCollisionShape();
  void Draw();
  void ProcessCollision(GameObject& other);
  void addFuel(float fuel);
  userInterface();
};


