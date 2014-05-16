#include <SFML/Graphics.hpp>
#include "Assets.h"

const float BIRD_FRAME_DURATION = 0.05;

int main()
{
	float frame_timer = BIRD_FRAME_DURATION;
	
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	window.setVerticalSyncEnabled(true);

    sf::Texture birdTexture;
	birdTexture.loadFromFile(GetAssetPath("Assets", "NewBird.png"));

	sf::Sprite birdSprite;
	birdSprite.setTexture(birdTexture);

	birdSprite.setTextureRect(sf::IntRect(0, 0, 110.2, 101.333));
	int y_pos = 0;
	int x_pos = 0;

    sf::Clock clock; // starts the clock

    while (window.isOpen())
    {
		sf::Time elapsed = clock.getElapsedTime();
		frame_timer -= elapsed.asSeconds();
		clock.restart();
		
		if(y_pos >= birdTexture.getSize().y)
			y_pos = 0;
	    if(x_pos*110 >= birdTexture.getSize().x - 110)
			x_pos = 0;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		if(frame_timer <= 0)
		{
			birdSprite.setTextureRect(sf::IntRect(x_pos*110.2, y_pos*101.333, 110, 101));
			x_pos++;
			if(x_pos*110 >= birdTexture.getSize().x)
				y_pos++;
			frame_timer =BIRD_FRAME_DURATION;
		}
        window.clear();
        window.draw(birdSprite);
        window.display();
    }
    return 0;
}
