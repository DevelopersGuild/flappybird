#include "Ground.h"
#include "Assets.h"
#include "Constants.h"

Ground::Ground()
{
	groundTexture.loadFromFile(GetAssetPath("Assets/Ground.png"));
	
	for(int i = 0; i < NUMBER_OF_GROUND_SPRITES; i++)
	{
		groundSprite[i].setTexture(groundTexture);
		groundSprite[i].setOrigin(0, 113);
		ground_x_pos[i] = 800 * i;
		ground_y_pos = 650;
		groundSprite[i].setPosition(ground_x_pos[i], ground_y_pos);
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
		ground_x_pos[i] -= velocity * seconds;
		groundSprite[i].setPosition(ground_x_pos[i], ground_y_pos);
		
		if(ground_x_pos[i] <= -800)
		{
			ground_x_pos[i] = 800;
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
	{
		ground_x_pos[i] = 800 * i;
		groundSprite[i].setPosition(ground_x_pos[i], ground_y_pos);
	}
	velocity = GROUND_VELOCITY;
}

void Ground::moveForwards()
{
	velocity = GROUND_VELOCITY;
	velocity *= 1.0 + GROUND_SPEED_BONUS;
}