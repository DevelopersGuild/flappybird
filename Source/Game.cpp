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
	bgTexture.loadFromFile(GetAssetPath("Assets", "bg.png")); //Loads sprite sheet as texture
	bgSprite.setTexture(bgTexture);  // sets texture of sprite to the sprite sheet
	bgSprite.setTextureRect(sf::IntRect(0, 0, 800, 600));
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
	bird.update( seconds , pipes.getVelocity());
	pipes.update( seconds );
}

void Game::render()
{
	window.clear();
	window.draw(bgSprite);
	bird.render( window );
	pipes.render( window );

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
			if(bird.jumped)
			{
				pipes.moveForwards();
				bird.setRotationIncrement(-5);
				bird.jumped = false;
			}
		}
    default:
        break;
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
