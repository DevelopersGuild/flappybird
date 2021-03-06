#include "Assets.h"
#include "Bird.h"
#include "Constants.h"
#include "Game.h"
#include "Pipes.h"
#include "Score.h"
#include "Background.h"
#include "PowerUp.h"
#include <iostream>
#include <fstream>

using namespace std;

 enum 
{
	 preGame, midGame, postGame
}GameState;

Game::Game()
	: window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Flappy Bird")
{
    //Turning vertical-sync on causes window.display() to pause the app until 1/60th of a second has passed.
	window.setVerticalSyncEnabled(true);
	
	loadResources();
	
	GameState = preGame;
	highScore = false;
	resetPopUp = false;
	aboutPopUp = false;
	popUps[0] = &highScore;
	popUps[1] = &resetPopUp;
	popUps[2] = &aboutPopUp;

	GameSound::preGameMusicOn();
} 

void Game::loadResources()
{
	scoreBackgroundTexture.loadFromFile(GetAssetPath("Assets/ScoreBackground.png"));
	scoreBackgroundSprite.setTexture(scoreBackgroundTexture);
	scoreBackgroundSprite.setOrigin(226, 116);
	scoreBackgroundSprite.setPosition(400, 300);

	scoreBackgroundHighTexture.loadFromFile(GetAssetPath("Assets/ScoreBackgroundHigh.png"));
	scoreBackgroundHighSprite.setTexture(scoreBackgroundHighTexture);
	scoreBackgroundHighSprite.setOrigin(226, 116);
	scoreBackgroundHighSprite.setPosition(400, 300);

	gameTitleTexture.loadFromFile(GetAssetPath("Assets/gameTitle.png"));
	gameTitleSprite.setTexture(gameTitleTexture);
	gameTitleSprite.setOrigin(285,33);
	gameTitleSprite.setPosition(400,100);

	gameoverTexture.loadFromFile(GetAssetPath("Assets/gameoverText.png"));
	gameoverSprite.setTexture(gameoverTexture);
	gameoverSprite.setOrigin(231,5);
	gameoverSprite.setPosition(400,100);

	resetScorePlaqueTexture.loadFromFile(GetAssetPath("Assets/ResetScorePlaque.png"));
	resetScorePlaqueSprite.setTexture(resetScorePlaqueTexture);
	resetScorePlaqueSprite.setOrigin(400, 300);
	resetScorePlaqueSprite.setPosition(400, 300);

	aboutSectionTexture.loadFromFile(GetAssetPath("Assets/About.png"));
	aboutSectionSprite.setTexture(aboutSectionTexture);
	aboutSectionSprite.setOrigin(400, 300);
	aboutSectionSprite.setPosition(400, 300);

	font.loadFromFile(GetAssetPath("Assets/Karmatic.ttf"));

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
	startInstructions.setPosition(200,200);
	startInstructions.setString("HIT SPACE OR UP TO PLAY!");

	restartInstructions.setFont(font);
	restartInstructions.setCharacterSize(25);
	restartInstructions.setColor(sf::Color::White);
	restartInstructions.setPosition(190,450);
	restartInstructions.setString("HIT ENTER TO PLAY AGAIN!");

	keyInstructions.setFont(font);
	keyInstructions.setCharacterSize(15);
	keyInstructions.setColor(sf::Color::White);
	keyInstructions.setPosition(0,0);
	keyInstructions.setString("HIT 'r' TO RESET HIGHSCORE \nHIT 'a' TO VIEW THE ABOUT SECTION");
	
	credits.setFont(font);
	credits.setCharacterSize(25);
	credits.setColor(sf::Color(207, 173, 89, 255));
	credits.setString(CREDITS_TEXT);
	credits.setPosition(230, 150);

	FiftyPercentOpaqueTexture.loadFromFile(GetAssetPath("Assets/50Opaque.png"));
	FiftyPercentOpaqueSprite.setTexture(FiftyPercentOpaqueTexture);
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
	background.update( seconds );
	ground.update( seconds );
	arrows.update( seconds );
	bird.preGameUpdate( seconds );
}

void Game::midGameUpdate(float seconds)
{
	if(GameState != postGame)
	{
		background.update( seconds );
		ground.update ( seconds );
		arrows.update(seconds);
	}
	bird.update( seconds , pipes.getVelocity());
	if(GameState == midGame)
		pipes.update( seconds, powerUp.getPowerUpType() );
	score.update( pipes.getScore() );
	powerUp.update ( seconds, bird.getPosition());
}

void Game::render()
{
	window.clear();

	background.render( window );
	arrows.render( window, pipes.getArrowOn() );
	bird.render( window );
	pipes.render( window );
	ground.render( window );

	if(GameState == preGame)
	{
		window.draw(gameTitleSprite);
		window.draw(startInstructions);
		window.draw( keyInstructions );
		arrows.preGameRender( window );
		window.draw( startInstructions );
		if(resetPopUp == true)
		{
			window.draw(FiftyPercentOpaqueSprite);
			window.draw(resetScorePlaqueSprite);
		}
		if(aboutPopUp == true)
		{
			window.draw(FiftyPercentOpaqueSprite);
			window.draw(aboutSectionSprite);
			window.draw(credits);
		}
	}
	else if(GameState == midGame)
	{
		score.render( window );
		powerUp.render( window );
	}
	else if(GameState == postGame)
	{
		window.draw(FiftyPercentOpaqueSprite);
		window.draw(gameoverSprite);

		if(highScore)
			window.draw(scoreBackgroundHighSprite);
		else
			window.draw(scoreBackgroundSprite);

		window.draw(finalScoreText);
		window.draw(bestScoreText);
		window.draw(highScoreText);
		window.draw(restartInstructions);
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
			if((event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Up) && noPopUpsAreOpen())
			{
				bird.jump();
				GameState = midGame;
				GameSound::preGameMusicOff();
				GameSound::midGameMusicOn();
			}
			if (event.key.code == sf::Keyboard::R  && noPopUpsAreOpen())
				resetPopUp = true;

			if(event.key.code == sf::Keyboard::Y && resetPopUp == true)
			{
				score.deleteHighScore();
				resetPopUp = false;
			}
			if(event.key.code == sf::Keyboard::N && resetPopUp == true)
				resetPopUp = false;
			if(event.key.code == sf::Keyboard::Escape)
				resetPopUp = false;

			if(event.key.code == sf::Keyboard::A && noPopUpsAreOpen())
				aboutPopUp = true;
			if(event.key.code == sf::Keyboard::Escape && aboutPopUp == true)
				aboutPopUp = false;
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
				if(pipes.getArrowOn())
				{
					background.moveForwards();
					pipes.moveForwards();
					ground.moveForwards();
					powerUp.moveForwards( pipes.getVelocity() );
					bird.jumped = 0;
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
				GameSound::preGameMusicOn();
			}
			break;
		default:
			break;
		}
	}
}

void Game::reset()
{
	background.reset();
	ground.reset();
	bird.reset();
	pipes.reset();
	score.reset();
	powerUp.reset();
	highScoreText.setString("");
	highScore = false;
}

void Game::GameOver()
{
	string best;
	
	GameSound::birdCollision();
	GameSound::midGameMusicOff();

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
	if(bird.getPosition().y > 550)
       return false;
	if(bird.getPosition().y < 0)
       return false;
	if(pipes.isCollision(bird.getPosition(), powerUp.getPowerUpType()))
		return false;
    else
        return true;
}

bool Game::noPopUpsAreOpen()
{
	for(int i = 0; i < NUMBER_OF_POPUPS; i++)
		if(*popUps[i])
			return false;
	return true;
}