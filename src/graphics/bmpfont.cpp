#include "bmpfont.h"
#include "rectangle.h"
#include "vector2D.h"

bool BmpFont::Load(const std::string& name){
    return bFontSheet.Load(name);
}

Size BmpFont::GetSizeOf (const std::string& str) const{

    Size textSize;
    size_t length = str.length();
    
    int i =0;

    for(char c: str){

        if(c== ' '){
            textSize.width += GetFontSpacingBetweenWords();
            ++i;
            continue;
        }

        Sprite sprite = bFontSheet.GetSprite(std::string("") + c);
        textSize.height = textSize.height < sprite.height ? sprite.height : textSize.height;
        textSize.width += sprite.width;

        if(i+1 < length){
            textSize.width += GetFontSpacingBetweenLetters();
        }

        ++i;
    }

    return textSize;
}

Vector2D BmpFont::GetDrawPosition(const std::string& str, const Rectangle& box, BmpFontXAlignment xAlign, BmpFontYAlignment yAlign) const{

    Size textSize = GetSizeOf(str);

    uint32_t x = 0;
    uint32_t y = 0;

    if(xAlign == BFXA_CENTER){

        x = box.GetWidth() / 2- textSize.width /2 ;
    }else if(xAlign == BFXA_RIGHT){

        x = box.GetWidth() - textSize.width;
    }
    x += box.GetTopLeftPoint().GetX();

    if(yAlign == BFYA_CENTER){

        y = (box.GetHeight()/2) - textSize.height/2;
    }
    else if(yAlign == BFYA_BOTTOM){

        y = box.GetHeight() - textSize.height;
    }
    y += box.GetTopLeftPoint().GetY();

    return Vector2D(x,y);
}