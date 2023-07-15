#ifndef FILECOMMANDLOADER_H
#define FILECOMMANDLOADER_H

#include <functional>
#include <vector>
#include <stdint.h>
#include <string>
#include <fstream>
#include <iostream>

#include "color.h"
#include "vector2D.h"


class Color;
class Vector2D;

enum CommandType{

    COMMAND_ONE_LINE = 0,
    COMMAND_MULTI_LINE
};

struct ParseFuncParams{

    std::string line;
    size_t dilimitPos;
    uint32_t lineNum;
};

using ParseFunction = std::function<void(const ParseFuncParams& params)>;

struct Command{

    CommandType commandType = COMMAND_ONE_LINE;
    std::string command = "";
    ParseFunction parseFunc = nullptr;
};

class FileCommandLoader{

public: 

    void AddCommand(const Command& command);
    bool LoadFile(const std::string& filePath);

    static Color ReadColor(const ParseFuncParams& params);
    static Vector2D ReadSize(const ParseFuncParams& params);
    static int ReadInt(const ParseFuncParams& params);
    static std::string ReadString(const ParseFuncParams& params);
    static char ReadChar(const ParseFuncParams& params);

private:
    std::vector<Command> gCommands;

};

#endif