#include "Assets.h"
#include "GameSound.h"

static GameSound instance;

GameSound::GameSound()
{
	midGameMusic.openFromFile(GetAssetPath("Assets/MidGame.ogg"));
	midGameMusic.setVolume(20);
	midGameMusic.setLoop(true);
	
	preGameMusic.openFromFile(GetAssetPath("Assets/PreGame.ogg"));
	preGameMusic.setLoop(true);
	preGameMusic.setVolume(20);

	scoredPointBuffer.loadFromFile(GetAssetPath("Assets/ScoredPoint.ogg"));
	scoredPointSound.setBuffer(scoredPointBuffer);
	scoredPointSound.setVolume(50);

	birdCollisionBuffer.loadFromFile(GetAssetPath("Assets/BirdDies.ogg"));
	birdCollisionSound.setBuffer(birdCollisionBuffer);

	boostBuffer.loadFromFile(GetAssetPath("Assets/Boost.ogg"));
	boostSound.setBuffer(boostBuffer);

	powerUpCollectBuffer.loadFromFile(GetAssetPath("Assets/PUCollect.ogg"));
	powerUpCollectSound.setBuffer(powerUpCollectBuffer);
}

void GameSound::preGameMusicOn()
{
	instance.preGameMusic.play();
}

void GameSound::preGameMusicOff()
{
	instance.preGameMusic.stop();
}

void GameSound::midGameMusicOn()
{
	instance.midGameMusic.play();
}

void GameSound::midGameMusicOff()
{
	instance.midGameMusic.stop();
}

void GameSound::scoredPoint()
{
	instance.scoredPointSound.play();
}

void GameSound::birdCollision()
{
	instance.birdCollisionSound.play();
}

void GameSound::powerUpCollect()
{
	instance.powerUpCollectSound.play();
}

void GameSound::boost()
{
	instance.boostSound.play();
}