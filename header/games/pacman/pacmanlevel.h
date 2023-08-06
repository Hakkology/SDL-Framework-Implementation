#ifndef GAMES_PACMAN_PACMANLEVEL__H__
#define GAMES_PACMAN_PACMANLEVEL__H__

#include <string>
#include <vector>

#include "vector2D.h"
#include "excluder.h"
#include "pacmangameutils.h"

class Screen;
class PacmanPlayer;

class PacmanLevel{

public:

    bool Init (const std::string& levelPath, PacmanPlayer* noptrPacman);
    void Update (uint32_t dt);
    void Draw (Screen& screen);

    bool WillCollide(const Rectangle& bbox, PacmanMovement direction) const;

private:

    struct Tile
    {
        Vector2D position = Vector2D::Zero;
        Vector2D offset = Vector2D::Zero;
        int width = 0;
        int collidable = 0;
        int isTeleportTile = 0;
        char teleportToSymbol = 0;
        char symbol = '-';
    };

    bool LoadLevel (const std::string& levelPath);
    Tile* GetTileForSymbol(char symbol);

    std::vector<Excluder> pWalls;
    std::vector<Tile> pTiles;

    Vector2D pLayoutOffset;
    size_t pTileHeight;

    PacmanPlayer* pnoptrPacman;
    
};


#endif  //!GAMES_PACMAN_PACMANLEVEL__H__