#ifndef FLAPPYBIRD_ARROWS
#define FLAPPYBIRD_ARROWS

#include <SFML/Graphics.hpp>
#include "Score.h"

class Arrows
{
public:
	Arrows();
	void update(float seconds);
	void render(sf::RenderWindow &window, bool on);
	void reset();

private:
	sf::Texture arrowOffTexture;
	sf::Sprite arrowOffSprite;
	sf::Texture arrowOnTexture;
	sf::Sprite arrowOnSprite;

	int moveArrow;
	Score score;
};

#endif