#ifndef FLAPPYBIRD_GAME
#define FLAPPYBIRD_GAME

#include <SFML/Graphics.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Music.hpp>
#include "Bird.h"
#include "Pipes.h"
#include "Score.h"
#include "Arrows.h"
#include "Ground.h"
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
    //Constructor
    Game();

    // Run the main loop of the program.
    void mainLoop();

    // Handle a single event.
    void handleEvent(sf::Event event);

    // Calls reset() and anything else that happens when the bird dies.
    void birdDies();

    // All the checks to see if the bird is alive or dead at this point in time.
    bool isBirdAlive();

	void GameOver();

private:
	// Update Bird in its preGame state.
	void preGameUpdate(float seconds);

    // Update Bird and Pipes and anything else that needs to be updated.
    void midGameUpdate(float seconds);

    // Render Bird and Pipes and anything else that needs to be rendered.  Do not update anything.
    void render();

	// Reset Bird and Pipes and anything else that needs to be reset.
    void reset();

	 // Initialize the game.
    void loadResources();

	//Checks that no PopUps are open in the game window.
	bool noPopUpsAreOpen();

	sf::RenderWindow window;

	sf::Clock clock;	// Starts the clock
	sf::Time deltaTime;	// Stores the time difference between the current and previous frames

	float background_X_pos;
	float background_x_pos_increment;
	Bird bird;
	Pipes pipes;
	Score score;
	Arrows arrows;
	Ground ground;

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite[2];

	sf::Texture FiftyPercentOpaqueTexture;
	sf::Sprite FiftyPercentOpaqueSprite;

	sf::Texture scoreBackgroundTexture;
	sf::Sprite scoreBackgroundSprite;

	sf::Texture scoreBackgroundHighTexture;
	sf::Sprite scoreBackgroundHighSprite;

	sf::Texture gameoverTexture;
	sf::Sprite gameoverSprite;

	sf::Texture gameTitleTexture;
	sf::Sprite gameTitleSprite;

	sf::Texture resetScorePlaqueTexture;
	sf::Sprite resetScorePlaqueSprite;
	
	sf::Texture aboutSectionTexture;
	sf::Sprite aboutSectionSprite;
		
	sf::Font font;
	sf::Text finalScoreText;
	sf::Text bestScoreText;
	sf::Text highScoreText;
	sf::Text startInstructions;
	sf::Text restartInstructions;
	sf::Text keyInstructions;
	sf::Text credits;

	//Audio sprites
	sf::Music midGameMusic;
	sf::SoundBuffer birdDiesSoundBuffer;
	sf::Sound birdDiesSound;
	sf::Music preGameMusic;
   
	//PopUps
	bool highScore;
	bool resetPopUp;
	bool aboutPopUp;
	bool* popUps[NUMBER_OF_POPUPS];
};

#endif
