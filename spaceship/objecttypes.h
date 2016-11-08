#pragma once


// List of object types available in the game
// Add a name for each possible type of entity in your game
// Still using old enums until C++11 is available

enum ObjectType{UNKNOWN, SPACESHIP, PING, BUILDING, LEVEL, BULLET, UI, EXPLOSION, BUILDINGSIDE, COLLIDER, LANDER, FLOOR};

enum class CollisionType{BOUNCE, LANDER, FUELANDER};

enum class CollisionPosition{ LEFT, TOP, RIGHT };