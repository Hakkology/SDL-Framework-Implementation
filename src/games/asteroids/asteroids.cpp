#include <string>

#include "asteroids.h"
#include "screen.h"
#include "rectangle.h"
#include "animatedsprite.h"
#include "app.h"



Asteroid::Asteroid() :a_Size(AsteroidSize::SMALL), a_Destroyed(false), a_Rotation(0), a_Reproduce(true), a_Score(0)
{
}

void Asteroid::Init(const SpriteSheet& spriteSheet, const Vector2D& direction, const Vector2D& position, AsteroidSize size, const Color& spriteColour)
{
	a_Size = size;
	a_SpriteSheet = spriteSheet;
	a_MovementDirection = direction;

	a_Sprite = spriteSheet.GetSprite(GetSpriteName());
	a_SpriteBox = Rectangle(position, a_Sprite.width, a_Sprite.height);

	Vector2D aWidth = Vector2D(App::Singleton().Width(), 0.0f);
	Vector2D aHeight = Vector2D(0.0f, App::Singleton().Height());
	
	// We need to create 4 boundaries at each side of the screen
	a_CollisionBoundaries.push_back(Circle(a_SpriteBox.GetCenterPoint(), (a_Sprite.width / 2)));
	a_CollisionBoundaries.push_back(Circle(a_SpriteBox.GetCenterPoint() - aWidth, (a_Sprite.width / 2)));
	a_CollisionBoundaries.push_back(Circle(a_SpriteBox.GetCenterPoint() + aWidth, (a_Sprite.width / 2)));
	a_CollisionBoundaries.push_back(Circle(a_SpriteBox.GetCenterPoint() - aHeight, (a_Sprite.width / 2)));
	a_CollisionBoundaries.push_back(Circle(a_SpriteBox.GetCenterPoint() + aHeight, (a_Sprite.width / 2)));
}

void Asteroid::Draw(Screen& screen)
{
	screen.Draw(a_SpriteSheet, GetSpriteName(), a_SpriteBox.GetTopLeftPoint(), White(), a_Rotation);
}

void Asteroid::Update(uint32_t dt, const Rectangle& boundary)
{
	a_Rotation += a_RotatingSpeed * dt;
	Vector2D delta = (a_MovementDirection * a_Speed * dt);

	// Update the sprite's location
	a_SpriteBox.MoveBy(delta);
	WrapAroundBoundary(&a_SpriteBox, boundary);

	Vector2D offset;
	Rectangle mapBoundary;

	for (size_t i = 0; i < a_CollisionBoundaries.size(); i++)
	{
		// Move the boundaries
		a_CollisionBoundaries[i].MoveBy(delta);

		// Get their individual map boundaries
		mapBoundary = boundary;
		GetBoundaryOffset(offset, i);
		mapBoundary.MoveBy(offset);

		WrapAroundBoundary(&a_CollisionBoundaries[i], mapBoundary);
	}
}

void Asteroid::GetBoundaryOffset(Vector2D& offset, int boundaryID)
{
	Vector2D aWidth = Vector2D(App::Singleton().Width(), 0.0f);
	Vector2D aHeight = Vector2D(0.0f, App::Singleton().Height());

	switch (boundaryID)
	{
	case 0:
		offset = Vector2D::Zero;
		break;
	case 1:
		offset = -aWidth;
		break;
	case 2:
		offset = aWidth;
		break;
	case 3:
		offset = -aHeight;
		break;
	case 4:
		offset = aHeight;
		break;
	}
}

void Asteroid::Hit(const bool split)
{
	a_Destroyed = true;
	a_Reproduce = split;

}

std::string Asteroid::GetSpriteName()
{
	std::string spriteName;

	switch (a_Size)
	{
		case AsteroidSize::SMALL:
		{
			spriteName = "small_rock";
			a_Score = 100;
			return spriteName;
		}
		case AsteroidSize::MEDIUM:
		{
			spriteName = "medium_rock";
			a_Score = 50;
			return spriteName;
		}
		case AsteroidSize::LARGE:
		{
			spriteName = "medium_rock2";
			a_Score = 20;
			return spriteName;
		}
		case AsteroidSize::EXTRALARGE:
		{
			spriteName = "big_rock";
			a_Score = 10;
			return spriteName;
		}
	}

	return spriteName;
}


void Asteroid::WrapAroundBoundary(Circle* collisionBoundary, const Rectangle& boundary)
{
	Vector2D centerPoint = collisionBoundary->GetCenterPoint();
	Vector2D position = centerPoint;

	if (centerPoint.GetX() < boundary.GetTopLeftPoint().GetX())
	{
		position += Vector2D(boundary.GetWidth(), 0);
	}
	if (centerPoint.GetX() >= boundary.GetBottomRightPoint().GetX())
	{
		position -= Vector2D(boundary.GetWidth(), 0);
	}
	if (centerPoint.GetY() < boundary.GetTopLeftPoint().GetY())
	{
		position += Vector2D(0, boundary.GetHeight());
	}
	if (centerPoint.GetY() >= boundary.GetBottomRightPoint().GetY())
	{
		position -= Vector2D(0, boundary.GetHeight());
	}

	collisionBoundary->MoveTo(position);
}

void Asteroid::WrapAroundBoundary(Rectangle* box, const Rectangle& boundary)
{
	Vector2D topLeft = box->GetTopLeftPoint();
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

	box->MoveTo(position);
}