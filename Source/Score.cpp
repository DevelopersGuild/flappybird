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
}

void Score::update(int score)
{
	//using static_cast because to_sting doesn't take ints.
	scoreText.setString(to_string(static_cast<long long>(score)));
}

void Score::render(sf::RenderWindow &window)
{
	window.draw(scoreText);
}
	
bool Score::isHighScore(int score)
{
	ifstream highScore(GetAssetPath("Assets/HighScore.txt"));
	string buffer;
	getline(highScore, buffer);
	highScore.close();
	if(score > stoi(buffer))
	{
		ofstream newScore(GetAssetPath("Assets/HighScore.txt"));
		newScore << to_string(static_cast<long long>(score));
		newScore.close();
		return true;
	}
	else
		return false;
}
	
void Score::reset(int pipeNumber)
{

}

void Score::deleteHighScore()
{
	ofstream highScore(GetAssetPath("Assets/HighScore.txt"));
	highScore << to_string(static_cast<long long>(0));
	highScore.close();
}