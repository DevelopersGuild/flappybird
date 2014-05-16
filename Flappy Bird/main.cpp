#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

const float BIRD_FRAME_DURATION = 0.045;

int main()
{
	float bird_frame_timer = BIRD_FRAME_DURATION;
	
    sf::RenderWindow window(sf::VideoMode(800, 600), "Flappy Bird");
	window.setVerticalSyncEnabled(true);

    sf::Texture birdTexture;
	birdTexture.loadFromFile("NewBird.png"); //Loads sprite sheet as texture

	sf::Sprite birdSprite;
	birdSprite.setTexture(birdTexture); // sets texture of sprite to the sprite sheet

	birdSprite.setTextureRect(sf::IntRect(0, 0, 110.2, 101.333));
	int y_pos = 0;
	int x_pos = 0;

    sf::Clock clock; // starts the clock

    while (window.isOpen())
    {
		sf::Time elapsed = clock.getElapsedTime();
		bird_frame_timer -= elapsed.asSeconds();
		clock.restart();
		
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		if(y_pos*101 >= birdTexture.getSize().y)
			y_pos = 0;
	    if(x_pos*110 >= birdTexture.getSize().x - 110)
		{
			x_pos = 0;
			y_pos++;
		}

		if(y_pos == 2 && x_pos == 4)
		{
			x_pos = 0;
			y_pos = 0;
		}

		if(bird_frame_timer <= 0)
		{
			birdSprite.setTextureRect(sf::IntRect(x_pos*110, y_pos*102, 111, 101));
			x_pos++;
			//if(x_pos*110 >= birdTexture.getSize().x)
				//y_pos++;
			bird_frame_timer =BIRD_FRAME_DURATION;
		}
		
		

		
        window.clear();
        window.draw(birdSprite);
        window.display();
    }
    return 0;
}
