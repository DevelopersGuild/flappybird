#include "Assets.h"
#include "Constants.h"
#include "Pipes.h"

Pipes::Pipes()
{
	pipeTexture.loadFromFile(GetAssetPath("Assets/Pipe.png"));

	velocity = PIPES_VELOCITY;
	score = 0;
	y_pos = 0;
	tempBoost = 0;
	boostMeter = 0;
	arrowOn = false;
	
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

void Pipes::update(float seconds, int powType)
{
	if (velocity > PIPES_VELOCITY)
		velocity -= PIPES_DECELERATION * seconds;
	if (velocity < PIPES_VELOCITY)
		velocity = PIPES_VELOCITY;
	
	for(int i = 0; i < NUMBER_OF_PIPES; i++)
	{
		topPipeSprite[i].move(-velocity * seconds, 0);
		bottomPipeSprite[i].move(-velocity * seconds, 0);
		
		if(topPipeSprite[i].getPosition().x <= -100)
		{
			spawnPipe(i, powType);
		}
	}

	if (powType == 2)
		PU_InfiniteBoost();
	else
	{
		tempBoost = ( topPipeSprite[0].getPosition().x < BIRD_X_POS ) + ( topPipeSprite[1].getPosition().x < BIRD_X_POS );
		if (boostMeter + tempBoost >= 5)
			arrowOn = true;
	}
}

void Pipes::moveForwards()
{
	velocity = PIPES_VELOCITY;
	velocity *= 1.0 + PIPES_SPEED_BONUS;
	arrowOn = false;
	boostMeter = 0;
	GameSound::boost();
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

void Pipes::spawnPipe(int pipeNumber, int powType)
{
	if (powType == 1)
		PU_ShrinkPipes(pipeNumber);
	else 
	{
		y_pos = 100 + randomInt();
		pipesOriginalPosition(pipeNumber);
	}
	
	if (powType == 0)
		PU_DoubleScore();
	else incrementScore();

	if (boostMeter < 5)
		boostMeter++ ;
}

int Pipes::randomInt()
{
	return rand() % 200;
}

bool Pipes::isCollision(sf::Vector2f point, int powType)
{
	if (powType == 3) //and
		return false;

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

void Pipes::pipesOriginalPosition(int pipeNumber)
{
	topPipeSprite[pipeNumber].setPosition(PIPE_SPAWN_POSITION, y_pos);
	bottomPipeSprite[pipeNumber].setPosition(PIPE_SPAWN_POSITION, y_pos + DISTANCE_BETWEEN_TOP_AND_BOTTOM_PIPES);
}

void Pipes::PU_DoubleScore()
{
	score+= 2;
}

void Pipes::PU_ShrinkPipes(int pipeNumber)
{
	topPipeSprite[pipeNumber].setPosition(PIPE_SPAWN_POSITION, 100);
	bottomPipeSprite[pipeNumber].setPosition(PIPE_SPAWN_POSITION, 100+ PU_DISTANCE_BETWEEN_TOP_AND_BOTTOM_PIPES);
}

void Pipes::PU_InfiniteBoost()
{
	boostMeter = 5;
	arrowOn = true;
}

void Pipes::PU_InvinciBird()
{
	score+= 2;
}
