#include "Assets.h"
#include "Constants.h"
#include "Bird.h"
#include <math.h>
#include <iostream>

using namespace std;

Bird::Bird()
	: bird_frame_timer( BIRD_FRAME_DURATION ), bird_y_pos( 0 ), bird_x_pos( 0 )
{
	birdTexture.loadFromFile(GetAssetPath("Assets/NewBird.png")); //Loads sprite sheet as texture
	birdSprite.setTexture(birdTexture);  // sets texture of sprite to the sprite sheet
	birdSprite.setTextureRect(sf::IntRect(0, 0, BIRD_FRAME_SIZE_X, BIRD_FRAME_SIZE_Y));
	birdSprite.setOrigin(BIRD_FRAME_SIZE_X/2, BIRD_FRAME_SIZE_Y/2);
	velocity = 0;
	rotation = 0;
	birdSprite.setPosition(BIRD_X_POS, 300);
	rotationIncrement = 2;
	jumped = 0;
	animationRemaining = BIRD_JUMP_ANIMATION_TIMER;
}

void Bird::preGameUpdate(float seconds)
{
	bird_frame_timer -= seconds;

	if(bird_frame_timer <= 0.0)
	{
		advanceAnimation();
		bird_frame_timer =  1.5 * BIRD_FRAME_DURATION;
	}
	setAnimationFrame(bird_x_pos, bird_y_pos);
}

void Bird::update(float seconds, float pipes_veloctity)
{
	bird_frame_timer -= seconds;
	animationRemaining -= seconds;
	if (animationRemaining < 0.0)
		animationRemaining = 0.0;
	velocity += GRAVITY * seconds;
	rotation = atan2f(velocity, pipes_veloctity) * 180 / 3.14;
	if(velocity * seconds < 550)
	{
		birdSprite.move(0.0, velocity * seconds);
		birdSprite.setRotation(rotation);
	}

	//if the jump function has been called, reset the bird animation to the first frame
	if(animationRemaining == 0.0)
	{
		bird_x_pos = 0;
		bird_y_pos = 0;
	}
	else
	{
		advanceAnimation();
	}
	setAnimationFrame(bird_x_pos, bird_y_pos);
}

void Bird::render(sf::RenderWindow &window)
{
	window.draw(birdSprite);
}

void Bird::advanceAnimation()
{
	while (bird_frame_timer <= 0)
	{
		bird_x_pos++;
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
		bird_frame_timer += BIRD_FRAME_DURATION;
	}
}

void Bird::setAnimationFrame(int x, int y)
{
	birdSprite.setTextureRect(sf::IntRect(x*110, y*102, 111, 101));
}

void Bird::reset()
{
	birdSprite.setPosition(sf::Vector2f(BIRD_X_POS, 300));
	birdSprite.setRotation(0.0f);
	velocity = 0.0f;
	jumped = 0;
}

void Bird::jump()
{
    velocity = BIRD_JUMP_VELOCITY;
    animationRemaining = BIRD_JUMP_ANIMATION_TIMER;
    bird_x_pos = 0;
    bird_y_pos = 0;
    bird_frame_timer = BIRD_FRAME_DURATION;
    jumped++;
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
    return birdSprite.getPosition();
}