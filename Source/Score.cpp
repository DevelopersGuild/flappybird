#include "Assets.h"
#include "Score.h"


Score::Score()
{
	font.loadFromFile(GetAssetPath("Assets/Karmatic.ttf"));
	scoreText.setFont(font);
	scoreText.setCharacterSize(34);
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
	return true;
}
	
void Score::reset(int pipeNumber)
{

}