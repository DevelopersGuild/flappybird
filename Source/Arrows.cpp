#include "Arrows.h"
#include "Assets.h"
#include "Constants.h"
#include "Score.h"
#include <cmath>
#include <iostream>

using namespace std;
Arrows::Arrows()
{
	arrowOffTexture.loadFromFile(GetAssetPath("Assets/ArrowOff.png"));
	arrowOffSprite.setTexture(arrowOffTexture);
	arrowOffSprite.setScale(1.5, 1.5);
	arrowOffSprite.setPosition(730, 550);
	arrowOnTexture.loadFromFile(GetAssetPath("Assets/ArrowOn.png"));
	arrowOnSprite.setTexture(arrowOnTexture);
	arrowOnSprite.setScale(1.5, 1.5);
	arrowOnSprite.setPosition(730, 550);

	moveArrow = 0;
}

void Arrows::update(float seconds)
{
	static float timedif = 0;
	timedif += seconds;
	//if(moveArrow <= 20)
		arrowOnSprite.move(0, sin(8*timedif));
	//else if(moveArrow <=40)
		//arrowOnSprite.move(0, -0.5);
	//else
		//moveArrow = 0;
		//moveArrow++;
}

void Arrows::render(sf::RenderWindow &window, bool on)
{
	if(on)
		window.draw(arrowOnSprite);
	else
		window.draw(arrowOffSprite);
}

void Arrows::reset()
{

}