#ifndef APP_BUTTONOPTIONSSCENE__H__
#define APP_BUTTONOPTIONSSCENE__H__

#include <string>
#include <vector>

#include "scene.h"
#include "button.h"

class ButtonOptionsScene: public Scene{

public:

    ButtonOptionsScene(const std::vector<std::string>& optionNames, const Color& textColor);

    virtual void Init () override;
    virtual void Update(uint32_t dt) override;
    virtual void Draw(Screen& theScreen) override;

    void SetButtonActions(const std::vector<Button::ButtonAction>& buttonActions);

private:

    void SetNextButtonHighlighted();
    void SetPreviousButtonHighlighted();
    void ExecuteCurrentButtonAction();
    void HighlightCurrentButton();

    std::vector<Button> bButtons;
    int bHighlightedOption;


};


#endif  