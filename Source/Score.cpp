#include "Assets.h"
#include "Score.h"
#include <fstream>
#include <string>

Score::Score()
{
	font.loadFromFile(GetAssetPath("Assets/Karmatic.ttf"));
	scoreText.setFont(font);
	scoreText.setCharacterSize(44);
	scoreText.setColor(sf::Color(0, 0, 0, 255));
	scoreText.setPosition(400,50);

	scoredPointSoundBuffer.loadFromFile(GetAssetPath("Assets/ScoredPoint.ogg"));
	scoredPointSound.setBuffer(scoredPointSoundBuffer);
	scoredPointSound.setVolume(50);

	currentScore = 0;
	tempScore = 0;
	arrowOn = false;
}

void Score::update(int score)
{
	if(score > currentScore)
	{
		tempScore = score;
		currentScore = score;
		scoredPointSound.play();
	}
	
	if(tempScore > 0 && tempScore % 5 == 0)
		arrowOn = true;
	tempScore = 0;
	//using static_cast because to_sting doesn't take ints.
	scoreText.setString(to_string(static_cast<long long>(score)));
}

void Score::render(sf::RenderWindow &window)
{
	
	window.draw(scoreText);
}
	
bool Score::isHighScore()
{
	ifstream highScore(GetAssetPath("Assets/HighScore.txt"));
	string buffer;
	getline(highScore, buffer);
	highScore.close();
	if(currentScore > stoi(buffer))
	{
		ofstream newScore(GetAssetPath("Assets/HighScore.txt"));
		newScore << to_string(static_cast<long long>(currentScore));
		newScore.close();
		return true;
	}
	else
		return false;
}
	
void Score::reset()
{
	currentScore = 0;
	arrowOn = false;
}

void Score::deleteHighScore()
{
	ofstream highScore(GetAssetPath("Assets/HighScore.txt"));
	highScore << to_string(static_cast<long long>(0));
	highScore.close();
}

bool Score::getArrowOn()
{
	return arrowOn;
}

void Score::setArrowOn(bool b)
{
	arrowOn = b;
}