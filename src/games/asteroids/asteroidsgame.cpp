#include <stdlib.h>
#include <time.h>

#include "asteroidsgame.h"
#include "screen.h"
#include "triangle.h"
#include "app.h"

#include "gamecontroller.h"

void AsteroidsGame::Init(GameController& controller)
{
	// Init the player
	a_AsteroidsSpriteSheet.Load("AsteroidsSprites");
	a_AnimationsPath = App::Singleton().GetBasePath() + "Assets/AsteroidsAnimations.txt";
	a_Player.Init(a_AsteroidsSpriteSheet, a_AnimationsPath);

	// Set up the game controller
	ButtonAction accelerateAction;
	accelerateAction.key = GameController::UpKey();
	accelerateAction.action = [this](uint32_t dt, InputState state)
	{
		if (GameController::IsPressed(state))
		{
			a_Player.Accelerate(dt);
		}
	};

	controller.AddInputActionForKey(accelerateAction);

	ButtonAction rotateLeftAction;
	rotateLeftAction.key = GameController::LeftKey();
	rotateLeftAction.action = [this](uint32_t dt, InputState state)
	{
		if (GameController::IsPressed(state))
		{
			a_Player.Rotate(RotationDirection::ROTATE_LEFT);
		}
	};

	controller.AddInputActionForKey(rotateLeftAction);

	ButtonAction rotateRightAction;
	rotateRightAction.key = GameController::RightKey();
	rotateRightAction.action = [this](uint32_t dt, InputState state)
	{
		if (GameController::IsPressed(state))
		{
			a_Player.Rotate(RotationDirection::ROTATE_RIGHT);
		}
	};

	controller.AddInputActionForKey(rotateRightAction);

	ButtonAction fireAction;
	fireAction.key = GameController::PushKey();
	fireAction.action = [this](uint32_t dt, InputState state)
	{
		if (GameController::IsPressed(state))
		{
			ShootMissile(a_Player.Position(), a_Player.GetLookingDirection());
		}
	};

	controller.AddInputActionForKey(fireAction);

	ButtonAction backAction;
	backAction.key = GameController::CancelKey();
	backAction.action = [this](uint32_t dt, InputState state)
	{
		if (a_GameState == AsteroidsGameState::GAME_OVER && GameController::IsPressed(state))
		{
			// Go back to the starting scene
			App::Singleton().PopScene();
		}
	};

	controller.AddInputActionForKey(backAction);

	a_Font = App::Singleton().GetFont();
	ResetGame();
}

void AsteroidsGame::Update(uint32_t dt)
{
	if (a_GameState == AsteroidsGameState::LEVEL_STARTING)
	{
		a_LevelStartingTimer += dt;
		if (a_LevelStartingTimer >= LEVEL_STARTING_TIME)
		{
			a_LevelStartingTimer = 0;
			a_GameState = AsteroidsGameState::PLAY_GAME;
		}

		if (a_LevelStartingTimer % 1000 == 0)
		{
			--a_CountDown;
		}
	}
	else if (a_GameState == AsteroidsGameState::PLAY_GAME)
	{
		a_Player.Update(dt, a_MapBoundary);
		UpdateMisiles(dt);
		UpdateAsteroids(dt);
		CalculateCollisions(a_Player);
	}
	else if (a_GameState == AsteroidsGameState::LOSS_LIFE)
	{
		// Let the misiles and the player finish their dying animations
		a_Player.Update(dt, a_MapBoundary);
		UpdateMisiles(dt);

		bool finishedMissileAnimation = true;
		for (const auto& missile : a_Missiles)
		{
			finishedMissileAnimation *= missile.IsFinishedAnimation();
		}

		if (a_Player.IsFinishedAnimation() && finishedMissileAnimation)
		{
			if (a_Player.GetLives() > 0)
			{
				ResetPlayer();
			}
			else
			{
				// Update the high score table
				// a_HighScoreTable.UpdateTable(m_Player.GetScore());
				// a_HighScoreTable.SaveToFile();
				a_GameState = AsteroidsGameState::GAME_OVER;
			}
		}
	}
}

void AsteroidsGame::UpdateMisiles(uint32_t dt)
{
	if (a_Missiles.size() > 0)
	{
		for (size_t i = 0; i < a_Missiles.size(); i++)
		{
			// Update the misile and check if it should exist
			a_Missiles[i].Update(dt, a_MapBoundary);
		}
	}

	auto i = remove_if(a_Missiles.begin(), a_Missiles.end(), [&](AsteroidsMissile missile) { return !a_MapBoundary.ContainsPoint(missile.Position()); });
	if (i != a_Missiles.end())
	{
		a_Missiles.erase(i);
	}
}

void AsteroidsGame::UpdateAsteroids(uint32_t dt)
{
	size_t size = a_Asteroids.size();
	
	// Generate 2 new asteroids when a big one is destroyed
	for (size_t i = 0; i < size; i++)
	{
		if (a_Asteroids[i].IsDestroyed() && a_Asteroids[i].GetSize() > 0 && a_Asteroids[i].Reproduce())
		{
			Asteroid currentAsteroid = a_Asteroids[i];
			GenerateAsteroids(2, currentAsteroid.Position(), static_cast<AsteroidSize>(currentAsteroid.GetSize() - 1));
		}
	}

	// Delete the destroyed asteroids from the map
	auto k = remove_if(a_Asteroids.begin(), a_Asteroids.end(), [&](Asteroid asteroid) { return asteroid.IsDestroyed(); });
	if (k != a_Asteroids.end())
	{
		a_Asteroids.erase(k);
	}

	// If all asteroids are destroyed we add new asteroids
	if (a_Asteroids.size() > 0)
	{
		// Update the position of the remaining asteroid
		for (auto& asteroid : a_Asteroids)
		{
			asteroid.Update(dt, a_MapBoundary);
		}
	}
	else
	{
		GenerateAsteroids(3);
	}

	// Generate new asteroids as time passes
	a_Accumulator += dt;
	if (a_Accumulator >= 1000)
	{
		if (a_Asteroids.size() < 15)
		{
			GenerateAsteroids(1);
			a_Accumulator = 0;
		}
	}
}

void AsteroidsGame::Draw(Screen& screen)
{

	if (a_Asteroids.size() > 0)
	{
		for (auto& asteroid : a_Asteroids)
		{
			asteroid.Draw(screen);
		}
	}

	if (a_GameState == AsteroidsGameState::PLAY_GAME || a_GameState == AsteroidsGameState::LOSS_LIFE)
	{
		a_Player.Draw(screen);

		if (a_Missiles.size() > 0)
		{
			for (auto& missile : a_Missiles)
			{
				missile.Draw(screen);
			}
		}
	}
	else
	{	
		uint32_t aWidth = App::Singleton().Width();
		uint32_t aHeight = App::Singleton().Height();

		Vector2D textPos;
		Rectangle rect = Rectangle(Vector2D(aWidth / 2, aHeight / 2) - Vector2D(3, 3), 6, 6);
		
		if (a_GameState == AsteroidsGameState::LEVEL_STARTING)
		{
			if (a_CountDown > 0)
			{
				textPos = a_Font.GetDrawPosition(std::to_string(a_CountDown), rect, BmpFontXAlignment::BFXA_CENTER, BmpFontYAlignment::BFYA_CENTER);
				screen.Draw(a_Font, std::to_string(a_CountDown), textPos, Red());
			}
		}
		else
		{
			textPos = a_Font.GetDrawPosition("Game Over!", rect, BmpFontXAlignment::BFXA_CENTER, BmpFontYAlignment::BFYA_CENTER);
			screen.Draw(a_Font, "Game Over!", textPos, Red());
		}
	}
}


void AsteroidsGame::CalculateCollisions(AsteroidsPlayer& player)
{
	std::vector<Circle> collisionBoundaries;
	for (size_t i = 0; i < a_Asteroids.size(); i++)
	{
		// Collision Asteroid to player
		collisionBoundaries = a_Asteroids[i].GetCollisionBoxes();
		for (auto& boundary : collisionBoundaries)
		{
			if (boundary.Intersects(a_Player.GetCollisionBox()))
			{
				a_Asteroids[i].Hit(false);
				a_Player.CrashedIntoAsteroid();
				a_GameState = AsteroidsGameState::LOSS_LIFE;
				break;
			}

			// Collision Asteroid to missile
			for (size_t j = 0; j < a_Missiles.size(); j++)
			{
				if (!a_Missiles[j].IsHit())
				{
					if (boundary.Intersects(a_Missiles[j].GetCollisionBox()))
					{
						a_Missiles[j].Hit(a_Asteroids[i].GetSize() == 0);
						a_Asteroids[i].Hit();
						a_Player.AddToScore(a_Asteroids[i].GetScore());
						break;
					}
				}
			}
		}
	}
}

void AsteroidsGame::GenerateAsteroids(const int n, const Vector2D& position, AsteroidSize size)
{
	uint32_t aWidth = App::Singleton().Width();
	uint32_t aHeight = App::Singleton().Height();
	float x, y;
	Vector2D newPosition;
	int newSize;
	srand(time(NULL));

	int corridor = 40;

	// This should generate both the split asteroids and the new asteroids in the surrounding map
	for (size_t i = 0; i < n; i++)
	{
		if (size == AsteroidSize::EXTRALARGE)
		{
			++a_NumAsteroids;
		}

		if (position == Vector2D::Zero)
		{
			// We are placing the asteroid in the surronding area of the map (i.e not in the center nor where the player is)
			float y = (float)(rand() % aHeight);
			x = 0.0f;
			
			if (y > corridor || y < aHeight - corridor)
			{
				if ((rand() % 2) == 1)
				{
					x = (float)(rand() % corridor);
				}
				else
				{
					x = (float)(aWidth - (rand() % corridor));
				}
			}
			else
			{
				x = (float)(rand() % aWidth);
			}

			newPosition = Vector2D(x, y);
		}
		else
		{
			newPosition = position;
		}

		if (size == AsteroidSize::NONE)
		{
			// We choose a random size 
			newSize = rand() % 4;
		}
		else 
		{
			newSize = static_cast<int>(size);
		}
		
		Vector2D randomDir((float)(rand() % 10), (float)(rand() % 10));

		Asteroid asteroid;
		asteroid.Init(a_AsteroidsSpriteSheet, randomDir.GetUnitVector(), newPosition, static_cast<AsteroidSize>(newSize));
		a_Asteroids.push_back(asteroid);
	}
}

void AsteroidsGame::ShootMissile(const Vector2D& position, const Vector2D& direction)
{
	if (a_Missiles.size() < 3)
	{
		// When player presses the action button we fire a misile
		AsteroidsMissile missile;
		missile.Init(a_AsteroidsSpriteSheet, a_AnimationsPath, a_Player.GetLookingDirection(), a_Player.Position());
		a_Missiles.push_back(missile);
	}
}

void AsteroidsGame::ResetGame()
{
	a_MapBoundary = { Vector2D::Zero, Vector2D((App::Singleton().Width()), (App::Singleton().Height())) };
	a_Player.Reset();
	a_Accumulator = 0;
	a_Missiles.clear();
	ResetAsteroids();
	a_CountDown = 3;
	a_GameState = AsteroidsGameState::LEVEL_STARTING;

	//m_HighScoreTable.Init("Asteroids");
}

void AsteroidsGame::ResetPlayer()
{
	a_Player.ResetPosition();
	a_Player.ResetToFirstAnimation();
	ResetAsteroids();
	a_CountDown = 3;
	a_GameState = AsteroidsGameState::LEVEL_STARTING;
}

void AsteroidsGame::ResetAsteroids()
{
	a_Asteroids.clear();
	GenerateAsteroids(3);
}

const std::string& AsteroidsGame::GetName() const
{
	static const std::string name = "Astaurads!";
	return name;
}
