#ifndef GAMES_PACMAN_PACMANLEVEL__H__
#define GAMES_PACMAN_PACMANLEVEL__H__

#include <string>
#include <vector>
#include <random>

#include "vector2D.h"
#include "bmpimage.h"
#include "excluder.h"
#include "pacmangameutils.h"
#include "spritesheet.h"

class Screen;
class PacmanPlayer;
class PacmanGhost;

class PacmanLevel{

public:

    bool Init (const std::string& levelPath, const SpriteSheet* noptrSpriteSheet, PacmanPlayer* noptrPacman);
    void Update (uint32_t dt);
    void Draw (Screen& screen);

    bool WillCollide(const Rectangle& bbox, PacmanMovement direction) const;
    bool IsLevelOver() const;
    
    void IncreaseLevel();
    void ResetToFirstLevel();
    void ResetLevel ();

    inline Vector2D GetLayoutOffset() const {return pLayoutOffset;}
    inline Vector2D GetPacmanSpawnLocation () const {return pPacmanSpawnLocation;}
    inline const std::vector<Vector2D>& GetGhostSpawnPoints() { return pGhostSpawnPoints;}

private:

    struct Tile{
        Vector2D position = Vector2D::Zero;
        Vector2D offset = Vector2D::Zero;
        int width = 0;
        int collidable = 0;
        int isTeleportTile = 0;
        int excludePelletTile = 0;
        int pacmanSpawnPoint = 0;
        int itemSpawnPoint = 0;
        int blinkySpawnPoint = 0;
        int inkySpawnPoint = 0;
        int pinkySpawnPoint = 0;
        int clydeSpawnPoint = 0;
        char teleportToSymbol = 0;
        char symbol = '-';
    };

    struct Pellet{
        uint32_t score=0;
        Rectangle pBBox;
        int powerPellet =0;
        int eaten = 0;
    };

    struct BonusItem
    {
        uint32_t score = 0;
        Rectangle bbox;
        int eaten = 0;
        int spawned = 0;
        int spawnTime = -1;
    };

    struct BonusItemLevelProperties{

        uint32_t score = 0;
        std::string spriteName = "";
        uint32_t begin = 0;
        uint32_t end = 0;
    };
    
    Tile* GetTileForSymbol(char symbol);

    void ResetPellets ();
    void GetBonusItemSpriteName(std::string& spriteName, uint32_t& score) const;
    void SpawnBonusItem();

    bool LoadLevel (const std::string& levelPath);
    bool ShouldSpawnBonusItem() const;
    bool HasEatenAllPellets() const;
    size_t NumPelletsEaten() const;

    std::default_random_engine pGenerator;

    BonusItem pBonusItem;
    std::string pBonusItemSpriteName;
    const SpriteSheet* pnoptrSpriteSheet;

    std::vector<Vector2D> pGhostSpawnPoints;
    std::vector<BonusItemLevelProperties> pBonusItemProperties;
    std::vector<Excluder> pWalls;
    std::vector<Tile> pTiles;
    std::vector<Tile> pExclusionTiles;
    std::vector<Pellet> pPellets;

    Vector2D pLayoutOffset;
    Vector2D pPacmanSpawnLocation;
    size_t pTileHeight;

    int pCurrentLevel;

    PacmanPlayer* pnoptrPacman;
    
};


#endif  //!GAMES_PACMAN_PACMANLEVEL__H__