#ifndef _GAMES_ACTOR__H__
#define _GAMES_ACTOR__H__

#include <string>

#include "animatedsprite.h"
#include "rectangle.h"
#include "color.h"

class Screen;
class SpriteSheet;
class Vector2D;

class Actor
{
public:

	virtual ~Actor() {}
	virtual void Init(const SpriteSheet& spriteSheet, const std::string& animationsPath, const Vector2D& initialPos, const Color& spriteColour = White());

	virtual void Update(uint32_t dt) = 0;
	virtual void Draw(Screen& screen);

	inline bool IsFinishedAnimation() const { return m_Sprite.IsFinishedPlayingAnimation(); }

	inline Vector2D Position() const { return m_Sprite.Position(); }
	inline const Color& GetSpriteColour() const { return m_Sprite.GetColor(); }

	inline void MoveBy(const Vector2D& delta) { m_Sprite.MoveBy(delta); }
	inline void MoveTo(const Vector2D& position) { m_Sprite.SetPosition(position); }

	inline const Rectangle GetBoundingBox() const { return m_Sprite.GetBoundingBox(); }


protected:
	void SetAnimation(const std::string& animationName, bool looped);

	AnimatedSprite m_Sprite;

};

#endif  //!_GAMES_ACTOR__H__