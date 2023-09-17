#include "asteroidsactor.h"
#include "screen.h"
#include "line2D.h"

AsteroidsActor::AsteroidsActor():a_Speed(0.0f), a_RotationAngle(0.0f){
    
}

void AsteroidsActor::Init(const SpriteSheet& spriteSheet, const std::string& animationsPath, const Vector2D& initialPos, float movementSpeed, const Color& spriteColour)
{
	Actor::Init(spriteSheet, animationsPath, initialPos, spriteColour);
	a_MovementDirection = Vector2D(0, -1);
	a_LookingDirection = Vector2D(0, -1);
	a_Speed = movementSpeed;
	a_RotationAngle = 0;	
}

void AsteroidsActor::Update(uint32_t dt)
{
	Vector2D velocity = a_MovementDirection * (float)dt * a_Speed;
	m_Sprite.MoveBy(velocity);
	m_Sprite.Update(dt);
}

void AsteroidsActor::Draw(Screen& screen)
{
	float rotationAngle = a_LookingDirection.AngleBetween(Vector2D(0, -1));

	m_Sprite.Draw(screen, -1 * rotationAngle);
}

void AsteroidsActor::WrapAroundBoundary(const Rectangle& boundary)
{
	Vector2D topLeft = m_Sprite.GetBoundingBox().GetTopLeftPoint();
	Vector2D position = topLeft;

	if (topLeft.GetX() < boundary.GetTopLeftPoint().GetX())
	{
		position += Vector2D(boundary.GetWidth(), 0);
	}
	if (topLeft.GetX() >= boundary.GetBottomRightPoint().GetX())
	{
		position -= Vector2D(boundary.GetWidth(), 0);
	}
	if (topLeft.GetY() < boundary.GetTopLeftPoint().GetY())
	{
		position += Vector2D(0, boundary.GetHeight());
	}
	if (topLeft.GetY() >= boundary.GetBottomRightPoint().GetY())
	{
		position -= Vector2D(0, boundary.GetHeight());
	}

	m_Sprite.MoveTo(position);
}

void AsteroidsActor::Rotate(const float angle)
{
	// This is how the sprite should rotate
	Vector2D pointInBoundary = m_Sprite.GetBoundingBox().GetCenterPoint() + a_LookingDirection * m_Sprite.GetBoundingBox().GetHeight() / 2;
	pointInBoundary.Rotate(angle, m_Sprite.GetBoundingBox().GetCenterPoint());
	Vector2D direction = pointInBoundary - m_Sprite.GetBoundingBox().GetCenterPoint();

	a_LookingDirection = direction.GetUnitVector();
}