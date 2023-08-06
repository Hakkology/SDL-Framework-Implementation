#ifndef GRAPHICS_ANIMATEDSPRITE__H__
#define GRAPHICS_ANIMATEDSPRITE__H__

#include <stdint.h>
#include <string>

#include "animationplayer.h"
#include "vector2D.h"
#include "color.h"

class Rectangle;
class Screen;
class SpriteSheet;

class AnimatedSprite{

public:

    AnimatedSprite();

    void Init (const std::string& animationsPath, const SpriteSheet& spriteSheet, const Color& color = White());
    void Update (uint32_t dt);
    void Draw (Screen& theScreen);

    void SetAnimation(const std::string& animationName, bool looped);

    Vector2D Size () const;
    void Stop();
    const Rectangle GetBoundingBox() const;
    
    inline Vector2D Position() const {return mPosition;}
    inline void SetPosition(const Vector2D& position) {mPosition += position;}
    inline void MoveBy(const Vector2D& delta) {mPosition += delta;}
    inline bool IsFinishedPlayingAnimation() const {return mAnimationPlayer.IsFinishedPlaying();}
    inline const Color& GetColor() const {return mColor;}
    inline const SpriteSheet* GetSpriteSheet() const {return mnoptrSpriteSheet;}

private:

    const SpriteSheet* mnoptrSpriteSheet;
    AnimationPlayer mAnimationPlayer;
    Vector2D mPosition;
    Color mColor;
};

#endif