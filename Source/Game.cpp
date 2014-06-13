#include "Assets.h"
#include "Bird.h"
#include "Constants.h"
#include "Game.h"
#include "Pipes.h"
#include "Score.h"
#include <iostream>
#include <fstream>

using namespace std;

 enum 
{
	 preGame, midGame, postGame
}GameState;

Game::Game()
	: window(sf::VideoMode(800, 600), "Flappy Bird")
{
    //Turning vertical-sync on causes window.display() to pause the app until 1/60th of a second has passed.
	window.setVerticalSyncEnabled(true);
	
	loadResources();
	
	GameState = preGame;
	highScore = false;
}

void Game::loadResources()
{
	backgroundTexture.loadFromFile(GetAssetPath("Assets/background.png"));
	background_X_pos = 0;
	background_x_pos_increment = 0.8;
	//Initialize background sprites.
	for(int i = 0; i < 2; i++)
	{
		backgroundSprite[i].setTexture(backgroundTexture);
		backgroundSprite[i].setTextureRect(sf::IntRect(0, 0, 1024, 256));
		backgroundSprite[i].setScale(1, 2.343); //To fill entire window with sprite
	}

	scoreBackgroundTexture.loadFromFile(GetAssetPath("Assets/ScoreBackground.png"));
	scoreBackgroundSprite.setTexture(scoreBackgroundTexture);
	scoreBackgroundSprite.setOrigin(226, 116);
	scoreBackgroundSprite.setPosition(400, 300);

	scoreBackgroundHighTexture.loadFromFile(GetAssetPath("Assets/ScoreBackgroundHigh.png"));
	scoreBackgroundHighSprite.setTexture(scoreBackgroundHighTexture);
	scoreBackgroundHighSprite.setOrigin(226, 116);
	scoreBackgroundHighSprite.setPosition(400, 300);

	font.loadFromFile(GetAssetPath("Assets/Karmatic.ttf"));

	gameTitle.setFont(font);
	gameTitle.setCharacterSize(50);
	gameTitle.setColor(sf::Color::Black);
	gameTitle.setPosition(200,100);
	gameTitle.setString("Flappy Bird");

	gameOverText.setFont(font);
	gameOverText.setCharacterSize(44);
	gameOverText.setColor(sf::Color::White);
	gameOverText.setPosition(230,100);
	gameOverText.setString("Game Over!");

	finalScoreText.setFont(font);
	finalScoreText.setCharacterSize(30);
	finalScoreText.setColor(sf::Color::White);
	finalScoreText.setPosition(520,250);

	bestScoreText.setFont(font);
	bestScoreText.setCharacterSize(30);
	bestScoreText.setColor(sf::Color::White);
	bestScoreText.setPosition(520,330);

	startInstructions.setFont(font);
	startInstructions.setCharacterSize(25);
	startInstructions.setColor(sf::Color::White);
	startInstructions.setPosition(200,400);
	startInstructions.setString("HIT SPACE OR UP TO PLAY!");

	restartInstructions.setFont(font);
	restartInstructions.setCharacterSize(25);
	restartInstructions.setColor(sf::Color::White);
	restartInstructions.setPosition(200,450);
	restartInstructions.setString("HIT ENTER TO PLAY AGAIN!");

	FiftyPercentOpaqueTexture.loadFromFile(GetAssetPath("Assets/50Opaque.png"));
	FiftyPercentOpaqueSprite.setTexture(FiftyPercentOpaqueTexture);

	midGameMusic.openFromFile(GetAssetPath("Assets/MidGame.ogg"));
	midGameMusic.setVolume(20);
	midGameMusic.setLoop(true);
	
	preGameMusic.openFromFile(GetAssetPath("Assets/PreGame.ogg"));
	preGameMusic.setLoop(true);
	preGameMusic.setVolume(20);
	preGameMusic.play();

	birdDiesSoundBuffer.loadFromFile(GetAssetPath("Assets/BirdDies.ogg"));
	birdDiesSound.setBuffer(birdDiesSoundBuffer);
	
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
        }
		render();
	}
}

void Game::preGameUpdate(float seconds)
{
	if(background_X_pos <= -1024)
		background_X_pos = 0;
	if(background_x_pos_increment > 0.8)
		background_x_pos_increment -= 0.0625;

	backgroundSprite[0].setPosition(background_X_pos, 0);
	backgroundSprite[1].setPosition(background_X_pos + 1024, 0);
	background_X_pos -= background_x_pos_increment;
	
	arrows.update(seconds);
	bird.preGameUpdate( seconds );
}

void Game::midGameUpdate(float seconds)
{
	if(GameState != postGame)
	{
		if(background_X_pos <= -1024)
			background_X_pos = 0;
		if(background_x_pos_increment > 0.8)
			background_x_pos_increment -= 0.0625;

		backgroundSprite[0].setPosition(background_X_pos, 0);
		backgroundSprite[1].setPosition(background_X_pos + 1024, 0);
		background_X_pos -= background_x_pos_increment;
		
		arrows.update(seconds);
	}
	bird.update( seconds , pipes.getVelocity());
	if(GameState == midGame)
		pipes.update( seconds );
	score.update( pipes.getScore() );
}

void Game::render()
{
	window.clear();

	window.draw(backgroundSprite[0]);
	window.draw(backgroundSprite[1]);

	arrows.render( window, score.getArrowOn() );
	bird.render( window );
	pipes.render( window );

	if(GameState == midGame)
	{
		score.render( window );
	}
	else if(GameState == postGame)
	{
		window.draw(FiftyPercentOpaqueSprite);
		window.draw(gameOverText);

		if(highScore)
			window.draw(scoreBackgroundHighSprite);
		else
			window.draw(scoreBackgroundSprite);

		window.draw(finalScoreText);
		window.draw(bestScoreText);
		window.draw(highScoreText);
		window.draw(gameTitle);
		window.draw(restartInstructions);
	}
	else
	{
		window.draw(gameTitle);
		window.draw(startInstructions);
	}

	window.display();
}

void Game::handleEvent(sf::Event event)
{
	if(event.type == sf::Event::Closed)
		window.close();
	if(GameState == preGame)
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			if(event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Up)
			{
				bird.jump();
				GameState = midGame;
				preGameMusic.stop();
				midGameMusic.play();
			}
			break;
		default:
			break;
		}
	}
	else if(GameState == midGame)
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			if(event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Up)
			{
				bird.jump();
			}
			else if(event.key.code == sf::Keyboard::Right)
			{
				if(score.getArrowOn())
				{
					background_x_pos_increment = 2;
					pipes.moveForwards();
					bird.setRotationIncrement(-5);
					bird.jumped = 0;
					score.setArrowOn(false);
				}
			}
			break;
		default:
			break;
		}
	}
	else if(GameState == postGame)
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			if(event.key.code == sf::Keyboard::Return)
			{
				GameState = preGame;
				reset();
				preGameMusic.play();
			}
			break;
		default:
			break;
		}
	}
}

void Game::reset()
{
	bird.reset();
	pipes.reset();
	score.reset();
	highScoreText.setString("");
	highScore = false;
}

void Game::birdDies()
{
    reset();
}

void Game::GameOver()
{
	string best;
	birdDiesSound.play();
	midGameMusic.stop();

	if(score.isHighScore())
	{
		highScoreText.setString("New");
		highScore = true;
	}

	ifstream bestScore(GetAssetPath("Assets/HighScore.txt"));
	getline(bestScore, best);
	bestScore.close();

	bestScoreText.setString(best);
	GameState = postGame;
	finalScoreText.setString(to_string(static_cast<long long>(pipes.getScore())));
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
