#include "Assets.h"
#include "Constants.h"
#include "Pipes.h"

Pipes::Pipes()
{
	pipeTexture.loadFromFile(GetAssetPath("Assets", "Pipe.png"));

	pipeSprite.setTexture(pipeTexture);
	pipeSprite.setTextureRect(sf::IntRect(140, 0, 116, 1725));

	pipe_x_pos = 480;
	pipe_y_pos = -700;
}

void Pipes::update(float seconds)
{
	pipe_x_pos--;
	pipeSprite.setPosition(pipe_x_pos, pipe_y_pos);
	if(pipe_x_pos <= -200)
	{
		reset();
	}
}

void Pipes::render(sf::RenderWindow &window)
{
	window.draw(pipeSprite);
}

void Pipes::reset()
{
	pipe_x_pos = 900;
	pipe_y_pos = rand()%(-350) - 700;
}

bool Pipes::isCollision(sf::Vector2f point)
{
	// Change this later to actually check for collisions
    return false;
}

int Pipes::getScore()
{
    return 0;
}

/**
 * Add additional things.
 */
