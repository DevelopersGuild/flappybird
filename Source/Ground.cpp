#include "Ground.h"
#include "Assets.h"
#include "Constants.h"

Ground::Ground()
{
	groundTexture.loadFromFile(GetAssetPath("Assets/Ground.png"));
	
	for(int i = 0; i < NUMBER_OF_GROUND_SPRITES; i++)
	{
		groundSprite[i].setTexture(groundTexture);
		groundSprite[i].setOrigin(0, 110);
		groundSprite[i].setPosition(GROUND_SPRITE_LENGTH * i, GROUND_Y_POSITION);
	}

	velocity = GROUND_VELOCITY;
}

void Ground::update(float seconds)
{
	if(velocity > GROUND_VELOCITY)
	{
		velocity -= GROUND_DECELERATION * seconds;
	}
	if (velocity < GROUND_VELOCITY)
	{
		velocity = GROUND_VELOCITY;
	}
	for(int i = 0; i < NUMBER_OF_GROUND_SPRITES; i++)
	{
		groundSprite[i].move(-velocity * seconds, 0);
		
		if(groundSprite[i].getPosition().x <= -GROUND_SPRITE_LENGTH)
		{
			groundSprite[i].move(4*GROUND_SPRITE_LENGTH, 0);
		}
	}
}

void Ground::render(sf::RenderWindow &window)
{
	for(int i = 0; i < NUMBER_OF_GROUND_SPRITES; i++)
	{
		window.draw(groundSprite[i]);
	}
}

void Ground::reset()
{
	for(int i = 0; i < NUMBER_OF_GROUND_SPRITES; i++)
		groundSprite[i].setPosition(GROUND_SPRITE_LENGTH * i, GROUND_Y_POSITION);
	velocity = GROUND_VELOCITY;
}

void Ground::moveForwards()
{
	velocity = GROUND_VELOCITY;
	velocity *= 1.0 + GROUND_SPEED_BONUS;
}