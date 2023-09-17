#ifndef _GAMES_TETRIS_TETRISLEVEL__H__
#define _GAMES_TETRIS_TETRISLEVEL__H__

#include "tetrisblock.h"
#include "rectangle.h"
#include "bmpfont.h"

class Screen;

// Contains the boundary, playing field and all of the pieces that have fallen and stopped

class TetrisLevel
{

public:
	static const uint8_t LEVEL_WIDTH = 10;
	static const uint8_t LEVEL_HEIGHT = 20;

	TetrisLevel();
	~TetrisLevel() {};

	void Init(const Vector2D& startPosition);
	void Update(uint32_t dt, uint32_t& score);
	void Draw(Screen& theScreen, int level, uint32_t score);

	void AddPiece(const TetrisBlock& newPiece);
	bool DoesPieceFit(TetrisBlock pieceToFit, const Vector2D& vector, int rotation);

	inline const Rectangle GetLevelBoundary() const { return t_LevelBoundary; }
	inline const int GetCompletedLines() const { return t_Lines; }

private:

	uint32_t GetLevelIndex(float x, float y);
	uint32_t t_PlayingField[LEVEL_WIDTH * LEVEL_HEIGHT];

	Rectangle t_LevelBoundary;

	uint32_t t_Lines;

	BmpFont t_Font;
};

#endif  //!_GAMES_TETRIS_TETRISLEVEL__H__