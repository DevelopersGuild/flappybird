#include "Assets.h"
#include "Constants.h"
#include "Bird.h"

Bird::Bird()
	: bird_frame_timer( BIRD_FRAME_DURATION ), bird_y_pos( 0 ), bird_x_pos( 0 )
{
	birdTexture.loadFromFile(GetAssetPath("Assets", "NewBird.png")); //Loads sprite sheet as texture

	birdSprite.setTexture(birdTexture);  // sets texture of sprite to the sprite sheet
	birdSprite.setTextureRect(sf::IntRect(0, 0, 110.2, 101.333));
}

void Bird::update(float seconds)
{
	bird_frame_timer -= seconds;
}

void Bird::render(sf::RenderWindow &window)
{
	if( bird_y_pos*101 >= birdTexture.getSize().y )
	{
			bird_y_pos = 0;
	}
	
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
		bird_frame_timer = BIRD_FRAME_DURATION;
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
	// This should be changed to return the bird's actual position
    return sf::Vector2f();
}

/**
 * Add additional things.
 */
