#include "pacmanlevel.h"
#include "filecommandloader.h"
#include "screen.h"
#include "pacmanplayer.h"
#include "app.h"
#include "circle.h"

bool PacmanLevel::Init(const std::string &levelPath, PacmanPlayer* noptrPacman){

    pnoptrPacman = noptrPacman;

    bool levelLoaded = LoadLevel(levelPath);
    if (levelLoaded)
    {
        ResetLevel();
    }
    return levelLoaded;
}

void PacmanLevel::Update(uint32_t dt){

    BoundaryEdge edge;

    for(auto& wall: pWalls){

        if (wall.HasCollided(pnoptrPacman->GetBoundingBox(), edge))
        {
            Vector2D offset = wall.GetCollisionOffset(pnoptrPacman->GetBoundingBox());
            pnoptrPacman->MoveBy(offset * 1.1f);
            pnoptrPacman->Stop();
        }
    }

    for(Tile t: pTiles) {
        if (t.isTeleportTile) {
            Rectangle teleportTileAABB(t.position , t.width, static_cast<float>(pTileHeight));

            if (teleportTileAABB.Intersects(pnoptrPacman->GetBoundingBox())) {
                Tile* teleportToTile = GetTileForSymbol(t.teleportToSymbol);
                assert(teleportToTile);

                if (teleportToTile->isTeleportTile) {

                    Vector2D newPosition = teleportToTile->position + teleportToTile->offset;
                    pnoptrPacman->MoveTo(newPosition);
                }
            }
        }
    }
}

void PacmanLevel::Draw(Screen &screen){

    // Debug for walls
    for(const auto& wall: pWalls){

        screen.Draw(wall.GetRectangle(), Blue()); 
    }

    for (const auto& pellet : pPellets){
        if (!pellet.eaten)
        {
            if (!pellet.powerPellet)
            {
                screen.Draw(pellet.pBBox, White());
            }
            else
            {
                Circle c (pellet.pBBox.GetCenterPoint(), pellet.pBBox.GetWidth()/2.0f);
                screen.Draw(c, White(), true, White());
            }
        }
    }

    for (auto& pellet : pPellets){

        if (!pellet.eaten)
        {
            if (pnoptrPacman -> GetEatingBoundingBox().Intersects(pellet.pBBox))
            {
                pellet.eaten = true;
                pnoptrPacman ->AteItem(pellet.score);

                if (pellet.powerPellet)
                {
                    pnoptrPacman->ResetGhostEatenMultiplier();
                }
            }
        }
    }
}

bool PacmanLevel::WillCollide(const Rectangle &bbox, PacmanMovement direction) const
{
    Rectangle bBox = bbox;

    bBox.MoveBy(GetMovementVector(direction));
    
    BoundaryEdge edge;

    for(const auto& wall: pWalls){

        if (wall.HasCollided(bBox, edge))
        {
            return true;
        }
    }
    return false;
}

void PacmanLevel::ResetLevel(){
    
    ResetPellets();
    if (pnoptrPacman)
    {
        pnoptrPacman -> MoveTo(pPacmanSpawnLocation);
        pnoptrPacman -> ResetToFirstAnimation();
    }
}

void PacmanLevel::ResetPellets(){

    pPellets.clear();

    const uint32_t PELLET_SIZE =2 ;
    const uint32_t PADDING = static_cast<uint32_t>(pTileHeight);

    uint32_t startingY = pLayoutOffset.GetY() + PADDING + pTileHeight -1;
    uint32_t startingX = PADDING + 3;

    const uint32_t LEVEL_HEIGHT = pLayoutOffset.GetY() + 32 * pTileHeight;

    Pellet p;
    p.score = 10;

    uint32_t row =0;

    for (uint32_t y = startingY; y < LEVEL_HEIGHT; y += PADDING, ++row)
    {
        for (uint32_t x = startingX, col =0;  x < App::Singleton().Width(); x+= PADDING, ++col)
        {
            if (row == 0 || row == 22)
            {
                if (col == 0 || col ==25)
                {
                    p.powerPellet = 1;
                    p.score = 50;
                    p.pBBox = Rectangle(Vector2D (x-3, y-3), pTileHeight, pTileHeight);
                    pPellets.push_back(p);

                    p.powerPellet = 0;
                    p.score = 10;

                    continue;
                }
            }
            Rectangle rect = Rectangle(Vector2D(x,y), PELLET_SIZE, PELLET_SIZE);

            bool found = false;

            for (const Excluder& wall: pWalls){
                if (wall.GetRectangle().Intersects(rect))
                {
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                for( const Tile& excludePelletTile: pExclusionTiles){
                    if (excludePelletTile.excludePelletTile)
                    {
                        Rectangle tileAABB(excludePelletTile.position, excludePelletTile.width, pTileHeight);
                        
                        if (tileAABB.Intersects(rect))
                        {
                            found = true;
                            break;
                        }
                    }
                }
            }
            
            if (!found)
            {
                p.pBBox = rect;
                pPellets.push_back(p);
            }
            
        }
    }
}

bool PacmanLevel::LoadLevel(const std::string &levelPath)
{
    FileCommandLoader fileLoader;

    Command tileWidthCommand;
    tileWidthCommand.command = "tile_width";
    tileWidthCommand.parseFunc = [this](ParseFuncParams params){
        pTiles.back().width =  FileCommandLoader::ReadInt(params);
    };
    fileLoader.AddCommand(tileWidthCommand);

    Command tileHeightCommand;
    tileHeightCommand.command = "tile_height";
    tileHeightCommand.parseFunc = [this](ParseFuncParams params){
        pTileHeight =  FileCommandLoader::ReadInt(params);
    };
    fileLoader.AddCommand(tileHeightCommand);

    Command tileCommand;
    tileCommand.command = "tile";
    tileCommand.parseFunc = [this](ParseFuncParams params){
        pTiles.push_back(Tile());
    };
    fileLoader.AddCommand(tileCommand);

    Command tileSymbolCommand;
    tileSymbolCommand.command = "tile_symbol";
    tileSymbolCommand.parseFunc = [this](ParseFuncParams params){
        pTiles.back().symbol =  FileCommandLoader::ReadChar(params);
    };
    fileLoader.AddCommand(tileSymbolCommand);

    Command tileCollisionCommand;
    tileCollisionCommand.command = "tile_collision";
    tileCollisionCommand.parseFunc = [this](ParseFuncParams params){
        pTiles.back().collidable =  FileCommandLoader::ReadInt(params);
    };
    fileLoader.AddCommand(tileCollisionCommand);

    Vector2D layoutOffset;

    Command layoutOffsetCommand;
    layoutOffsetCommand.command = "layout_offset";
    layoutOffsetCommand.parseFunc = [&layoutOffset, this](ParseFuncParams params){
        pLayoutOffset =  FileCommandLoader::ReadSize(params);
        layoutOffset = pLayoutOffset;
    };
    fileLoader.AddCommand(layoutOffsetCommand);

    Command tileIsTeleportTileCommand;
    tileIsTeleportTileCommand.command = "tile_is_teleport_tile";
    tileIsTeleportTileCommand.parseFunc = [this](ParseFuncParams params){
        pTiles.back().isTeleportTile = FileCommandLoader::ReadInt(params);
    };
    fileLoader.AddCommand(tileIsTeleportTileCommand);

    Command tileToTeleportToCommand;
    tileToTeleportToCommand.command = "tile_teleport_to_symbol";
    tileToTeleportToCommand.parseFunc = [this](ParseFuncParams params){
        pTiles.back().teleportToSymbol = FileCommandLoader::ReadChar(params);
    };
    fileLoader.AddCommand(tileToTeleportToCommand);

    Command tileOffsetCommand;
    tileOffsetCommand.command = "tile_offset";
    tileOffsetCommand.parseFunc = [this](ParseFuncParams params){
        pTiles.back().offset = FileCommandLoader::ReadSize(params);
    };
    fileLoader.AddCommand(tileOffsetCommand);

    Command tileExcludePelletCommand;
    tileExcludePelletCommand.command = "tile_exclude_pellet";
    tileExcludePelletCommand.parseFunc = [this](ParseFuncParams params){
        pTiles.back().excludePelletTile = FileCommandLoader::ReadInt(params);
    };
    fileLoader.AddCommand(tileExcludePelletCommand);

    Command tilePacmanSpawnPointCommand;
    tilePacmanSpawnPointCommand.command = "tile_pacman_spawn_point";
    tilePacmanSpawnPointCommand.parseFunc = [this](ParseFuncParams params){
        pTiles.back().pacmanSpawnPoint = FileCommandLoader::ReadInt(params);
    };
    fileLoader.AddCommand(tilePacmanSpawnPointCommand);

    Command layoutCommand;
    layoutCommand.command = "layout";
    layoutCommand.commandType = COMMAND_MULTI_LINE;
    layoutCommand.parseFunc = [&layoutOffset, this](ParseFuncParams params){

        // startingX updated to move the map a little to the right.
        int startingX = layoutOffset.GetX();

        for (int c = 0; c < params.line.length(); ++c)
        {
            Tile* tile = GetTileForSymbol(params.line[c]);

            if (tile)
            {
                tile->position = Vector2D(startingX, layoutOffset.GetY());

                if (tile-> collidable >0)
                {
                    Excluder wall;
                    wall.Init(Rectangle(Vector2D(startingX, layoutOffset.GetY()), tile->width, static_cast<int>(pTileHeight)));
                    pWalls.push_back(wall);
                }

                if (tile-> pacmanSpawnPoint >0)
                {
                    pPacmanSpawnLocation = Vector2D(startingX + tile->offset.GetX(), layoutOffset.GetY() + tile->offset.GetY());
                }
                
                if (tile->excludePelletTile >0)
                {
                    pExclusionTiles.push_back(*tile);
                }
            
                startingX += tile->width;
            }
        }
        layoutOffset += Vector2D(0, pTileHeight);
    };

    fileLoader.AddCommand(layoutCommand);

    return fileLoader.LoadFile(levelPath);
}

PacmanLevel::Tile *PacmanLevel::GetTileForSymbol(char symbol)
{
    for (size_t i = 0; i < pTiles.size(); ++i)
    {
        if (pTiles[i].symbol == symbol)
        {
            return &pTiles[i];
        }
    }
    return nullptr;
}


