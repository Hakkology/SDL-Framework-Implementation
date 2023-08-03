#include "button.h"
#include "screen.h"

Button::Button(const BmpFont &BmpFont, const Color &textColor, const Color &highlightColor):
bBmpFont(BmpFont), bTextColor(textColor), bHighlightColor(highlightColor), bTitle(""), bHighlighted(false), bAction(nullptr){

}

void Button::Init(Vector2D topLeft, unsigned int width, unsigned int height){

    bBBox = Rectangle(topLeft, width, height);
}

void Button::Draw(Screen &theScreen){

    theScreen.Draw(bBmpFont, bTitle, bBmpFont.GetDrawPosition(bTitle, bBBox, BFXA_CENTER, BFYA_CENTER), bTextColor);

    if (bHighlighted)
    {
        theScreen.Draw(bBBox, bHighlightColor);
    }
    
}

void Button::ExecuteAction(){

    bAction();
}
