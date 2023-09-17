#include "asteroidsplayer.h"
#include "screen.h"
#include "rectangle.h"
#include "app.h"

#include <iostream>

AsteroidsPlayer::AsteroidsPlayer(): a_Lives(3), a_IsDying(false){

}

void AsteroidsPlayer::Init(const SpriteSheet& spriteSheet, const std::string& animationsPath, const Color& spriteColour)
{
	Vector2D startPosition = Vector2D((App::Singleton().Width() / 2), (App::Singleton().Height() / 2));
	AsteroidsActor::Init(spriteSheet, animationsPath, startPosition, 0.0f, spriteColour);
	a_CollisionBoundary = Circle(Vector2D::Zero, m_Sprite.GetBoundingBox().GetHeight() / 2);
	//a_Score.PlayerName = "ABC";
	Reset();
}

void AsteroidsPlayer::Update(uint32_t dt, const Rectangle& boundary)
{
	if (a_IsDying)
	{
		AsteroidsActor::Update(dt);
		a_IsDying = !IsFinishedAnimation();
		return;
	}

	AsteroidsActor::Update(dt);
	WrapAroundBoundary(boundary);
	a_CollisionBoundary.MoveTo(m_Sprite.GetBoundingBox().GetCenterPoint());
}

void AsteroidsPlayer::Accelerate(uint32_t dt)
{
	SetAnimation("thrusters", false);
	Vector2D currentVelocity = a_MovementDirection * a_Speed;

	Vector2D acceleration = a_LookingDirection * PLAYER_ACCELERATION * dt;
	Vector2D finalVelocity = currentVelocity + acceleration;

	a_Speed = finalVelocity.Magnitude();
	SetMovementDirection(finalVelocity.GetUnitVector());

	if (a_Speed > MAX_SPEED)
	{
		a_Speed = MAX_SPEED;
	}
}

void AsteroidsPlayer::Rotate(RotationDirection rotationDirection)
{
	float rotationAngle = static_cast<float>(rotationDirection) * 0.3f;
	AsteroidsActor::Rotate(rotationAngle);
}

void AsteroidsPlayer::MoveTo(const Vector2D& position)
{
	Actor::MoveTo(position);
	a_CollisionBoundary.MoveTo(position);
}

void AsteroidsPlayer::AddToScore(uint32_t score)
{
	a_Score += score;
}

void AsteroidsPlayer::Reset()
{
	ResetToFirstAnimation();
	ResetPosition();
	ResetScore();
	a_Lives = 3;
	a_Speed = 0;
}

void AsteroidsPlayer::CrashedIntoAsteroid()
{
	SetAnimation("explosion", false);
	a_IsDying = true;
	LooseLife();
}

void AsteroidsPlayer::ResetScore()
{
	a_Score = 0;
}

void AsteroidsPlayer::ResetPosition()
{
	a_MovementDirection = Vector2D(0, -1);
	a_LookingDirection = Vector2D(0, -1);
	
	Vector2D startPosition = Vector2D((App::Singleton().Width() / 2), (App::Singleton().Height() / 2));
	MoveTo(startPosition);
}

void AsteroidsPlayer::ResetToFirstAnimation()
{
	SetAnimation("ship", true);
}