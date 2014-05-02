#include <SFML/Graphics.hpp>
#include <stdlib.h>

// Constants
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define INITIAL_CIRCLE_SIZE 100.f
#define CIRCLE_GROWTH_PER_MILLISECOND 0.01f

int main()
{
    // Initialize SFML
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_WIDTH), "Flappy Bird");
    window.setVerticalSyncEnabled(true);
    sf::CircleShape shape(INITIAL_CIRCLE_SIZE);
    shape.setFillColor(sf::Color::Green);
    sf::Clock myTimer;

    // Main loop
    while (window.isOpen())
    {
        // Get how long it's been since the last frame was drawn
        sf::Time frameTime = myTimer.getElapsedTime();
        myTimer.restart();

        // Receive all incoming input
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update game state
        shape.setRadius(shape.getRadius() + frameTime.asMilliseconds() * CIRCLE_GROWTH_PER_MILLISECOND);

        // Draw a frame and display it
        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}