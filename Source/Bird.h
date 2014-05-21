#ifndef FLAPPYBIRD_BIRD
#define FLAPPYBIRD_BIRD

#include <SFML/Graphics.hpp>

/**
 * Bird class responsibilities:
 *
 *  - Moves in Y-coordinate.
 *
 *  - Graphical rotation.
 *
 *  - Animate between several frames over time.
 */

class Bird
{
public:
    /**
     * Add parameters to Bird's constructor.
     */
    Bird();

    /**
     * Try not to change the public methods' names and parameters, if possible.
     */
    // Move the bird.
    void update(float seconds);
    // Draw the bird.  Do not move the bird.
    void render(sf::RenderWindow &window);
    // Reset the bird to its starting position.
    void reset();
    // The player has the bird jump.
    void jump();
    // The center of the bird.  To be used by Game.
    sf::Vector2f getPosition();

private:
	float bird_frame_timer;

	sf::Texture birdTexture;
	sf::Sprite birdSprite;
	
	int bird_y_pos;
	int bird_x_pos;
    
    /**
     * Add additional things.
     */
};

#endif
