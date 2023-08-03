#ifndef GRAPHICS_ANIMATIONPLAYER__H__
#define GRAPHICS_ANIMATIONPLAYER__H__

#include <stdint.h>
#include <vector>

#include "animation.h"

class AnimationPlayer
{

public:
    AnimationPlayer();

    bool Init (const std::string& animationsPath);
    bool Play(const std::string& animationName, bool looped);
    void Pause();
    void Stop();
    void Update(uint32_t dt);

    AnimationFrame GetCurrentAnimationFrame() const;
    inline uint32_t IsFinishedPlaying() const {return mIsFinishedPlaying;}
    inline uint32_t GetCurrentFrameNumber() const {return mFrame;}

private:

    uint32_t mTime;
    std::vector<Animation> mAnimations;
    size_t mCurrentAnimation;
    uint32_t mFrame;

    bool mLooped;
    bool mIsPlaying;
    bool mIsFinishedPlaying;

};


#endif  //!__ANIMATIONPLAYER__H__