#ifndef FLAPPYBIRD_POWERUP
#define FLAPPYBIRD_POWERUP

#include <SFML/Graphics.hpp>
#include "GameSound.h"
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <string>

/*Note: Power up effects (int)
		0 = Double score for 5 seconds
		1 = Shrink pipes for 5 seconds
		2 = Infinite Boost for 4 seconds
		3 = InvinciBird for 4 seconds
*/
class PowerUp
{
public:
    
    PowerUp();
    
    void update(float seconds, sf::Vector2f point);

	void moveForwards(float pipesVelocity);

    void render(sf::RenderWindow &window);

	void reset();

    bool isCollision(sf::Vector2f point);

	int getPowerUpType();

	void setDuration();

	void checkDuration(float seconds);

	void setSpawnPowerUp();

	void setPowerName();
    
private:

	sf::Texture powerUpTexture;
	sf::Sprite powerUpSprite;

	sf::Font font;
	sf::Text PU_Type;
	sf::Text PU_Duration;

	float velocity;
	float pu_frame_timer;  //set frames (like bird's wings) for powerup?
	int y_pos;
	float totalTime;
	int effect;
	float powDuration;
	float durationPassed;

	sf::SoundBuffer PUCollectBuffer;
	sf::Sound PUCollect;
};

#endif
