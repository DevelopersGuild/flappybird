#include "Assets.h"
#include "Constants.h"
#include "Bird.h"

Bird::Bird()
	: bird_frame_timer( BIRD_FRAME_DURATION ), bird_y_pos( 0 ), bird_x_pos( 0 )
{
	birdTexture.loadFromFile(GetAssetPath("Assets", "NewBird.png")); //Loads sprite sheet as texture
	birdSprite.setTexture(birdTexture);  // sets texture of sprite to the sprite sheet
	birdSprite.setTextureRect(sf::IntRect(0, 0, 110.2, 101.333));
	velocity = 0;
	rotation = 0;
	maxY = 100.f;
}

void Bird::update(float seconds)
{
	bird_frame_timer -= seconds;
	velocity += GRAVITY * seconds;
	if(rotation <= 45)
		rotation += 1.5;
	birdSprite.setPosition(50, birdSprite.getPosition().y + velocity * seconds);
	birdSprite.setRotation(rotation);
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
	velocity = BIRD_JUMP_VELOCITY;
	rotation = 1; 
}

sf::Vector2f Bird::getPosition()
{
	// This should be changed to return the bird's actual position
    return sf::Vector2f();
}

/**
 * Add additional things.
 */
