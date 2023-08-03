#include "buttonoptionsScene.h"
#include "app.h"
#include "bmpfont.h"
#include "utilities.h"

ButtonOptionsScene::ButtonOptionsScene(const std::vector<std::string> &optionNames, const Color &textColor):
    bHighlightedOption(0)
{
    const BmpFont& font = App::Singleton().GetFont();

    for (size_t i = 0; i < optionNames.size(); ++i)
    {
        bButtons.push_back(Button(font, textColor));
        bButtons.back().SetButtonText(optionNames[i]);
    }
    
    if (optionNames.size() > 0)
    {
        bButtons[bHighlightedOption].SetHighlighted(true);
    }
    
}

void ButtonOptionsScene::Init(){

    ButtonAction upAction;
    upAction.key = GameController::UpKey();
    upAction.action = [this](uint32_t dt, InputState state){
        if (GameController::IsPressed(state))
        {
            SetPreviousButtonHighlighted();
        }
    };
    sGameController.AddInputActionForKey(upAction);

    ButtonAction downAction;
    downAction.key = GameController::DownKey();
    downAction.action = [this](uint32_t dt, InputState state){
        if (GameController::IsPressed(state))
        {
            SetNextButtonHighlighted();
        }
    };
    sGameController.AddInputActionForKey(downAction);

    ButtonAction acceptAction;
    acceptAction.key = GameController::ActionKey();
    acceptAction.action = [this](uint32_t dt, InputState state){
        if (GameController::IsPressed(state))
        {
            ExecuteCurrentButtonAction();
        }
    };
    sGameController.AddInputActionForKey(acceptAction);

    uint32_t height = App::Singleton().Height();
    uint32_t width = App::Singleton().Width();

    const BmpFont& font = App::Singleton().GetFont();

    Size fontSize = font.GetSizeOf(bButtons[0].GetButtonText());

    const int BUTTON_PAD = 10;
    unsigned int buttonHeight = fontSize.height + BUTTON_PAD * 2;
    uint32_t maxButtonWidth = fontSize.width;

    for(const auto& button: bButtons){

        Size s = font.GetSizeOf(button.GetButtonText());

        if (s.width > maxButtonWidth)
        {
            maxButtonWidth = s.width;
        }
    }

    maxButtonWidth += BUTTON_PAD * 2;

    const uint32_t Y_PAD = 1;
    uint32_t yOffset = height/2 - ((buttonHeight + Y_PAD) * static_cast<uint32_t>(bButtons.size()))/2;

    for(auto& button: bButtons){
        
        button.Init(Vector2D(width/2 - maxButtonWidth/2, yOffset), maxButtonWidth, buttonHeight);
        yOffset += buttonHeight + Y_PAD;
    }

    bButtons[bHighlightedOption].SetHighlighted(true);
}

void ButtonOptionsScene::Update(uint32_t dt){

}

void ButtonOptionsScene::Draw(Screen &theScreen){

    for(auto& button: bButtons){
        button.Draw(theScreen);
    }
}

void ButtonOptionsScene::SetButtonActions(const std::vector<Button::ButtonAction> &buttonActions){

    for (size_t i = 0; i < bButtons.size(); ++i)
    {
        bButtons[i].SetButtonAction(buttonActions[i]);
    }
}

void ButtonOptionsScene::SetNextButtonHighlighted(){

    bHighlightedOption = (bHighlightedOption +1) % bButtons.size();
    HighlightCurrentButton();
}

void ButtonOptionsScene::SetPreviousButtonHighlighted(){

    --bHighlightedOption;

    if (bHighlightedOption <0)
    {
        bHighlightedOption = static_cast<int>(bButtons.size()) -1;
    }
    HighlightCurrentButton();
    
}

void ButtonOptionsScene::ExecuteCurrentButtonAction(){

    bButtons[bHighlightedOption].ExecuteAction();
}

void ButtonOptionsScene::HighlightCurrentButton(){

    for(auto& button: bButtons){

        button.SetHighlighted(false);
    }
    bButtons[bHighlightedOption].SetHighlighted(true);
}
