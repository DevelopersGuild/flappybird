#include "Assets.h"
#include "Constants.h"
#include "Pipes.h"

Pipes::Pipes()
	: pipes_frame_timer(PIPES_FRAME_DURATION)
{
	pipeTexture.loadFromFile(GetAssetPath("Assets", "Pipe.png"));
	pipeSprite.setTexture(pipeTexture);
	pipeSprite.setTextureRect(sf::IntRect(140, 0, 116, 1725));
	pipe_x_pos = 480;
	pipe_y_pos = -500;
	pipe_x_pos_increment = 10;
	forwardsCounter = 0;
	velocity = 0;
}

void Pipes::update(float seconds)
{
	velocity += PIPES_ACCELERATION * seconds; 
	pipes_frame_timer -=seconds;
	//to control the ammount of time the pipe animation is sped up
	if(pipes_frame_timer <= 0)
	{
		if(pipe_x_pos_increment == 16)
			forwardsCounter++;
		if(forwardsCounter >= 16)
		{
			pipe_x_pos_increment = 10;
			forwardsCounter = 0;
		}
		pipe_x_pos -= pipe_x_pos_increment;
		pipeSprite.setPosition(pipe_x_pos, pipe_y_pos);
	
		if(pipe_x_pos <= -200)
		{
			reset();
		}
		pipes_frame_timer = PIPES_FRAME_DURATION; 
	}
	
}

void Pipes::moveForwards()
{
	pipe_x_pos_increment = 16;
}

void Pipes::render(sf::RenderWindow &window)
{
	window.draw(pipeSprite);
}

void Pipes::reset()
{
	pipe_x_pos = 900;
	pipe_y_pos = rand()%(-250) - 700;
}

bool Pipes::isCollision(sf::Vector2f point)
{
	// Change this later to actually check for collisions
    return false;
}

float Pipes::getVelocity(){return velocity;}

int Pipes::getScore()
{
    return 0;
}

/**
 * Add additional things.
 */
