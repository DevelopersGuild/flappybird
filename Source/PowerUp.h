#ifndef FLAPPYBIRD_POWERUP
#define FLAPPYBIRD_POWERUP

#include <SFML/Graphics.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

/*Note: Power up effects (int)
		0 = Double score for 5 seconds
		1 = ...
*/
class PowerUp
{
public:
    
    PowerUp();
    
    void update(float seconds, sf::Vector2f point);

	void moveForwards(float pipesVelocity);

    void render(sf::RenderWindow &window);

	void reset();

    void spawnPU(int pipeNumber);

    bool isCollision(sf::Vector2f point);

	int getPowerUpType();

	void checkDuration();

	void setSpawnPowerUp();
    
private:

	sf::Texture powerUpTexture;
	sf::Sprite powerUpSprite;

	float velocity;
	float pu_frame_timer;  //set frames (like bird's wings) for powerup?
	int y_pos;
	float totalTime;
	int effect;
	float powDuration;

	sf::SoundBuffer PUCollectBuffer;
	sf::Sound PUCollect;
	
};

#endif
