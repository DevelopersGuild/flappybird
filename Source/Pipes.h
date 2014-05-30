#ifndef FLAPPYBIRD_PIPES
#define FLAPPYBIRD_PIPES

#include <SFML/Graphics.hpp>

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
	void Pipes::moveForwards();
    // Draw pipes on screen.  Do not move them.
    void render(sf::RenderWindow &window);
    // Delete all pipes as the game is beginning anew.
    void reset();
    // Is the following point within one of the pipes?
    bool isCollision(sf::Vector2f point);
    // How many pipes have passed by on-screen?
    int getScore();
	// Add 1 to the score.
	void incrementScore();
    
private:

	sf::Texture pipeTexture;
	sf::Sprite pipeSprite;

	int pipe_y_pos;
	int pipe_x_pos;
	int pipe_x_pos_increment; //The 
	int forwardsCounter;
	int score;
    /**
     * Add additional things.
     */
	
};

#endif
