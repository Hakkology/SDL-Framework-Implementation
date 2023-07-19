#include "gameScene.h"

GameScene::GameScene(std::unique_ptr<Game> optrGame):sGame(std::move(optrGame)){

}

void GameScene::Init(){

    sGame->Init(sGameController);
}

void GameScene::Update(uint32_t dt){

    sGame->Update(dt);
}

void GameScene::Draw(Screen &screen){

    sGame->Draw(screen);
}

const std::string& GameScene::GetSceneName() const {

    return sGame->GetName();
}