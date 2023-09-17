#ifndef _GAMES_ASTEROIDS_ASTEROIDSACTOR__H__
#define _GAMES_ASTEROIDS_ASTEROIDSACTOR__H__

#include <string>

#include "vector2D.h"
#include "rectangle.h"
#include "circle.h"
#include "color.h"
#include "actor.h"

class Screen;
class SpriteSheet;

class AsteroidsActor : public Actor
{
public:

	AsteroidsActor();
	virtual ~AsteroidsActor() {}
	virtual void Init(const SpriteSheet& spriteSheet, const std::string& animationsPath, const Vector2D& initialPos, float movementSpeed, const Color& spriteColour = White());
	virtual void Update(uint32_t dt) override;
	virtual void Draw(Screen& screen) override;

	void WrapAroundBoundary(const Rectangle& boundary);
	void Rotate(const float angle);

	inline void SetMovementDirection(Vector2D direction) { a_MovementDirection = direction; }
	inline void SetMovementSpeed(const float speed) { a_Speed = speed; }
	inline Vector2D GetLookingDirection() const { return a_LookingDirection; }
	inline void Stop() { a_Speed = 0.0f; }

protected:
	float a_Speed;
	Vector2D a_MovementDirection;
	Vector2D a_LookingDirection;

private:
	float a_RotationAngle;
	Vector2D a_Offset;
};

#endif  //!_GAMES_ASTEROIDS_ASTEROIDSACTOR__H__