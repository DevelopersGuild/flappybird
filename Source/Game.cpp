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
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		bird.render(window);
        window.clear();
        window.display();
    }
}

void Game::update(float seconds)
{
}

void Game::render()
{
}

void Game::handleEvent(sf::Event event)
{
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
