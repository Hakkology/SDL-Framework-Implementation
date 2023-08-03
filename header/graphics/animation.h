#ifndef GRAPHICS_ANIMATION__H__
#define GRAPHICS_ANIMATION__H__

#include <string>
#include <vector>

#include "vector2D.h"
#include "color.h"
#include "constants.h"

struct AnimationFrame
{
    std::string frame = "";
    std::string overlay = "";
    Color frameColor = White();
    Color overlayColor = White();
    Vector2D size;
    Vector2D offset = Vector2D::Zero;
    int frameColorSet = 0;
};

class Animation
{

public:

    AnimationFrame GetAnimationFrame (uint32_t frameNum) const;

    inline void AddFrame(const std::string& frame) {mFrames.push_back(frame);}
    inline void AddFrameColor(const Color& color) {mFrameColors.push_back(color);}
    inline void AddOverlayFrameColor (const Color& color) {mOverlayColors.push_back(color);}
    inline void AddFrameOffset (const Vector2D& offset) {mFrameOffsets.push_back(offset);}

    inline void SetSpriteSheetName(const std::string& spriteSheetName) {mSpriteSheetName = spriteSheetName;}
    inline const std::string& GetSpriteSheetName() const {return mSpriteSheetName;}

    inline void SetName (const std::string& animationName) {mAnimationName = animationName;}
    inline const std::string& GetName() const {return mAnimationName;}

    inline Vector2D Size() const {return mSize;}
    inline void SetSize(const Vector2D& size) {mSize = size;}

    inline void SetFPS (int fps) {mFPS = fps;}

    inline void SetOverlay (const std::string& overlayName) {mOverlay = overlayName;}
    inline const std::string& OverlayName() const {return mOverlay;}

    size_t NumFrames() const {return mFrames.size();}
    size_t NumFrameColors() const {return mFrameColors.size();}
    size_t NumOverlayColors() const {return mOverlayColors.size();}
    size_t NumFrameOffsets() const {return mFrameOffsets.size();}

    static std::vector<Animation> LoadAnimations(const std::string& animationFilePath);


private:

    std::string mAnimationName;
    std::string mSpriteSheetName;
    std::string mOverlay;
    std::vector<std::string> mFrames;
    std::vector<Color> mFrameColors;
    std::vector<Color> mOverlayColors;
    std::vector<Vector2D> mFrameOffsets;
    
    Vector2D mSize;
    int mFPS;
};

#endif  //!__ANIMATION__H__