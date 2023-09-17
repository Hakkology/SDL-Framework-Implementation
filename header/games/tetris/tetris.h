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

	TetrisGameState t_GameState;
	TetrisBlock t_Block;
	TetrisBlock t_NextBlock;
	TetrisLevel t_TetrisLevel;
	
	uint32_t t_Score;
	// HighScoreTable m_HighScoreTable;

	int t_BlocksAccumulated;
	
	Rectangle t_LevelBoundary;
	uint32_t t_TimeAccumulated = 0;

	Vector2D t_PieceStartPosition;
	
	int t_CompletedLines;
	int t_Level;
};

#endif  //!_GAMES_TETRIS_TETRIS__H__