#include "pacmanlevel.h"
#include "filecommandloader.h"
#include "screen.h"
#include "pacmanplayer.h"
#include "pacmanghost.h"
#include "app.h"
#include "circle.h"

bool PacmanLevel::Init(const std::string &levelPath, const SpriteSheet* noptrSpriteSheet){

    pCurrentLevel =0 ;
    pnoptrSpriteSheet = noptrSpriteSheet;
    pBonusItemSpriteName = "";

    std::random_device r;
    pGenerator.seed(r());

    pGhostSpawnPoints.resize(NUM_GHOSTS);

    bool levelLoaded = LoadLevel(levelPath);
    if (levelLoaded)
    {
        cout << "Level loaded successfully." << endl;
        ResetLevel();
    }
    return levelLoaded;
}

void PacmanLevel::Update(uint32_t dt, PacmanPlayer& pacman, std::vector<PacmanGhost>& ghosts, std::vector<PacmanGhostAI>& ghostAIs){

    for(const auto& wall: pWalls){

        BoundaryEdge edge;
        if (wall.HasCollided(pacman.GetBoundingBox(), edge))
        {
            Vector2D offset = wall.GetCollisionOffset(pacman.GetBoundingBox());
            pacman.MoveBy(offset);
            pacman.Stop();
        }

        for (auto& ghost: ghosts)
        {
            if (wall.HasCollided(ghost.GetBoundingBox(), edge))
            {
                Vector2D offset = wall.GetCollisionOffset(ghost.GetBoundingBox());
                ghost.MoveBy(offset);
                ghost.Stop();
            }
        }
    }

    for(const auto& gate : pGate){

        BoundaryEdge edge;
        if (gate.HasCollided(pacman.GetBoundingBox(), edge))
        {
            Vector2D offset = gate.GetCollisionOffset(pacman.GetBoundingBox());
            pacman.MoveBy(offset);
            pacman.Stop();
        }

        for (size_t i = 0; i<NUM_GHOSTS; ++i)
        {

            PacmanGhostAI ghostAI = ghostAIs[i];
            PacmanGhost ghost = ghosts[i];

            if (!(ghostAI.WantsToLeavePen() || ghostAI.IsEnteringPen()) && gate.HasCollided(ghost.GetBoundingBox(), edge))
            {
                Vector2D offset = gate.GetCollisionOffset(ghost.GetBoundingBox());
                ghost.MoveBy(offset);
                ghost.Stop();
            }
        }
    }

    for(Tile t: pTiles) {
        if (t.isTeleportTile) {
            Rectangle teleportTileAABB(t.position , t.width, static_cast<float>(pTileHeight));

            Tile* teleportToTile = GetTileForSymbol(t.teleportToSymbol);
            assert(teleportToTile);

            if (teleportToTile->isTeleportTile) {

                if (teleportTileAABB.Intersects(pacman.GetBoundingBox())) {

                    pacman.MoveTo(teleportToTile->position + teleportToTile->offset);
                }

                for(auto& ghost: ghosts){
                    if (teleportTileAABB.Intersects(ghost.GetBoundingBox())) {

                        ghost.MoveTo(teleportToTile->position + teleportToTile->offset);
                    }
                }
            }
        }
    }

    for (auto& pellet : pPellets){

        if (!pellet.eaten)
        {
            if (pacman.GetEatingBoundingBox().Intersects(pellet.pBBox))
            {
                pellet.eaten = true;
                pacman.AteItem(pellet.score);

                if (pellet.powerPellet)
                {
                    pacman.ResetGhostEatenMultiplier();
                }
            }
        }
    }

    if (ShouldSpawnBonusItem())
    {
        SpawnBonusItem();
    }
    
    if (pBonusItem.spawned && !pBonusItem.eaten)
    {
        if (pacman.GetEatingBoundingBox().Intersects(pBonusItem.bbox))
        {
            pBonusItem.eaten = true;
            pacman.AteItem(pBonusItem.score);
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

    if (pBonusItem.spawned && !pBonusItem.eaten)
    {
        screen.Draw(*pnoptrSpriteSheet, pBonusItemSpriteName, pBonusItem.bbox.GetTopLeftPoint());
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

    for(const auto& gate: pGate){

        if (gate.HasCollided(bBox, edge))
        {
            return true;
        }
    }
    
    return false;
}

bool PacmanLevel::WillCollide(const PacmanGhost &ghost, const PacmanGhostAI &ghostAI, PacmanMovement direction) const
{
    Rectangle bbox = ghost.GetBoundingBox();

    bbox.MoveBy(GetMovementVector(direction));
    BoundaryEdge edge;

    for (const auto& wall : pWalls){

        if (wall.HasCollided(bbox, edge))
        {
            return true;
        }
    }

    for (const auto& gate : pGate){

        if (!(ghostAI.IsEnteringPen() || ghostAI.WantsToLeavePen() && gate.HasCollided(bbox, edge)))
        {
            return true;
        }
    }

    return false;
}

bool PacmanLevel::IsLevelOver() const{

    return HasEatenAllPellets();
}

void PacmanLevel::IncreaseLevel(){

    pCurrentLevel++;

    if (pCurrentLevel > NUM_LEVELS)
    {
        pCurrentLevel = 1;
    }
    ResetLevel();
}

void PacmanLevel::ResetToFirstLevel(){

    pCurrentLevel = 1;
    ResetLevel();
}

bool PacmanLevel::ShouldSpawnBonusItem() const{

    auto numEaten = NumPelletsEaten();
    return !pBonusItem.spawned && numEaten >= pBonusItem.spawnTime;
}

void PacmanLevel::SpawnBonusItem(){
 
    pBonusItem.spawned = 1;
    pBonusItem.eaten = 0;
}

void PacmanLevel::GetBonusItemSpriteName(std::string& spriteName, uint32_t& score) const{

    for(const auto& properties : pBonusItemProperties){

        if (pCurrentLevel >= properties.begin && pCurrentLevel <= properties.end)
        {
            spriteName = properties.spriteName;
            score = properties.score;
        }
    }
}

void PacmanLevel::ResetLevel()
{
    ResetPellets();

    std::uniform_int_distribution <size_t> distribution (20, pPellets.size() -50);
    pBonusItem.spawnTime = static_cast<int>(distribution(pGenerator));

    GetBonusItemSpriteName(pBonusItemSpriteName, pBonusItem.score);

}

bool PacmanLevel::HasEatenAllPellets() const
{
    return NumPelletsEaten() >= pPellets.size() -4 ;
}

size_t PacmanLevel::NumPelletsEaten() const
{
    size_t numEaten = 0;
    for ( const auto& pellet : pPellets){

        if (!pellet.powerPellet && pellet.eaten)
        {
            ++numEaten;
        }
    }
    return numEaten;
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
	tileIsTeleportTileCommand.parseFunc = [this](ParseFuncParams params)
		{
			pTiles.back().isTeleportTile = FileCommandLoader::ReadInt(params);
		};

	fileLoader.AddCommand(tileIsTeleportTileCommand);

	Command tileToTeleportToCommand;
	tileToTeleportToCommand.command = "tile_teleport_to_symbol";
	tileToTeleportToCommand.parseFunc = [this](ParseFuncParams params)
		{
			pTiles.back().teleportToSymbol = FileCommandLoader::ReadChar(params);
		};

	fileLoader.AddCommand(tileToTeleportToCommand);

	Command tileOffsetCommand;
	tileOffsetCommand.command = "tile_offset";
	tileOffsetCommand.parseFunc = [this](ParseFuncParams params)
		{
			pTiles.back().offset = FileCommandLoader::ReadSize(params);
		};

	fileLoader.AddCommand(tileOffsetCommand);

	Command tileExcludePelletCommand;
	tileExcludePelletCommand.command = "tile_exclude_pellet";
	tileExcludePelletCommand.parseFunc = [this](ParseFuncParams params)
		{
			pTiles.back().excludePelletTile = FileCommandLoader::ReadInt(params);
		};

	fileLoader.AddCommand(tileExcludePelletCommand);

	Command tilePacmanSpawnPointCommand;
	tilePacmanSpawnPointCommand.command = "tile_pacman_spawn_point";
	tilePacmanSpawnPointCommand.parseFunc = [this](ParseFuncParams params)
		{
			pTiles.back().pacmanSpawnPoint = FileCommandLoader::ReadInt(params);
		};

	fileLoader.AddCommand(tilePacmanSpawnPointCommand);

	Command tileItemSpawnPointCommand;
	tileItemSpawnPointCommand.command = "tile_item_spawn_point";
	tileItemSpawnPointCommand.parseFunc = [this](ParseFuncParams params)
		{
			pTiles.back().itemSpawnPoint = FileCommandLoader::ReadInt(params);
		};

	fileLoader.AddCommand(tileItemSpawnPointCommand);

	Command tileBlinkySpawnPointCommand;
	tileBlinkySpawnPointCommand.command = "tile_blinky_spawn_point";
	tileBlinkySpawnPointCommand.parseFunc = [this](ParseFuncParams params)
		{
			pTiles.back().blinkySpawnPoint = FileCommandLoader::ReadInt(params);
		};

	fileLoader.AddCommand(tileBlinkySpawnPointCommand);

	Command tilePinkySpawnPointCommand;
	tilePinkySpawnPointCommand.command = "tile_pinky_spawn_point";
	tilePinkySpawnPointCommand.parseFunc = [this](ParseFuncParams params)
		{
			pTiles.back().pinkySpawnPoint = FileCommandLoader::ReadInt(params);
		};

	fileLoader.AddCommand(tilePinkySpawnPointCommand);

	Command tileInkySpawnPointCommand;
	tileInkySpawnPointCommand.command = "tile_inky_spawn_point";
	tileInkySpawnPointCommand.parseFunc = [this](ParseFuncParams params)
		{
			pTiles.back().inkySpawnPoint = FileCommandLoader::ReadInt(params);
		};

	fileLoader.AddCommand(tileInkySpawnPointCommand);

	Command tileClydeSpawnPointCommand;
	tileClydeSpawnPointCommand.command = "tile_clyde_spawn_point";
	tileClydeSpawnPointCommand.parseFunc = [this](ParseFuncParams params)
		{
			pTiles.back().clydeSpawnPoint = FileCommandLoader::ReadInt(params);
		};

	fileLoader.AddCommand(tileClydeSpawnPointCommand);

    Command tileGateCommand;
	tileGateCommand.command = "tile_is_gate";
	tileGateCommand.parseFunc = [this](ParseFuncParams params)
		{
			pTiles.back().isGate = FileCommandLoader::ReadInt(params);
		};

	fileLoader.AddCommand(tileGateCommand);

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

                if (tile -> isGate > 0)
                {
                    Excluder gate;
                    gate.Init(Rectangle(Vector2D(startingX, layoutOffset.GetY()), tile->width, static_cast<int>(pTileHeight)));
                    pGate.push_back(gate);
                }
                else if (tile-> collidable >0)
                {
                    Excluder wall;
                    wall.Init(Rectangle(Vector2D(startingX, layoutOffset.GetY()), tile->width, static_cast<int>(pTileHeight)));
                    pWalls.push_back(wall);
                }

                if (tile-> pacmanSpawnPoint >0)
                {
                    pPacmanSpawnLocation = Vector2D(startingX + tile->offset.GetX(), layoutOffset.GetY() + tile->offset.GetY());
                }
                else if (tile -> blinkySpawnPoint > 0)
                {
                    pGhostSpawnPoints[BLINKY] = Vector2D(startingX + tile-> offset.GetX(), layoutOffset.GetY() + tile -> offset.GetY());
                } 
                else if (tile -> pinkySpawnPoint > 0)
                {
                    pGhostSpawnPoints[PINKY] = Vector2D(startingX + tile-> offset.GetX(), layoutOffset.GetY() + tile -> offset.GetY());
                } 
                else if (tile -> inkySpawnPoint > 0)
                {
                    pGhostSpawnPoints[INKY] = Vector2D(startingX + tile-> offset.GetX(), layoutOffset.GetY() + tile -> offset.GetY());
                } 
                else if (tile -> clydeSpawnPoint > 0)
                {
                    pGhostSpawnPoints[CLYDE] = Vector2D(startingX + tile-> offset.GetX(), layoutOffset.GetY() + tile -> offset.GetY());
                } 
                else if (tile -> itemSpawnPoint > 0)
                {
                    pBonusItem.bbox = Rectangle(Vector2D(startingX + tile -> offset.GetX(), layoutOffset.GetY() + tile->offset.GetY()), SPRITE_WIDTH, SPRITE_HEIGHT);
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

	Command bonusItemCommand;
	bonusItemCommand.command = "bonus_item";
	bonusItemCommand.parseFunc = [this](ParseFuncParams params)
		{
			BonusItemLevelProperties newProperty;
			pBonusItemProperties.push_back(newProperty);
		};

	fileLoader.AddCommand(bonusItemCommand);

	Command bonusItemSpriteNameCommand;
	bonusItemSpriteNameCommand.command = "bonus_item_sprite_name";
	bonusItemSpriteNameCommand.parseFunc = [this](ParseFuncParams params)
		{
			pBonusItemProperties.back().spriteName = FileCommandLoader::ReadString(params);
		};

	fileLoader.AddCommand(bonusItemSpriteNameCommand);


	Command bonusItemScoreCommand;
	bonusItemScoreCommand.command = "bonus_item_score";
	bonusItemScoreCommand.parseFunc = [this](ParseFuncParams params)
		{
			pBonusItemProperties.back().score = FileCommandLoader::ReadInt(params);
		};

	fileLoader.AddCommand(bonusItemScoreCommand);

	Command bonusItemBeginLevelCommand;
	bonusItemBeginLevelCommand.command = "bonus_item_begin_level";
	bonusItemBeginLevelCommand.parseFunc = [this](ParseFuncParams params)
		{
			pBonusItemProperties.back().begin = FileCommandLoader::ReadInt(params);
		};

	fileLoader.AddCommand(bonusItemBeginLevelCommand);


	Command bonusItemEndLevelCommand;
	bonusItemEndLevelCommand.command = "bonus_item_end_level";
	bonusItemEndLevelCommand.parseFunc = [this](ParseFuncParams params)
		{
			pBonusItemProperties.back().end = FileCommandLoader::ReadInt(params);
		};

	fileLoader.AddCommand(bonusItemEndLevelCommand);

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


