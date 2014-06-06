#include "Assets.h"
#include "Constants.h"
#include "Pipes.h"

Pipes::Pipes()
	: pipes_frame_timer(PIPES_FRAME_DURATION)
{
	bottomPipeTexture.loadFromFile(GetAssetPath("Assets/bPipe.png"));
	topPipeTexture.loadFromFile(GetAssetPath("Assets/tPipe.png"));
	for(int i = 0; i < NUMBER_OF_PIPES; i++)
	{
		bottomPipeSprite[i].setTexture(bottomPipeTexture);
		topPipeSprite[i].setTexture(topPipeTexture);
		bottomPipeSprite[i].setTextureRect(sf::IntRect(0, 0, 130, 500));
		topPipeSprite[i].setTextureRect(sf::IntRect(0, 0, 130, 500));
		bottomPipeSprite[i].setOrigin(0,0);
		topPipeSprite[i].setOrigin(0,500);
		pipe_x_pos[i] = 900 + 500*i;
		pipe_y_pos[i] = 100 + randomInt();

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
		topPipeSprite[i].setPosition(pipe_x_pos[i], pipe_y_pos[i]);
		bottomPipeSprite[i].setPosition(pipe_x_pos[i], pipe_y_pos[i] + DISTANCE_BETWEEN_TOP_AND_BOTTOM_PIPE);
		
		if(pipe_x_pos[i] <= -100)
		{
			spawnPipe(i);
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
		window.draw(bottomPipeSprite[i]);
		window.draw(topPipeSprite[i]);
	}
}

void Pipes::reset()
{
	pipe_x_pos[0] = 900;
	pipe_x_pos[1] = 1400;
	score = 0;
}

void Pipes::spawnPipe(int pipeNumber)
{
	pipe_x_pos[pipeNumber] = 900;
	pipe_y_pos[pipeNumber] = 100 + randomInt();
	incrementScore();
}

int Pipes::randomInt()
{
	return rand()%(251);
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
	return score + ( topPipeSprite[0].getPosition().x < BIRD_X_POS ) + ( topPipeSprite[1].getPosition().x < BIRD_X_POS  );
}
