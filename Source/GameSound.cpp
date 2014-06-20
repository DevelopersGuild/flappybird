#include "Assets.h"
#include "GameSound.h"

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
	preGameMusic.play();
}

void GameSound::preGameMusicOff()
{
	preGameMusic.stop();
}

void GameSound::midGameMusicOn()
{
	midGameMusic.play();
}

void GameSound::midGameMusicOff()
{
	midGameMusic.stop();
}

void GameSound::scoredPoint()
{
	scoredPointSound.play();
}

void GameSound::birdCollision()
{
	birdCollisionSound.play();
}

void GameSound::powerUpCollect()
{
	powerUpCollectSound.play();
}

void GameSound::boost()
{
	boostSound.play();
}