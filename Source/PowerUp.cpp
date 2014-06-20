#include "Assets.h"
#include "Constants.h"
#include "PowerUp.h"
#include <math.h>

PowerUp::PowerUp()
	: pu_frame_timer(PU_FRAME_DURATION)
{
	powerUpTexture.loadFromFile(GetAssetPath("Assets/PowerUp.png"));

	velocity = PU_VELOCITY;
	y_pos = 250;
	totalTime = 0;
	effect = -1;
	powDuration = 0;

	powerUpSprite.setTexture(powerUpTexture);
	powerUpSprite.setOrigin(37.5,37.5);
	powerUpSprite.setPosition(PU_RESET_POSITION, y_pos);
}

void PowerUp::update(float seconds, sf::Vector2f point)
{
	if (isCollision(point))
	{
		effect = rand()%NUMBER_OF_PU_TYPES;
		gameSound.powerUpCollect();
		setSpawnPowerUp();
	}
	if (velocity > PU_VELOCITY)
		velocity -= PU_DECELERATION * seconds;
	if (velocity < PU_VELOCITY)
		velocity = PU_VELOCITY;

	totalTime += seconds;
	powerUpSprite.move( -velocity * seconds, sin(totalTime) );

	if (powerUpSprite.getPosition().x < -50)
		reset();

	if (effect != -1)
	{
		powDuration += seconds;
		checkDuration();
	}
}

void PowerUp::moveForwards(float pipesVelocity)
{
	velocity *= 1.0 + PIPES_SPEED_BONUS;
}

void PowerUp::render(sf::RenderWindow &window)
{
	window.draw(powerUpSprite);
}

void PowerUp::setSpawnPowerUp()
{
	powerUpSprite.setPosition(PU_RESET_POSITION, y_pos);
	velocity = PU_VELOCITY;
}

void PowerUp::reset()
{
	setSpawnPowerUp();
	powDuration = 0;
	effect = -1;
	totalTime = 0;
}

bool PowerUp::isCollision(sf::Vector2f point)
{
	sf::Vector2f pos1(point.x - 18, point.y - 20);
	sf::Vector2f pos2(point.x + 23, point.y - 11);
	sf::Vector2f pos3(point.x - 7, point.y + 31);
	sf::Vector2f pos4(point.x + 27, point.y + 27);

	if(powerUpSprite.getGlobalBounds().contains(pos1))
		return true;
	else if(powerUpSprite.getGlobalBounds().contains(pos2))
		return true;
	else if(powerUpSprite.getGlobalBounds().contains(pos3))
		return true;
	else if(powerUpSprite.getGlobalBounds().contains(pos4))
		return true;

	return false;

}

int PowerUp::getPowerUpType()
{
	return effect;
}

void PowerUp::checkDuration()
{
	switch (effect)
	{
	case 0:// double score for 5s
		if (powDuration >= 5)
		{
			effect = -1;
			powDuration = 0;
		} break;
	case 1: // add more effects!
	default: break;
	}
}