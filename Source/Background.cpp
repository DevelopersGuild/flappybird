#include "Assets.h"
#include "Constants.h"
#include "Background.h"

Background::Background()
{
	backgroundTexture.loadFromFile(GetAssetPath("Assets/background.png"));
	background_X_pos = 0;
	background_x_pos_increment = 0.8f;
	//Initialize background sprites.
	for(int i = 0; i < NUMBER_OF_BACKGROUND_SPRITES; i++)
	{
		backgroundSprite[i].setTexture(backgroundTexture);
		backgroundSprite[i].setScale(1, 600/BACKGROUND_SPRITE_HEIGHT); //To fill entire window with sprite
		backgroundSprite[i].setOrigin(0, 0);
		backgroundSprite[i].setPosition(i * BACKGROUND_SPRITE_LENGTH, 0);
	}
	velocity = BACKGROUND_VELOCITY;
}

void Background::update(float seconds)
{
	/*
	*The following if statement checks if the background is moving faster than usual. If it is, it will slow it down by a little bit.
	* After a few frames, the speed will be back to normal. This makes the deceleration look smooth.
	*/
	if(velocity > BACKGROUND_VELOCITY)
	{
		velocity -= BACKGROUND_DECELERATION * seconds;
	}
	if (velocity < BACKGROUND_VELOCITY)
	{
		velocity = BACKGROUND_VELOCITY;
	}

	for(int i = 0; i < NUMBER_OF_BACKGROUND_SPRITES; i++)
	{
		backgroundSprite[i].move(-velocity * seconds, 0);

		//If the sprite has moved off screen, reset its position.
		if(backgroundSprite[i].getPosition().x <= -1024) 
		{
			backgroundSprite[i].move( NUMBER_OF_BACKGROUND_SPRITES*BACKGROUND_SPRITE_LENGTH, 0);
		}
	}
}

void Background::render(sf::RenderWindow &window)
{
	for(int i = 0; i <  NUMBER_OF_BACKGROUND_SPRITES; i++)
	{
		window.draw(backgroundSprite[i]);
	}
}

void Background::moveForwards()
{
	velocity = BACKGROUND_VELOCITY;
	velocity *= 1.0 + BACKGROUND_SPEED_BONUS;
}

void Background::reset()
{
	for(int i = 0; i < NUMBER_OF_BACKGROUND_SPRITES; i++)
	{
		backgroundSprite[i].setPosition(i * BACKGROUND_SPRITE_LENGTH, 0);
	}
}
