#pragma once

#include "GameObject.h"
#include "mysoundengine.h"
#include "GameObject.h"
#include "Spaceship.h"
#include "Building.h"
#include "BuildingTypes.h"

//The lander is a class which was created to position landing pads on the buildings
//but decided to just use the class for every collision wall
//Each lander is designated a building pointer so that the collision shape can 
//change as the buildings type changes
class Lander : public GameObject
{
private:
  Segment2D collisionShape;
  Building *m_pBuilding;
  float position1;
  float position2;
  float position3;
  float position4;
  int selectedType; //selected if it gives you fuel  
  CollisionType collisionReaction;  //Sets whether the player bounces or lands
  CollisionPosition currentPosition; //sets which side the wall is
public:

  void Initialise(Building *pBuilding, float pos1, float pos2, float pos3, float pos4, int coltype, CollisionPosition colpos, CollisionType colReac);
  void Draw();
  void becomeBuilding();  //changes collision shape based on the building
  void Update(float frameTime);
  IShape2D& GetCollisionShape();
  float GetTop(); //Gets the top of the segment
  int GetColType(); //returns the collision type whether it bounces or lands
  CollisionType getCollisionReaction();
  void ProcessCollision(GameObject& other);
  Segment2D GetShape();
  Lander();
};