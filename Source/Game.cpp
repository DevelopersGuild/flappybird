#include "Assets.h"
#include "Bird.h"
#include "Constants.h"
#include "Game.h"
#include "Pipes.h"
#include "Score.h"
#include <iostream>

using namespace std;

Game::Game()
	: window(sf::VideoMode(800, 600), "Flappy Bird")
{
    // Turning vertical-sync on causes window.display() to pause the app until
    // 1/60th of a second has passed.
	bg_X_pos = 0;
	bg_x_pos_increment = 0.8;
	 //Loads sprite sheet as texture
	bgTexture.loadFromFile(GetAssetPath("Assets/bg.png"));
	bgSprite[0].setTexture(bgTexture);  // sets texture of sprite to the sprite sheet
	bgSprite[1].setTexture(bgTexture);  // sets texture of sprite to the sprite sheet
	bgSprite[0].setTextureRect(sf::IntRect(0, 0, 1024, 256));
	bgSprite[1].setTextureRect(sf::IntRect(0, 0, 1024, 256));
	bgSprite[0].setScale(1, 2.343); //To fill entire screen with sprite
	bgSprite[1].setScale(1, 2.343); //To fill entire screen with sprite

	arrowOffTexture.loadFromFile(GetAssetPath("Assets/ArrowOff.png"));
	arrowOffSprite.setTexture(arrowOffTexture);
	arrowOffSprite.setScale(1.5, 1.5);
	arrowOffSprite.setPosition(730, 530);
	arrowOnTexture.loadFromFile(GetAssetPath("Assets/ArrowOn.png"));
	arrowOnSprite.setTexture(arrowOnTexture);
	arrowOnSprite.setScale(1.5, 1.5);
	arrowOnSprite.setPosition(730, 530);
	window.setVerticalSyncEnabled(true);
}

void Game::mainLoop()
{

	while (window.isOpen())
	{
		static int i = 0;
		i++;
		deltaTime = clock.restart();
		
		sf::Event event;
		while( window.pollEvent(event) )
		{
			handleEvent( event );
		}

		if(!isBirdAlive())
			cout << i << ": Bird is dead.\n";
		update( deltaTime.asSeconds() );
		render();
	}
}

void Game::update(float seconds)
{
	if(bg_X_pos <= -1024)
		bg_X_pos = 0;
	if(bg_x_pos_increment > 0.8)
		bg_x_pos_increment -= 0.0625;

	bgSprite[0].setPosition(bg_X_pos, 0);
	bgSprite[1].setPosition(bg_X_pos + 1024, 0);
	bg_X_pos -= bg_x_pos_increment;

	bird.update( seconds , pipes.getVelocity());
	pipes.update( seconds );
	score.update( pipes.getScore() );
}

void Game::render()
{
	
	window.clear();

	window.draw(bgSprite[0]);
	window.draw(bgSprite[1]);
	if(bird.jumped >= 10)
		window.draw(arrowOnSprite);
	else
		window.draw(arrowOffSprite);
	bird.render( window );
	pipes.render( window );
	score.render( window );
	window.display();
}

void Game::handleEvent(sf::Event event)
{
	switch (event.type)
    {
    case sf::Event::Closed:
        window.close();
        break;
	case sf::Event::KeyPressed:
		if(event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Up)
			bird.jump();
		else if(event.key.code == sf::Keyboard::Right)
		{
			if(bird.jumped >= 10)
			{
				bg_x_pos_increment = 2;
				pipes.moveForwards();
				bird.setRotationIncrement(-5);
				bird.jumped = 0;
			}
		}
    default:
        break;
    }
}

void Game::reset()
{
}

void Game::GameOver()
{

}

bool Game::isBirdAlive()
{
	if(pipes.isCollision(bird.getPosition()))
		return false;
	else 
		return true;
}