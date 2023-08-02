#ifndef GRAPHICS_BMPFONT_H
#define GRAPHICS_BMPFONT_H

#include <stdint.h>

#include "spritesheet.h"
#include "utilities.h"
#include "constants.h"

class Vector2D;
class Rectangle;

enum BmpFontXAlignment{

    BFXA_LEFT = 0,
    BFXA_CENTER,
    BFXA_RIGHT
};

enum BmpFontYAlignment{

    BFYA_TOP = 0,
    BFYA_CENTER,
    BFYA_BOTTOM
};

class BmpFont{

public:

    BmpFont(){}

    bool Load(const std::string& name);
    Size GetSizeOf (const std::string& str) const;
    Vector2D GetDrawPosition(const std::string& str, const Rectangle& box, BmpFontXAlignment xAlign=BFXA_LEFT, BmpFontYAlignment yAlign = BFYA_TOP) const;

    inline const SpriteSheet& GetSpriteSheet() const {return bFontSheet;}
    inline const uint32_t GetFontSpacingBetweenLetters() const {return FontSpacingBetweenLetters;}
    inline const uint32_t GetFontSpacingBetweenWords() const {return FontSpacingBetweenWords;}

private:

    SpriteSheet bFontSheet;

};

#endif