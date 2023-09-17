#include "actor.h"
#include "vector2D.h"

void Actor::Init(const SpriteSheet& spriteSheet, const std::string& animationsPath, const Vector2D& initialPos, const Color& spriteColour)
{
	m_Sprite.Init(animationsPath, spriteSheet, spriteColour);
	m_Sprite.SetPosition(initialPos);
}

void Actor::Draw(Screen& screen)
{
	m_Sprite.Draw(screen);
}

void Actor::SetAnimation(const std::string& animationName, bool looped)
{
	m_Sprite.SetAnimation(animationName, looped);
}