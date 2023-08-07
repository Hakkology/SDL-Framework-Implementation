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
    void ResetLevel ();
    inline Vector2D GetLayoutOffset() const {return pLayoutOffset;}
    inline Vector2D GetPacmanSpawnLocation () const {return pPacmanSpawnLocation;}

private:

    struct Tile{
        Vector2D position = Vector2D::Zero;
        Vector2D offset = Vector2D::Zero;
        int width = 0;
        int collidable = 0;
        int isTeleportTile = 0;
        int excludePelletTile = 0;
        int pacmanSpawnPoint = 0;
        char teleportToSymbol = 0;
        char symbol = '-';
    };

    struct Pellet{
        uint32_t score=0;
        Rectangle pBBox;
        int powerPellet =0;
        int eaten = 0;
    };

    bool LoadLevel (const std::string& levelPath);
    Tile* GetTileForSymbol(char symbol);

    void ResetPellets ();

    std::vector<Excluder> pWalls;
    std::vector<Tile> pTiles;
    std::vector<Tile> pExclusionTiles;
    std::vector<Pellet> pPellets;

    Vector2D pLayoutOffset;
    Vector2D pPacmanSpawnLocation;
    size_t pTileHeight;

    PacmanPlayer* pnoptrPacman;
    
};


#endif  //!GAMES_PACMAN_PACMANLEVEL__H__