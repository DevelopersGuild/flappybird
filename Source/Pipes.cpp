#include "Assets.h"
#include "Constants.h"
#include "Pipes.h"

Pipes::Pipes()
	: pipes_frame_timer(PIPES_FRAME_DURATION)
{
	pipeTexture.loadFromFile(GetAssetPath("Assets/Pipe.png"));

	velocity = PIPES_VELOCITY;
	score = 0;
	y_pos = 0;
	tempBoost = 0;
	boostMeter = 0;
	arrowOn = false;
	BoostBuffer.loadFromFile(GetAssetPath("Assets/Boost.ogg"));
	Boost.setBuffer(BoostBuffer);

	for(int i = 0; i < NUMBER_OF_PIPES; i++)
	{
		y_pos = randomInt();

		topPipeSprite[i].setTexture(pipeTexture);
		topPipeSprite[i].setScale(1, -1); //To invert sprite.
		topPipeSprite[i].setOrigin(110,0);
		topPipeSprite[i].setPosition(PIPE_RESET_POSITION + 500*i, 100 + y_pos);
		
		bottomPipeSprite[i].setTexture(pipeTexture);
		bottomPipeSprite[i].setOrigin(110,0);
		bottomPipeSprite[i].setPosition(PIPE_RESET_POSITION + 500*i, 100 + y_pos + DISTANCE_BETWEEN_TOP_AND_BOTTOM_PIPES);
	}
	
	
}

void Pipes::update(float seconds)
{
	if(velocity > PIPES_VELOCITY)
		velocity -= PIPES_DECELERATION * seconds;
	if (velocity < PIPES_VELOCITY)
		velocity = PIPES_VELOCITY;
	
	for(int i = 0; i < NUMBER_OF_PIPES; i++)
	{
		topPipeSprite[i].move(-velocity * seconds, 0);
		bottomPipeSprite[i].move(-velocity * seconds, 0);
		
		if(topPipeSprite[i].getPosition().x <= -100)
		{
			spawnPipe(i);
		}
	}
	
	tempBoost = ( topPipeSprite[0].getPosition().x < BIRD_X_POS ) + ( topPipeSprite[1].getPosition().x < BIRD_X_POS );
	if (boostMeter + tempBoost >= 5)
		arrowOn = true;
}

void Pipes::moveForwards()
{
	velocity = PIPES_VELOCITY;
	velocity *= 1.0 + PIPES_SPEED_BONUS;
	arrowOn = false;
	boostMeter = 0;
	Boost.play();
}

void Pipes::render(sf::RenderWindow &window)
{
	for(int i = 0; i < NUMBER_OF_PIPES; i++)
	{
		window.draw(bottomPipeSprite[i]);
		window.draw(topPipeSprite[i]);
	}
}

void Pipes::reset()
{
	for(int i = 0; i < NUMBER_OF_PIPES; i++)
	{
		y_pos = 100 + randomInt();
		topPipeSprite[i].setPosition(PIPE_RESET_POSITION + DISTANCE_BETWEEN_PIPES * i, y_pos);
		bottomPipeSprite[i].setPosition(PIPE_RESET_POSITION + DISTANCE_BETWEEN_PIPES * i, y_pos + DISTANCE_BETWEEN_TOP_AND_BOTTOM_PIPES);
	}
	
	score = 0;
	boostMeter = 0;
	arrowOn = false;
	velocity = PIPES_VELOCITY;
}

void Pipes::spawnPipe(int pipeNumber)
{
	y_pos = 100 + randomInt();
	topPipeSprite[pipeNumber].setPosition(PIPE_SPAWN_POSITION, y_pos);
	bottomPipeSprite[pipeNumber].setPosition(PIPE_SPAWN_POSITION, y_pos + DISTANCE_BETWEEN_TOP_AND_BOTTOM_PIPES);
	incrementScore();
	if (boostMeter < 5)
		boostMeter++ ;
}

int Pipes::randomInt()
{
	return rand() % 200;
}

bool Pipes::isCollision(sf::Vector2f point)
{
	sf::Vector2f pos1(point.x - 18, point.y - 20);
	sf::Vector2f pos2(point.x + 23, point.y - 11);
	sf::Vector2f pos3(point.x - 7, point.y + 31);
	sf::Vector2f pos4(point.x + 27, point.y + 27);

	for(int i = 0; i < NUMBER_OF_PIPES; i++)
	{
			if(topPipeSprite[i].getGlobalBounds().contains(pos1) || bottomPipeSprite[i].getGlobalBounds().contains(pos1))
				return true;
			else if(topPipeSprite[i].getGlobalBounds().contains(pos2) || bottomPipeSprite[i].getGlobalBounds().contains(pos2))
				return true;
			else if(topPipeSprite[i].getGlobalBounds().contains(pos3) || bottomPipeSprite[i].getGlobalBounds().contains(pos3))
				return true;
			else if(topPipeSprite[i].getGlobalBounds().contains(pos4) || bottomPipeSprite[i].getGlobalBounds().contains(pos4))
				return true;
	}
	return false;

}

float Pipes::getVelocity()
{
	return velocity;
}

void Pipes::incrementScore()
{
	score++;
}

int Pipes::getScore()
{
	return score + ( topPipeSprite[0].getPosition().x < BIRD_X_POS ) + ( topPipeSprite[1].getPosition().x < BIRD_X_POS );
}

bool Pipes::getArrowOn()
{
	return arrowOn;
}