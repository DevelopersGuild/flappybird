#ifndef FLAPPYBIRD_GAME
#define FLAPPYBIRD_GAME

#include <SFML/Graphics.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Music.hpp>
#include "Bird.h"
#include "Pipes.h"
#include "Score.h"

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
    
    
	
    // Run the main loop of the program.
    void mainLoop();
	// Update Bird in its preGame state.
	void preGameUpdate(float seconds);
    // Update Bird and Pipes and anything else that needs to be updated.
    void midGameUpdate(float seconds);
    // Render Bird and Pipes and anything else that needs to be rendered.  Do not update anything.
    void render();
    // Handle a single event.
    void handleEvent(sf::Event event);
    // Reset Bird and Pipes and anything else that needs to be reset.
    void reset();
    // Calls reset() and anything else that happens when the bird dies.
    void birdDies();
    // All the checks to see if the bird is alive or dead at this point in time.
    bool isBirdAlive();
	void GameOver();
	//Initializes background sprite
	void init_Background(sf::Sprite* bgSprite, sf::Texture bgTexture);
private:
	sf::RenderWindow window;

	sf::Clock clock;	// Starts the clock
	sf::Time deltaTime;	// Stores the time difference between the current and previous frames

	float bg_X_pos;
	float bg_x_pos_increment;
	Bird bird;
	Pipes pipes;
	Score score; 
	sf::Texture bgTexture;
	sf::Sprite bgSprite[2];

	sf::Texture arrowOffTexture;
	sf::Sprite arrowOffSprite;
	sf::Texture arrowOnTexture;
	sf::Sprite arrowOnSprite;

	sf::Texture FiftyPercentOpaqueTexture;
	sf::Sprite FiftyPercentOpaqueSprite;

	sf::Font font;
	sf::Text text;
	//Audio sprites
	sf::Music midGameMusic;
	sf::SoundBuffer birdDiesSoundBuffer;
	sf::Sound birdDiesSound;
	sf::Music preGameMusic;
    /**
     * Add additional things.
     */
};

#endif
