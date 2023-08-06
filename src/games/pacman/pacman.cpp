#include "pacman.h"
#include "app.h"

void Pacman::Init(GameController &controller){

    pLevel.Init(App::Singleton().GetBasePath()+ "Assets/Pacman_level.txt");
}

void Pacman::Update(uint32_t dt){

    pLevel.Update(dt);
}

void Pacman::Draw(Screen &screen){

    pLevel.Draw(screen);
}

const std::string &Pacman::GetName() const{

    static std::string name = "Pacmania!";
    return name;
}
