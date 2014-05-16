#include "Assets.h"
#include "Bird.h"
#include "Constants.h"
#include "Game.h"
#include "Pipes.h"

Game::Game()
{
    //
    // This function is responsible for too much!  Help clean it up by putting
    // things in their approrpriate places around town.  (Delete this comment
    // when it is no longer necessary.)
    //
    
	float frame_timer = BIRD_FRAME_DURATION;
	
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    
    // Turning vertical-sync on causes window.display() to pause the app until
    // 1/60th of a second has passed.
	window.setVerticalSyncEnabled(true);
    
    sf::Texture birdTexture;
	birdTexture.loadFromFile(GetAssetPath("Assets", "NewBird.png"));
    
	sf::Sprite birdSprite;
	birdSprite.setTexture(birdTexture);
    
	birdSprite.setTextureRect(sf::IntRect(0, 0, 110.2, 101.333));
	int y_pos = 0;
	int x_pos = 0;
    
    sf::Clock clock; // starts the clock
    
    while (window.isOpen())
    {
		sf::Time elapsed = clock.getElapsedTime();
		frame_timer -= elapsed.asSeconds();
		clock.restart();
		
		if(y_pos >= birdTexture.getSize().y)
			y_pos = 0;
	    if(x_pos*110 >= birdTexture.getSize().x - 110)
			x_pos = 0;
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
		if(frame_timer <= 0)
		{
			birdSprite.setTextureRect(sf::IntRect(x_pos*110.2, y_pos*101.333, 110, 101));
			x_pos++;
			if(x_pos*110 >= birdTexture.getSize().x)
				y_pos++;
			frame_timer =BIRD_FRAME_DURATION;
		}
        window.clear();
        window.draw(birdSprite);
        window.display();
    }
}

void Game::mainLoop()
{
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
