#include "Assets.h"
#include "Constants.h"
#include "Bird.h"

Bird::Bird()
{
	float bird_frame_timer = BIRD_FRAME_DURATION;
	sf::Texture birdTexture;

	birdTexture.loadFromFile(GetAssetPath("Assets", "NewBird.png")); //Loads sprite sheet as texture

	sf::Sprite birdSprite;
	birdSprite.setTexture(birdTexture);  // sets texture of sprite to the sprite sheet
    
	birdSprite.setTextureRect(sf::IntRect(0, 0, 110.2, 101.333));
	bird_y_pos = 0;
	bird_x_pos = 0;
    
    sf::Clock clock; // starts the clock
}

void Bird::update(float seconds)
{
}

void Bird::render(sf::RenderWindow &window)
{
	sf::Time elapsed = clock.getElapsedTime();
	bird_frame_timer -= elapsed.asSeconds();
	clock.restart();

	if(bird_y_pos*101 >= birdTexture.getSize().y)
			bird_y_pos = 0;
	    if(bird_x_pos*110 >= birdTexture.getSize().x - 110)
		{
			bird_x_pos = 0;
			bird_y_pos++;
		}

		if(bird_y_pos == 2 && bird_x_pos == 4)
		{
			bird_x_pos = 0;
			bird_y_pos = 0;
		}

		if(bird_frame_timer <= 0)
		{
			birdSprite.setTextureRect(sf::IntRect(bird_x_pos*110, bird_y_pos*102, 111, 101));
			bird_x_pos++;
			bird_frame_timer =BIRD_FRAME_DURATION;
		}
	window.draw(birdSprite);
}

void Bird::reset()
{
}

void Bird::jump()
{
}

sf::Vector2f Bird::getPosition()
{
    return sf::Vector2f();
}

/**
 * Add additional things.
 */
