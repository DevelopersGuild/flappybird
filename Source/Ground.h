#ifndef FLAPPYBIRD_GROUND
#define FLAPPYBIRD_GROUND

#include <SFML/Graphics.hpp>
#include "Constants.h"

class Ground
{
public:
    //Constructor
    Ground();

    void render(sf::RenderWindow &window);

    void update(float seconds);

    void reset();

	void moveForwards();
private:
		sf::Texture groundTexture;
		sf::Sprite groundSprite[NUMBER_OF_GROUND_SPRITES];

		float velocity;
		float ground_frame_timer;
		float ground_y_pos;
		float ground_x_pos[NUMBER_OF_GROUND_SPRITES];
		float ground_x_pos_increment; //The 
};

#endif
