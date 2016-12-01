#include "SoundFX.h"
#include "gamecode.h"


SoundFX::SoundFX()
{
  m_NextExplosion = 0;
  m_NextZap = 0;

  for (int i = 0; i < NUMEXPLOSIONSOUNDS; i++)
  {
    m_Explosions[i] = 0;		// Not loaded yet
  }
  m_Thrust = 0;				// Not loaded yet
  for (int i = 0; i < NUMZAPSOUNDS; i++)
  {
    m_Zaps[i] = 0;		// Not loaded yet
  }
}

void SoundFX::LoadSounds()
{
  // Get the pointer to the sound engine
  MySoundEngine* pSoundEngine = MySoundEngine::GetInstance();

  // Load the explosions sounds
  for (int i = 0; i < NUMEXPLOSIONSOUNDS; i++)
  {
    // If sounds are currently loaded, no need to load them again
    if (m_Explosions[i] == 0)
    {
      switch (i % 5)		// Only 5 wave sounds
      {
      case 0:
        m_Explosions[i] = pSoundEngine->LoadWav(L"explosion1.wav");
        break;
      case 1:
        m_Explosions[i] = pSoundEngine->LoadWav(L"explosion2.wav");
        break;
      case 2:
        m_Explosions[i] = pSoundEngine->LoadWav(L"explosion3.wav");
        break;
      case 3:
        m_Explosions[i] = pSoundEngine->LoadWav(L"explosion4.wav");
        break;
      case 4:
        m_Explosions[i] = pSoundEngine->LoadWav(L"explosion5.wav");
        break;
      }
    }

  }
  // Load the thrust sound, as long as not already loaded
  if (m_Thrust == 0)
  {
    m_Thrust = pSoundEngine->LoadWav(L"thrustloop2.wav");
  }

  if (m_BGM == 0)
  {
    m_BGM = pSoundEngine->LoadWav(L"bgm.wav");
  }

  // Load the zap sounds.
  // Identical wave files, but neet multiple copies in case we need to plau
  // one before the other has finished
  for (int i = 0; i < NUMZAPSOUNDS; i++)
  {
    // If sounds are currently loaded, no need to load them again
    if (m_Zaps[i] == 0)
    {
      m_Zaps[i] = pSoundEngine->LoadWav(L"zap2.wav");
    }
  }
}

void SoundFX::PlayZap()
{
  // Play the sound
  MySoundEngine::GetInstance()->Play(m_Zaps[m_NextZap]);
  // Move on to the next sound
  ++m_NextZap;
  if (m_NextZap >= NUMZAPSOUNDS)
    m_NextZap = 0;
}

void SoundFX::PlayExplosion()
{
  // Play the sound
  MySoundEngine::GetInstance()->Play(m_Explosions[m_NextExplosion]);
  m_NextExplosion += rand() % 3;			// Stops it sounding too repetitive
  if (m_NextExplosion >= NUMEXPLOSIONSOUNDS)
    m_NextExplosion = 0;
}

void SoundFX::StartThrust()
{
  // Play thrust in a loop
  MySoundEngine::GetInstance()->Play(m_Thrust, true);
}

void SoundFX::StopThrust()
{
  // Stop the thrust loop
  MySoundEngine::GetInstance()->Stop(m_Thrust);
}
