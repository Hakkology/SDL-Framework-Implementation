#include "pacmanlevel.h"
#include "filecommandloader.h"
#include "screen.h"

bool PacmanLevel::Init(const std::string &levelPath){

    return LoadLevel(levelPath);
}

void PacmanLevel::Update(uint32_t dt){

}

void PacmanLevel::Draw(Screen &screen){

    // Debug for walls
    for(const auto& wall: pWalls){

        screen.Draw(wall.GetRectangle(), Blue()); 
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

    Command layoutCommand;
    layoutCommand.command = "layout";
    layoutCommand.commandType = COMMAND_MULTI_LINE;
    layoutCommand.parseFunc = [&layoutOffset, this](ParseFuncParams params){

        // startingX updated to move the map to middle.
        int startingX = layoutOffset.GetX() + SCREEN_WIDTH/4;

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
