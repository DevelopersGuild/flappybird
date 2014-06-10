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
    void update(float seconds, float pipes_velocity);
	//Simple animation of the bird flying on its own
	void Bird::preGameUpdate(float seconds);
    // Draw the bird.  Do not move the bird.
    void render(sf::RenderWindow &window);
	// Advance animation by one frame.
	void advanceAnimation();
	// Set which frame we are at in the animation from the sprite sheet.
	void setAnimationFrame(int x, int y);
    // Reset the bird to its starting position.
    void reset();
    // The player has the bird jump.
    void jump();
	
	void setRotationIncrement(int number);

	int getRotation();
    // The center of the bird.  To be used by Game.
    sf::Vector2f getPosition();

	int jumped;
private:
	float bird_frame_timer;
	float preGame_bird_frame_timer;

	sf::Texture birdTexture;
	sf::Sprite birdSprite;
	
	int bird_y_pos; // Controls sprite sheet animation.
	int bird_x_pos; // Controls sprite sheet animation.
	float velocity; // The birds velocity.
	float rotation; // To make bird rotate downwards when it's falling.
	float animationRemaining; //To make the bird flap its wings when it jumps.
    int rotationIncrement;

    /**
     * Add additional things.
     */
};

#endif
