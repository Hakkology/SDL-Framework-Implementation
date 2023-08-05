#ifndef GAMES_PACMAN_PACMAN__H__
#define GAMES_PACMAN_PACMAN__H__



#include "game.h"

class Pacman : public Game{

    virtual void Init(GameController& controller) override;
    virtual void Update(uint32_t dt) override;
    virtual void Draw (Screen& screen) override;
    virtual const std::string& GetName() const override;
};

#endif  //!GAMES_PACMAN_PACMAN__H__