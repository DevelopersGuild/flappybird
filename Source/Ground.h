#ifndef FLAPPYBIRD_GROUND
#define FLAPPYBIRD_GROUND

#include <SFML/Graphics.hpp>
#include "Constants.h"

class Ground
{
public:
    //Constructor
    Ground();

	//Draw all the ground sprites. Does not change any values.
    void render(sf::RenderWindow &window);

	//Updates the position of the ground sprites due to time.
    void update(float seconds);

	//
    void reset();

	void moveForwards();
private:
		sf::Texture groundTexture;
		sf::Sprite groundSprite[NUMBER_OF_GROUND_SPRITES];

		float velocity;
};

#endif
