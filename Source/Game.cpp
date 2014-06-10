#include "Assets.h"
#include "Bird.h"
#include "Constants.h"
#include "Game.h"
#include "Pipes.h"
#include "Score.h"
#include <iostream>

using namespace std;

 enum 
{
	 preGame, midGame, postGame
}GameState;

Game::Game()
	: window(sf::VideoMode(800, 600), "Flappy Bird")
{
    // Turning vertical-sync on causes window.display() to pause the app until
    // 1/60th of a second has passed.
	window.setVerticalSyncEnabled(true);

	bg_X_pos = 0;
	
	bg_x_pos_increment = 0.8;
	 //Loads sprite sheet as texture
	bgTexture.loadFromFile(GetAssetPath("Assets/bg.png"));
	bgSprite[0].setTexture(bgTexture);  // sets texture of sprite to the sprite sheet
	bgSprite[1].setTexture(bgTexture);  // sets texture of sprite to the sprite sheet
	bgSprite[0].setTextureRect(sf::IntRect(0, 0, 1024, 256));
	bgSprite[1].setTextureRect(sf::IntRect(0, 0, 1024, 256));
	bgSprite[0].setScale(1, 2.343); //To fill entire screen with sprite
	bgSprite[1].setScale(1, 2.343); //To fill entire screen with sprite

	arrowOffTexture.loadFromFile(GetAssetPath("Assets/ArrowOff.png"));
	arrowOffSprite.setTexture(arrowOffTexture);
	arrowOffSprite.setScale(1.5, 1.5);
	arrowOffSprite.setPosition(730, 530);
	arrowOnTexture.loadFromFile(GetAssetPath("Assets/ArrowOn.png"));
	arrowOnSprite.setTexture(arrowOnTexture);
	arrowOnSprite.setScale(1.5, 1.5);
	arrowOnSprite.setPosition(730, 530);

	font.loadFromFile(GetAssetPath("Assets/Karmatic.ttf"));
	text.setFont(font);
	text.setCharacterSize(44);
	text.setColor(sf::Color::White);
	text.setPosition(250,100);

	FiftyPercentOpaqueTexture.loadFromFile(GetAssetPath("Assets/50Opaque.png"));
	FiftyPercentOpaqueSprite.setTexture(FiftyPercentOpaqueTexture);

	preGameMusic.openFromFile(GetAssetPath("Assets/PreGame.ogg"));
	preGameMusic.play();
	preGameMusic.setLoop(true);
	preGameMusic.setVolume(20);

	midGameMusic.openFromFile(GetAssetPath("Assets/MidGame.ogg"));
	midGameMusic.setVolume(20);
	midGameMusic.setLoop(true);
	
	birdDiesSoundBuffer.loadFromFile(GetAssetPath("Assets/BirdDies.ogg"));
	birdDiesSound.setBuffer(birdDiesSoundBuffer);

	window.setVerticalSyncEnabled(true);

	GameState = preGame;
}

void Game::mainLoop()
{
	
	while (window.isOpen())
	{
		deltaTime = clock.restart();
		
		sf::Event event;
		while( window.pollEvent(event) )
		{
			handleEvent( event );
		}

		if(GameState == preGame)
			preGameUpdate( deltaTime.asSeconds() );
		else
			midGameUpdate( deltaTime.asSeconds() );
		
		if((!isBirdAlive()) && (GameState == midGame))
        {
			GameOver();
			birdDiesSound.play();
			midGameMusic.stop();
        }
		render();
	}
}

void Game::preGameUpdate(float seconds)
{
	if(bg_X_pos <= -1024)
		bg_X_pos = 0;
	if(bg_x_pos_increment > 0.8)
		bg_x_pos_increment -= 0.0625;

	bgSprite[0].setPosition(bg_X_pos, 0);
	bgSprite[1].setPosition(bg_X_pos + 1024, 0);
	bg_X_pos -= bg_x_pos_increment;

	bird.preGameUpdate( seconds );
}

void Game::midGameUpdate(float seconds)
{
	if(GameState != postGame)
	{
		if(bg_X_pos <= -1024)
			bg_X_pos = 0;
		if(bg_x_pos_increment > 0.8)
			bg_x_pos_increment -= 0.0625;
	}
	bgSprite[0].setPosition(bg_X_pos, 0);
	bgSprite[1].setPosition(bg_X_pos + 1024, 0);
	bg_X_pos -= bg_x_pos_increment;

	bird.update( seconds , pipes.getVelocity());
	if(GameState == midGame)
		pipes.update( seconds );
	score.update( pipes.getScore() );
}

void Game::render()
{
	window.clear();

	window.draw(bgSprite[0]);
	window.draw(bgSprite[1]);
	if(bird.jumped >= 10)
		window.draw(arrowOnSprite);
	else
		window.draw(arrowOffSprite);
	
	bird.render( window );
	if(GameState == midGame)
	{
		pipes.render( window );
		bird.render( window );
		score.render( window );
	}
	if(GameState == postGame)
		window.draw(FiftyPercentOpaqueSprite);
	window.draw(text);
	window.display();
}

void Game::handleEvent(sf::Event event)
{
	if(GameState == preGame)
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			if(event.key.code == sf::Keyboard::Space)
			{
				bird.jump();
				GameState = midGame;
				preGameMusic.stop();
				midGameMusic.play();
			}
		default:
			break;
		}
	}
	else if(GameState == midGame)
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			if(event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Up)
			{
				bird.jump();
			}
			else if(event.key.code == sf::Keyboard::Right)
			{
				if(bird.jumped >= 10)
				{
					bg_x_pos_increment = 2;
					pipes.moveForwards();
					bird.setRotationIncrement(-5);
					bird.jumped = 0;
				}
			}
		default:
			break;
		}
	}
	else if(GameState == postGame)
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			if(event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Return)
			{
				reset();
				midGameMusic.play();
			}
			break;
		default:
			break;
		}
	}
}

void Game::reset()
{
	GameState = midGame;
	text.setString("");
	bird.reset();
	pipes.reset();
	score.reset();
}

void Game::birdDies()
{
    reset();
}

void Game::GameOver()
{
	if(score.isHighScore())
		cout << "You got a highscore!";
	GameState = postGame;
	text.setString("Game Over!");
}

bool Game::isBirdAlive()
{
    if(bird.getPosition().y > 563)
        return false;
    if(bird.getPosition().y < 0)
        return false;
	if(pipes.isCollision(bird.getPosition()))
		return false;
    else
        return true;
}