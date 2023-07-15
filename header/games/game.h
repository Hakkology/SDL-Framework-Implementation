#ifndef GAMES_GAME_H
#define GAMES_GAME_H

#include <string>
#include <stdint.h>

class GameController;
class Screen;

class Game{

public:

    virtual ~Game(){}
    virtual void Update(uint32_t dt) = 0;
    virtual void Draw (Screen& screen) = 0;
    virtual std::string GetName() const = 0;

};

#endif