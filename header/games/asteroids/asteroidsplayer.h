#ifndef _GAMES_ASTEROIDS_ASTEROIDSPLAYER__H__
#define _GAMES_ASTEROIDS_ASTEROIDSPLAYER__H__

#include <vector>

#include "triangle.h"
#include "asteroidsactor.h"

class Screen;
class Rectangle;


enum class RotationDirection
{
	ROTATE_LEFT = -1,
	ROTATE_RIGHT = 1
};


class AsteroidsPlayer : public AsteroidsActor
{
public:

	AsteroidsPlayer();
	virtual void Init(const SpriteSheet& spriteSheet, const std::string& animationsPath, const Color& spriteColour = White());
	virtual void Update(uint32_t dt, const Rectangle& boundary);

	void Accelerate(uint32_t dt);
	void Rotate(RotationDirection rotationDirection);
	void MoveTo(const Vector2D& position);
	void AddToScore(uint32_t score);
	void Reset();
	void CrashedIntoAsteroid();
	void ResetToFirstAnimation();
	void ResetPosition();

	inline void LooseLife() { --a_Lives; }
	inline Circle const GetCollisionBox() const { return a_CollisionBoundary; }
	inline const int GetLives() const { return a_Lives; }
	inline const uint32_t GetScore() { return a_Score; }

private:
	void ResetScore();

private:
	int a_Lives;
	uint32_t a_Score;
	bool a_IsDying;
	Circle a_CollisionBoundary;

	float PLAYER_ACCELERATION = ASTEROIDS_PLAYER_ACCELERATION;
	float MAX_SPEED = ASTEROIDS_PLAYER_MAX_SPEED;
};

#endif  //!_GAMES_ASTEROIDS_ASTEROIDSPLAYER__H__