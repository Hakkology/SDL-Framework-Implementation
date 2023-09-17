#ifndef _GAMES_ASTEROIDS_ASTEROIDSMISSILE__H__
#define _GAMES_ASTEROIDS_ASTEROIDSMISSILE__H__

#include "triangle.h"
#include "rectangle.h"
#include "asteroidsactor.h"


class AsteroidsMissile : public AsteroidsActor
{
public:

	AsteroidsMissile();
	void Init(const SpriteSheet& spriteSheet, const std::string& animationsPath, const Vector2D& direction, const Vector2D& position, const Color& spriteColour = White());
	void Update(uint32_t dt, const Rectangle& boundary);
	inline Circle const GetCollisionBox() const { return a_CollisionBoundary; }

	void Hit(bool exploding);
	void SetFirstAnimation();
	inline bool IsHit() const { return a_Hit; }

private:
	bool a_Hit;
	bool a_Exploding;
	Circle a_CollisionBoundary;
};

#endif  //!_GAMES_ASTEROIDS_ASTEROIDSMISSILE__H__