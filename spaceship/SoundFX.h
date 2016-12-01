#pragma once

#include "GameObject.h"
#include "mysoundengine.h"
#include "GameObject.h"

class SoundFX
{

private:
  static const int NUMEXPLOSIONSOUNDS = 5;
  static const int NUMZAPSOUNDS = 3;
  SoundIndex m_Explosions[NUMEXPLOSIONSOUNDS];	// Explosion sounds
  SoundIndex m_Thrust;				// Engine thrust sound
  SoundIndex m_Zaps[NUMZAPSOUNDS];		// Zap sounds
  SoundIndex m_BGM;
  //  -- three copies since it is fiddly to play
  //  the same sound simultanously.
  int m_NextZap;				// The number of the next zap sound to play
  int m_NextExplosion;		// The number of the next explosion sound to play
public:
  SoundFX();
  void LoadSounds();
  void PlayZap();
  void PlayExplosion();
  void StartThrust();
  void StopThrust();
};