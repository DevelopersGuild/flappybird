#include "Assets.h"
#include "Constants.h"
#include "Pipes.h"

Pipes::Pipes()
	: pipes_frame_timer(PIPES_FRAME_DURATION)
{
	pipeTexture.loadFromFile(GetAssetPath("Assets", "Pipe.png"));
	for(int i = 0; i < NUMBER_OF_PIPES; i++)
	{
		pipeSprite[i].setTexture(pipeTexture);
		pipeSprite[i].setTextureRect(sf::IntRect(140, 0, 116, 1725));
		pipe_x_pos[i] = 900 + 500*i;
		pipe_y_pos[i] = randomInt();
	}
	velocity = PIPES_VELOCITY;
	score = 0;
}

void Pipes::update(float seconds)
{
	if(velocity > PIPES_VELOCITY)
		velocity -= PIPES_DECELERATION * seconds;
	if (velocity < PIPES_VELOCITY)
		velocity = PIPES_VELOCITY;
	
	for(int i = 0; i < NUMBER_OF_PIPES; i++)
	{
		pipe_x_pos[i] -= velocity * seconds;
		pipeSprite[i].setPosition(pipe_x_pos[i], pipe_y_pos[i]);
		if(pipe_x_pos[i] <= -200)
		{
			reset(i);
		}
	}
		
}

void Pipes::moveForwards()
{
	velocity = PIPES_VELOCITY;
	velocity *= 1.0 + PIPES_SPEED_BONUS;
}

void Pipes::render(sf::RenderWindow &window)
{
	for(int i = 0; i < NUMBER_OF_PIPES; i++)
	{
		window.draw(pipeSprite[i]);
	}
}

void Pipes::reset(int pipeNumber)
{
	pipe_x_pos[pipeNumber] = 900;
	pipe_y_pos[pipeNumber] = randomInt();
	incrementScore();
}

int Pipes::randomInt()
{
	return rand()%(-250) - 700;
}


bool Pipes::isCollision(sf::Vector2f point)
{
	// Change this later to actually check for collisions
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
    return score;
}

/**
 * Add additional things.
 */
