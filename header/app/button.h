#ifndef APP_BUTTON__H__
#define APP_BUTTON__H__

#include <string>
#include <functional>

#include "rectangle.h"
#include "color.h"
#include "bmpfont.h"
#include "inputaction.h"

class Screen;

class Button{

public:

    using ButtonAction = std::function<void(void)>;

    Button(const BmpFont& BmpFont, const Color& textColor, const Color& highlightColor = White());
    void Init (Vector2D topLeft, unsigned int width, unsigned int height);
    void Draw(Screen& theScreen);
    void ExecuteAction();

    inline void SetButtonText(const std::string& text) {bTitle = text;}
    inline const std::string& GetButtonText () const {return bTitle;}
    inline void SetHighlighted (bool highlighted) {bHighlighted = highlighted;}
    inline bool IsHighlighted () const {return bHighlighted;}
    inline void SetButtonAction(ButtonAction action) {bAction = action;}


private:

    const BmpFont& bBmpFont;

    std::string bTitle;
    Rectangle bBBox;

    bool bHighlighted;
    ButtonAction bAction;

    Color bHighlightColor;
    Color bTextColor;

};

#endif  //!__BUTTON__H__