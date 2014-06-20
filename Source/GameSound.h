#ifndef FLAPPYBIRD_GAMESOUND
#define FLAPPYBIRD_GAMESOUND

#include <SFML/Audio.hpp>


class GameSound
{
public:
	GameSound();

	static void preGameMusicOn();
	static void preGameMusicOff();

	static void midGameMusicOn();
	static void midGameMusicOff();

	static void scoredPoint();

	static void birdCollision();

	static void powerUpCollect();

	static void boost();
private:
	sf::Music preGameMusic;
	sf::Music midGameMusic;

	sf::SoundBuffer scoredPointBuffer;
	sf::Sound scoredPointSound;

	sf::SoundBuffer birdCollisionBuffer;
	sf::Sound birdCollisionSound;
	
	sf::SoundBuffer boostBuffer;
	sf::Sound boostSound;

	sf::SoundBuffer powerUpCollectBuffer;
	sf::Sound powerUpCollectSound;
};

#endif