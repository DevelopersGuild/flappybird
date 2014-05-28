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
	
	void setRotationIncrement(int number);

	int getRotation();
    // The center of the bird.  To be used by Game.
    sf::Vector2f getPosition();

	bool jumped;
private:
	float bird_frame_timer;

	sf::Texture birdTexture;
	sf::Sprite birdSprite;
	
	int bird_y_pos; // Controls sprite sheet animation.
	int bird_x_pos; // Controls sprite sheet animation.
	int velocity; // The birds velocity.
	int rotation; // To make bird rotate downwards when it's falling.
	int jumpAnimation; //To make the bird flap its wings when it jumps.
    int rotationIncrement;
    /**
     * Add additional things.
     */
};

#endif
