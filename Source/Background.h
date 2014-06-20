#ifndef FLAPPYBIRD_BACKGROUND
#define FLAPPYBIRD_BACKGROUND

#include <SFML/Graphics.hpp>
#include "Constants.h"


class Background
{
public:
	Background();

	void update(float seconds);

	void render(sf::RenderWindow &window);

	void moveForwards();

	void reset();
private:

	float background_X_pos;
	float background_x_pos_increment;
	float velocity;

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite[2];
};

#endif