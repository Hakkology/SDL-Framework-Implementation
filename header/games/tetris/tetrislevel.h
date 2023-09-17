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
	//static const Colour colours[7];

	TetrisLevel();
	~TetrisLevel() {};

	void Init(const Vector2D& startPosition);
	void Update(uint32_t dt, uint32_t& score);
	void Draw(Screen& theScreen, int level, uint32_t score);

	void AddPiece(const TetrisBlock& newPiece);
	bool DoesPieceFit(TetrisBlock pieceToFit, const Vector2D& vector, int rotation);

	inline const Rectangle GetLevelBoundary() const { return m_LevelBoundary; }
	inline const int GetCompletedLines() const { return m_Lines; }

private:

	uint32_t GetLevelIndex(float x, float y);
	uint32_t m_PlayingField[LEVEL_WIDTH * LEVEL_HEIGHT];

	Rectangle m_LevelBoundary;

	uint32_t m_Lines;

	BmpFont m_Font;
};

#endif  //!_GAMES_TETRIS_TETRISLEVEL__H__