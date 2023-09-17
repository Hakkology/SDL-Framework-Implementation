#ifndef _GAMES_ASTEROIDS_ASTEROIDSGAME__H__
#define _GAMES_ASTEROIDS_ASTEROIDSGAME__H__

#include "game.h"
#include "asteroidsplayer.h"
#include "asteroidsmissile.h"
#include "rectangle.h"
#include "asteroids.h"
#include "app.h"

enum class AsteroidsGameState
{
	LEVEL_STARTING = 0,
	PLAY_GAME,
	GAME_OVER,
	LOSS_LIFE
};

class AsteroidsGame : public Game
{
public:
	virtual void Init(GameController& controller);
	virtual void Update(uint32_t dt);
	virtual void Draw(Screen& screen);
	virtual const std::string& GetName() const;

	void CalculateCollisions(AsteroidsPlayer& player);

	void GenerateAsteroids(const int n, const Vector2D& position = Vector2D::Zero, AsteroidSize size = AsteroidSize::NONE);

private:
	void ShootMissile(const Vector2D& position, const Vector2D& direction);
	void ResetGame();
	void ResetPlayer();
	void ResetAsteroids();
	void UpdateMisiles(uint32_t dt);
	void UpdateAsteroids(uint32_t dt);

private:
	AsteroidsPlayer a_Player;
	Rectangle a_MapBoundary;
	std::vector<Asteroid> a_Asteroids;
	std::vector<AsteroidsMissile> a_Missiles;
	int a_NumAsteroids;
	uint64_t a_Accumulator;
	
	SpriteSheet a_AsteroidsSpriteSheet;
	std::string a_AnimationsPath;
	AsteroidsGameState a_GameState;
	uint32_t a_LevelStartingTimer;
	uint32_t a_CountDown;

	BmpFont a_Font;
	//HighScoreTable m_HighScoreTable;
};

#endif  //!_GAMES_ASTEROIDS_ASTEROIDSGAME__H__