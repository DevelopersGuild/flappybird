#ifndef FLAPPYBIRD_GAMESOUND
#define FLAPPYBIRD_GAMESOUND

#include <SFML/Audio.hpp>


class GameSound
{
public:
	GameSound();

	void preGameMusicOn();
	void preGameMusicOff();

	void midGameMusicOn();
	void midGameMusicOff();

	void scoredPoint();

	void birdCollision();

	void powerUpCollect();

	void boost();
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