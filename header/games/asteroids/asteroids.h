#ifndef _GAMES_ASTEROIDS_ASTEROIDS__H__
#define _GAMES_ASTEROIDS_ASTEROIDS__H__

#include "circle.h"
#include "spritesheet.h"
#include "asteroidsactor.h"

enum AsteroidSize
{
	SMALL = 0,
	MEDIUM,
	LARGE,
	EXTRALARGE,
	NONE
};

class Asteroid
{
public:
	Asteroid();
	void Init(const SpriteSheet& spriteSheet, const Vector2D& direction, const Vector2D& position, AsteroidSize size, const Color& spriteColour = White());
	void Draw(Screen& screen);
	void Update(uint32_t dt, const Rectangle& boundary);

	inline const unsigned int GetSize() const { return static_cast<int>(a_Size); }
	inline bool IsDestroyed() const { return a_Destroyed; }
	inline float const GetRadious() const { return a_CollisionBoundaries[0].GetRadius(); }
	inline Vector2D const Position() const { return a_SpriteBox.GetCenterPoint(); }
	inline std::vector<Circle> const GetCollisionBoxes() const{ return a_CollisionBoundaries; }
	inline bool Reproduce() const { return a_Reproduce; }
	inline int const GetScore() const { return a_Score; }

	void Hit(const bool split = true);

private:
	std::string GetSpriteName();
	void WrapAroundBoundary(Rectangle* box, const Rectangle& boundary);
	void WrapAroundBoundary(Circle* colBoundary, const Rectangle& boundary);
	void GetBoundaryOffset(Vector2D& offset, int boundaryID);

private:
	std::vector<Circle> a_CollisionBoundaries;
	Vector2D a_LookingDirection;
	Vector2D a_MovementDirection;
	
	AsteroidSize a_Size;
	int a_Score;
	bool a_Destroyed;
	float a_Rotation;
	bool a_Reproduce;

	SpriteSheet a_SpriteSheet;
	Sprite a_Sprite;
	Rectangle a_SpriteBox;

	static const float a_RotatingSpeed;
	static const float a_Speed;
};

#endif  //!_GAMES_ASTEROIDS_ASTEROIDS__H__