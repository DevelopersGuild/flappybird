#ifndef FLAPPYBIRD_PIPES
#define FLAPPYBIRD_PIPES

#include <SFML/Graphics.hpp>
#include "Constants.h"

/**
 * Pipes class responsibilities:
 *
 *  - Manage an array of pipes.
 *
 *  - Determine if a bird is colliding with any pipe.
 *
 *  - Calculate number of pipes passed.
 */

class Pipes
{
public:
    /**
     * Add parameters to Pipes's constructor.
     */
    Pipes();
    
    /**
     * Try not to change the public methods' names and parameters, if possible.
     */
    // Spawn new pipes if necessary.  Move pipes.
    void update(float seconds);
	//Speeds up the pipes animation to give the illusion that the bird moved forwards
	void moveForwards();
    // Draw pipes on screen.  Do not move them.
    void render(sf::RenderWindow &window);
    // Delete all pipes as the game is beginning anew.
    void reset(int pipeNumber);
    // Is the following point within one of the pipes?
    bool isCollision(sf::Vector2f point);

	float getVelocity();
    // How many pipes have passed by on-screen?
    int getScore();
	// Add 1 to the score.
	void incrementScore();
	// Returns a random integer, used for random y position of pipe.
	int randomInt();
    
private:

	sf::Texture bottomPipeTexture;
	sf::Sprite bottomPipeSprite[NUMBER_OF_PIPES];
	sf::Texture topPipeTexture;
	sf::Sprite topPipeSprite[NUMBER_OF_PIPES];

	float velocity;
	float pipes_frame_timer;
	int pipe_y_pos[NUMBER_OF_PIPES];
	int pipe_x_pos[NUMBER_OF_PIPES];
	int pipe_x_pos_increment; //The 
	int score;
    /**
     * Add additional things.
     */
	
};

#endif
