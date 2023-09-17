#ifndef _GAMES_TETRIS_TETRIS__H__
#define _GAMES_TETRIS_TETRIS__H__

#include "game.h"
#include "tetrisblock.h"
#include "tetrislevel.h"
//#include "App/HighScoreTable.h"

enum class TetrisGameState
{
	IN_GAME_OVER = 0, 
	IN_SERVE, 
	IN_PLAY
};

class Tetris : public Game
{

public:
	virtual void Init(GameController& controller) override;
	virtual void Update(uint32_t dt) override;
	virtual void Draw(Screen& screen) override;

	void ResetGame();

	virtual const std::string& GetName() const override;

private:

	TetrisGameState m_GameState;
	TetrisBlock m_Block;
	TetrisBlock m_NextBlock;
	TetrisLevel m_TetrisLevel;
	
	uint32_t m_Score;
	// HighScoreTable m_HighScoreTable;

	int m_BlocksAccumulated;
	
	Rectangle m_LevelBoundary;
	uint32_t m_TimeAccumulated = 0;

	Vector2D m_PieceStartPosition;
	
	int m_CompletedLines;
	int m_Level;
};

#endif  //!_GAMES_TETRIS_TETRIS__H__