#ifndef FLAPPYBIRD_SCORE
#define FLAPPYBIRD_SCORE

#include <SFML/Graphics.hpp>
#include "Pipes.h"
#include <string>
using namespace std;
/**
 * Score class responsibilities:
 *
 *  - Calculate score.
 *
 *  - Display score.
 */

class Score
{
public:
		Score();

		// Update the score.
		void update(int seconds);
		// Draw score on the screen.
		void render(sf::RenderWindow &window);
		//Checks for and records highscores.
		bool isHighScore(int score);
		// Rests the score to 0.
		void reset(int pipeNumber);
	private:
		sf::Font font;
		sf::Text scoreText;
};
#endif