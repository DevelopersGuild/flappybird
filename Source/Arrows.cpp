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
	arrowOffSprite.setPosition(730, 450);
	arrowOnTexture.loadFromFile(GetAssetPath("Assets/ArrowOn.png"));
	arrowOnSprite.setTexture(arrowOnTexture);
	arrowOnSprite.setScale(1.5, 1.5);
	arrowOnSprite.setPosition(730, 450);

	moveArrow = 0;
	totalTime = 0;
}

void Arrows::update(float seconds)
{
	totalTime += seconds;
	arrowOnSprite.move( 0, sin( 8 * totalTime) );
	
}

void Arrows::preGameRender(sf::RenderWindow &window)
{
	static float time = float(clock() / CLOCKS_PER_SEC);
}
void Arrows::render(sf::RenderWindow &window, bool on)
{
	if(on)
		window.draw( arrowOnSprite );
	else
		window.draw( arrowOffSprite );
}