#include <thread>
#include <chrono>
#include <stdlib.h> 

#include "tetris.h"
#include "tetris.h"
#include "gamecontroller.h"
#include "screen.h"
#include "app.h"


void Tetris::Init(GameController& controller)
{
	controller.ClearAll();
	
	ResetGame();

	ButtonAction moveLeft;
	moveLeft.key = GameController::LeftKey();
	moveLeft.action = [this](uint32_t dt, InputState state)
	{
		if (t_GameState == TetrisGameState::IN_PLAY)
		{
			if (GameController::IsPressed(state))
			{
				t_Block.SetXMovementDirection(XBlockDirection::LEFT);
			}
		}
	};

	controller.AddInputActionForKey(moveLeft);

	ButtonAction moveRight;
	moveRight.key = GameController::RightKey();
	moveRight.action = [this](uint32_t dt, InputState state)
	{
		if (t_GameState == TetrisGameState::IN_PLAY)
		{
			if (GameController::IsPressed(state))
			{
				t_Block.SetXMovementDirection(XBlockDirection::RIGHT);
			}
		}
	};

	controller.AddInputActionForKey(moveRight);

	ButtonAction moveDown;
	moveDown.key = GameController::DownKey();
	moveDown.action = [this](uint32_t dt, InputState state)
	{
		if (t_GameState == TetrisGameState::IN_PLAY)
		{
			if (GameController::IsPressed(state))
			{
				t_Block.SetYMovementDirection(YBlockDirection::DOWN);
			}
		}
	};

	controller.AddInputActionForKey(moveDown);

	// This is temporary - we will modify a rotation intentions field which then in Update we check collision and kicks
	ButtonAction rotateClockwise;
	rotateClockwise.key = GameController::ModifyKey();
	rotateClockwise.action = [this](uint32_t, InputState state)
	{
		if (t_GameState == TetrisGameState::IN_PLAY)
		{
			if (GameController::IsPressed(state))
			{
				t_Block.SetPieceRotation(3);
			}
		}
	};
	
	controller.AddInputActionForKey(rotateClockwise);

	ButtonAction rotateAntiClockwise;
	rotateAntiClockwise.key = GameController::PushKey();
	rotateAntiClockwise.action = [this](uint32_t, InputState state)
	{
		if (t_GameState == TetrisGameState::IN_PLAY)
		{
			if (GameController::IsPressed(state))
			{
				t_Block.SetPieceRotation(1);
			}
		}
	};

	controller.AddInputActionForKey(rotateAntiClockwise);

	ButtonAction serveAction;
	serveAction.key = GameController::ActionKey();
	serveAction.action = [this](uint32_t dt, InputState state)
	{
		if (GameController::IsPressed(state))
		{
			if (t_GameState == TetrisGameState::IN_SERVE)
			{
				t_GameState = TetrisGameState::IN_PLAY;
			}
		}
	};

	controller.AddInputActionForKey(serveAction);

	ButtonAction backAction;
	backAction.key = GameController::CancelKey();
	backAction.action = [this](uint32_t dt, InputState state)
	{
		if (t_GameState == TetrisGameState::IN_SERVE || t_GameState == TetrisGameState::IN_GAME_OVER)
		{
			if (GameController::IsPressed(state))
			{
				// Go back to the previous scene
				App::Singleton().PopScene();
			}
		}
	};

	controller.AddInputActionForKey(backAction);
}

void Tetris::Update(uint32_t dt)
{

	if(t_GameState == TetrisGameState::IN_PLAY)
	{
		t_TimeAccumulated += dt;

		if (t_TetrisLevel.DoesPieceFit(t_Block, t_Block.GetPositionChange(), t_Block.GetRotationChange()))
		{
			t_Block.Update(dt);
		}

		// Check if we have to increase the level
		if ((t_TetrisLevel.GetCompletedLines() % 2 <= t_CompletedLines % 2) && (t_CompletedLines < t_TetrisLevel.GetCompletedLines()))
		{
			t_Level -= 50;
		}

		t_CompletedLines = t_TetrisLevel.GetCompletedLines();

		if (t_TimeAccumulated > t_Level)
		{
			// Move the block down if we can do so
			Vector2D dy = { 0.0f, 1.0f * (float)TetrisBlock::BLOCK_HEIGHT };
			if (t_TetrisLevel.DoesPieceFit(t_Block, dy, 0))
			{
				t_Block.SetXMovementDirection(XBlockDirection::STOP);
				t_Block.MoveBy(dy);
				t_Block.Update(dt);
			}
			else
			{
				// Add piece to the field
				t_TetrisLevel.AddPiece(t_Block);

				// If there are completed lines update the field - clear the line
				t_TetrisLevel.Update(dt, t_Score);

				// m_Block becomes m_nextBlock and starts to move down if it can and add it 
				t_Block.Init(t_NextBlock.GetPieceType(), t_LevelBoundary, t_PieceStartPosition);

				// m_NextBlock gets generated
				Vector2D nextPiecePosition = { t_LevelBoundary.GetBottomRightPoint().GetX() + 35, t_LevelBoundary.GetTopLeftPoint().GetY() };
				t_NextBlock.Init(static_cast<TetrominoType>(rand() % 7), t_LevelBoundary, nextPiecePosition);

				if (!t_TetrisLevel.DoesPieceFit(t_Block, Vector2D(0, 0), 0))
				{
					// Game Over
					t_GameState = TetrisGameState::IN_GAME_OVER;

					// Update the highScore table
					// m_HighScoreTable.UpdateTable(m_Score);
					// m_HighScoreTable.SaveToFile();

					// // Make the highScoreScene Before resetting the game
					// std::unique_ptr<HighScoreScene> highScoreScene = std::make_unique<HighScoreScene>(m_HighScoreTable);

					// // Push the game over highscore scene
					// App::Singleton().PushScene(std::move(highScoreScene));
				}
			}

			t_TimeAccumulated = 0;
		}
	}

	if (t_GameState == TetrisGameState::IN_GAME_OVER)
	{
		// Reset the Game
		ResetGame();
	}
}

void Tetris::Draw(Screen& screen)
{  
	t_Block.Draw(screen);
	t_NextBlock.Draw(screen);
	
	// Draw the level
	t_TetrisLevel.Draw(screen, t_Level, t_Score);
}


void Tetris::ResetGame()
{
	t_TetrisLevel.Init(Vector2D(TetrisBlock::BLOCK_WIDTH, TetrisBlock::BLOCK_HEIGHT));

	t_CompletedLines = 0;
	
	t_LevelBoundary = t_TetrisLevel.GetLevelBoundary();

	t_PieceStartPosition = { t_LevelBoundary.GetTopLeftPoint().GetX() + TetrisBlock::BLOCK_WIDTH * 3, t_LevelBoundary.GetTopLeftPoint().GetY() };

	Vector2D nextPiecePosition = { t_LevelBoundary.GetBottomRightPoint().GetX() + 20, t_LevelBoundary.GetTopLeftPoint().GetY()};
	
	t_Block.Init(static_cast<TetrominoType>(rand() % 7), t_LevelBoundary, t_PieceStartPosition);
	t_NextBlock.Init(static_cast<TetrominoType>(rand() % 7), t_LevelBoundary, nextPiecePosition);

	// m_HighScoreTable.Init("Tetris");
	// m_Score.PlayerName = "ABC";
	t_Score = 0;

	t_GameState = TetrisGameState::IN_SERVE;
	
	t_Level = 500;
	t_CompletedLines = 0;
}

const std::string& Tetris::GetName() const
{
	static std::string name = "Tetrus";
	return name;
}