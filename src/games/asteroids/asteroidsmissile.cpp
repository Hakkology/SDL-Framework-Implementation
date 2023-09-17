#include "asteroidsmissile.h"
#include "screen.h"


AsteroidsMissile::AsteroidsMissile() :a_Hit(false), a_Exploding(false){

}

void AsteroidsMissile::Init(const SpriteSheet& spriteSheet, const std::string& animationsPath, const Vector2D& direction, const Vector2D& position, const Color& spriteColour)
{
	AsteroidsActor::Init(spriteSheet, animationsPath, position, MISSILE_SPEED, spriteColour);
	a_LookingDirection = direction;
	a_MovementDirection = direction;
	a_CollisionBoundary = Circle(Vector2D::Zero, m_Sprite.GetBoundingBox().GetHeight() / 2);
	a_Hit = false;
	SetFirstAnimation();
}

void AsteroidsMissile::Update(uint32_t dt, const Rectangle& mapBoundary)
{
	if (a_Exploding)
	{
		m_Sprite.Update(dt);
		if (IsFinishedAnimation())
		{
			a_Exploding = false;
			MoveTo(Vector2D(-100.0f, 0.0f));
		}
		return;
	}

	Vector2D velocity = a_MovementDirection * MISSILE_SPEED;
	AsteroidsActor::Update(dt);
	a_CollisionBoundary.MoveTo(m_Sprite.GetBoundingBox().GetCenterPoint());
}

void AsteroidsMissile::Hit(bool exploding)
{
	a_Hit = true;
	if (exploding)
	{
		SetAnimation("explosion", false);
		a_Exploding = true;
	}
	else
	{
		MoveTo(Vector2D(-100.0f, 0.0f));
	}
	
}

void AsteroidsMissile::SetFirstAnimation()
{
	SetAnimation("missile", true);
}