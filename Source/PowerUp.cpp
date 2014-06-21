#include "Assets.h"
#include "Constants.h"
#include "PowerUp.h"
#include <math.h>
#include <string>

using namespace std;

PowerUp::PowerUp()
	: pu_frame_timer(PU_FRAME_DURATION)
{
	powerUpTexture.loadFromFile(GetAssetPath("Assets/PowerUp.png"));

	velocity = PU_VELOCITY;
	y_pos = 200;
	totalTime = 0;
	effect = -1;
	powDuration = 0;
	durationPassed = 0;

	PUCollectBuffer.loadFromFile(GetAssetPath("Assets/PUCollect.ogg"));
	PUCollect.setBuffer(PUCollectBuffer);
	PUCollect.setVolume(50);

	powerUpSprite.setTexture(powerUpTexture);
	powerUpSprite.setOrigin(37.5,37.5);
	powerUpSprite.setPosition(PU_RESET_POSITION, y_pos);

	font.loadFromFile(GetAssetPath("Assets/Karmatic.ttf"));
	PU_Type.setFont(font);
	PU_Type.setCharacterSize(30);
	PU_Type.setColor(sf::Color(0, 0, 255, 255));
	PU_Type.setPosition(300,500);

	PU_Duration.setFont(font);
	PU_Duration.setCharacterSize(50);
	PU_Duration.setColor(sf::Color(255, 0, 255, 255));
	PU_Duration.setPosition(700,50);
}

void PowerUp::update(float seconds, sf::Vector2f point)
{
	if (isCollision(point))
	{
		effect = rand()%NUMBER_OF_PU_TYPES;
		GameSound::powerUpCollect();
		setSpawnPowerUp();
	}
	if (velocity > PU_VELOCITY)
		velocity -= PU_DECELERATION * seconds;
	if (velocity < PU_VELOCITY)
		velocity = PU_VELOCITY;

	totalTime += seconds;
	powerUpSprite.move( -velocity * seconds, 5*sin(4*totalTime) );

	if (powerUpSprite.getPosition().x < -50)
		reset();

	if (effect != -1)
	{
		setDuration();
		durationPassed += seconds;
		checkDuration( durationPassed );
		setPowerName();
	}
}

void PowerUp::moveForwards(float pipesVelocity)
{
	velocity *= 1.0 + PIPES_SPEED_BONUS;
}

void PowerUp::render(sf::RenderWindow &window)
{
	if (effect != -1)
	{
		window.draw(PU_Type);
		window.draw(PU_Duration);
	}
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
	durationPassed = 0;
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

void PowerUp::setDuration()
{
	switch (effect)
	{
	case 0:
	case 1: powDuration = 5;
		break;
	case 2:
	case 3:powDuration = 4;
		break;
	default: break;
	}
}

void PowerUp::checkDuration( float timePassed )
{
	if ((powDuration-timePassed) <= 0)
	{
		effect = -1;
		powDuration = 0;
	}
	PU_Duration.setString(to_string(static_cast<long long> (1+powDuration-timePassed)));
}

void PowerUp::setPowerName()
{
	switch (effect)
	{
	case 0: PU_Type.setString("2X POINT"); break;
	case 1: PU_Type.setString("PIPE SHRINK"); break;
	case 2: PU_Type.setString("INFINITE BOOST"); break;
	case 3: PU_Type.setString("INVINCIBIRD"); break;
	default: break;
		}
}