#include "Assets.h"
#include "Bird.h"
#include "Constants.h"
#include "Game.h"
#include "Pipes.h"

Game::Game()
	: window(sf::VideoMode(800, 600), "Flappy Bird")
{    
    // Turning vertical-sync on causes window.display() to pause the app until
    // 1/60th of a second has passed.
	window.setVerticalSyncEnabled(true);
}

void Game::mainLoop()
{
	while (window.isOpen())
	{
		deltaTime = clock.restart();
		
		sf::Event event;
		while( window.pollEvent(event) )
		{
			handleEvent( event );
		}

		update( deltaTime.asSeconds() );
		render();
	}
}

void Game::update(float seconds)
{
	bird.update( seconds );
	pipes.update( seconds );
}

void Game::render()
{
	window.clear();

	bird.render( window );
	pipes.render( window );

	window.display();
}

void Game::handleEvent(sf::Event event)
{
	if( event.type == sf::Event::Closed )
	{
		window.close();
	}
}

void Game::reset()
{
}

bool Game::isBirdAlive()
{
    return true;
}

/**
 * Add additional things.
 */
