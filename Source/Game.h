#ifndef FLAPPYBIRD_GAME
#define FLAPPYBIRD_GAME

#include <SFML/Graphics.hpp>
#include "Bird.h"
#include "Pipes.h"

/**
 * Game class responsibilities:
 *
 *  - Main loop.
 *
 *  - Handle game state.
 *
 *  - Process keyboard and mouse input.
 *
 *  - Orchestrate the game.
 */

class Game
{
public:
    /**
     * Do not add parameters to Game's constructor.
     */
    // Initialize the game.
    Game();
    
    /**
     * Try not to change the public methods' names and parameters, if possible.
     */
    // Run the main loop of the program.
    void mainLoop();
    // Update Bird and Pipes and anything else that needs to be updated.
    void update(float seconds);
    // Render Bird and Pipes and anything else that needs to be rendered.  Do not update anything.
    void render();
    // Handle a single event.
    void handleEvent(sf::Event event);
    // Reset Bird and Pipes and anything else that needs to be reset.
    void reset();
    // All the checks to see if the bird is alive or dead at this point in time.
    bool isBirdAlive();

private:
	sf::RenderWindow window;

	sf::Clock clock;	// Starts the clock
	sf::Time deltaTime;	// Stores the time difference between the current and previous frames
    sf::Texture bgTexture;
    sf::Sprite bgSprite;

	Bird bird;
	Pipes pipes;
    /**
     * Add additional things.
     */
};

#endif
