#include "Assets.h"
#include "Constants.h"
#include "Bird.h"
#include <iostream>
using namespace std;

Bird::Bird()
	: bird_frame_timer( BIRD_FRAME_DURATION ), bird_y_pos( 0 ), bird_x_pos( 0 )
{
	birdTexture.loadFromFile(GetAssetPath("Assets", "NewBird.png")); //Loads sprite sheet as texture
	birdSprite.setTexture(birdTexture);  // sets texture of sprite to the sprite sheet
	birdSprite.setTextureRect(sf::IntRect(0, 0, BIRD_FRAME_SIZE_X, BIRD_FRAME_SIZE_Y));
	velocity = 0;
	rotation = 0;
	jumpAnimation = 29;
	rotationIncrement = 2;
}

void Bird::update(float seconds)
{
	bird_frame_timer -= seconds;
	velocity += GRAVITY * seconds;

	if(rotation <= 60)
		rotation += rotationIncrement;
	if(rotation <= 0)
		rotationIncrement = 2;
	birdSprite.setPosition(400, birdSprite.getPosition().y + velocity * seconds);
	birdSprite.setRotation(rotation);
}

void Bird::render(sf::RenderWindow &window)
{
	//if the jump function has been called, reset the bird animation to the first frame
	if(jumpAnimation == 0)
	{
		bird_x_pos = 0;
		bird_y_pos = 0;
	}
	if(jumpAnimation <= 32)
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
		jumpAnimation++;
	}
	window.draw(birdSprite);
}

void Bird::reset()
{
}

void Bird::jump()
{
	if(birdSprite.getPosition().y >= BIRD_MAX_Y) //To make sure the bird doesn't go above the border of the window
	{
		velocity = BIRD_JUMP_VELOCITY;
		//this simply sets the rotation angle to zero degree, which doesn't look smooth. We'll change this later on.
		rotation = -10;
		jumpAnimation = 0;
		jumped = true;
	}
}

void Bird::setRotationIncrement(int number) 
{
	rotationIncrement = number;
}

int Bird::getRotation()
{
	return rotation;
}

sf::Vector2f Bird::getPosition()
{
	// This should be changed to return the bird's actual position
    return sf::Vector2f();
}

/**
 * Add additional things.
 */
