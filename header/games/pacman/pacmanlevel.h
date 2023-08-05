#ifndef GAMES_PACMAN_PACMANLEVEL__H__
#define GAMES_PACMAN_PACMANLEVEL__H__

#include <string>
#include <vector>

#include "vector2D.h"
#include "excluder.h"

class Screen;

class PacmanLevel{

public:

    bool Init (const std::string& levelPath);
    void Update (uint32_t dt);
    void Draw (Screen& screen);

private:

    struct Tile
    {
        Vector2D position = Vector2D::Zero;
        int width = 0;
        int collidable = 0;
        char symbol = '-';

    };

    bool LoadLevel (const std::string& levelPath);
    Tile* GetTileForSymbol(char symbol);

    std::vector<Excluder> pWalls;
    std::vector<Tile> pTiles;

    Vector2D pLayoutOffset;
    size_t pTileHeight;
    
};


#endif  //!GAMES_PACMAN_PACMANLEVEL__H__