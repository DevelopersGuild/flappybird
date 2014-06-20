#ifndef FLAPPYBIRD_SCORE
#define FLAPPYBIRD_SCORE

#include <SFML/Graphics.hpp>
#include "GameSound.h"
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
	bool isHighScore();
	// Rests the score to 0.
	void reset();
    void deleteHighScore();

private:
	sf::Font font;
	sf::Text scoreText;
		
	int currentScore;
};
#endif