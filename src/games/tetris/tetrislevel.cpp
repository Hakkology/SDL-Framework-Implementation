#include <math.h> 

#include "tetrislevel.h"
#include "color.h"
#include "screen.h"
#include "vector2D.h"
#include "app.h"

//Check app changes

TetrisLevel::TetrisLevel(): t_PlayingField{ 0 }
{

}

// Here wee add an integer parameter to pass by referemce the score which we can then save to m_Score
void TetrisLevel::Init(const Vector2D& startPosition)
{
	t_LevelBoundary = { startPosition, LEVEL_WIDTH * TetrisBlock::BLOCK_WIDTH, LEVEL_HEIGHT * TetrisBlock::BLOCK_HEIGHT};
	for (size_t i = 0; i < LEVEL_HEIGHT * LEVEL_WIDTH; i++)
	{
		// Clear the boundary
		t_PlayingField[i] = 0;
	}
	t_Lines = 0;
	t_Font = App::Singleton().GetFont();

}

void TetrisLevel::Update(uint32_t dt, uint32_t& score)
{
	/*
	1. Loop through the array, if there is a given row where all values are not 0, set them all to 0
	2. Move the aray down by changing the index
	*/
	std::vector<int> lines;
	bool bLine;
	for (size_t y = 0; y < LEVEL_HEIGHT; y++)
	{
		bLine = true;
		for (size_t x = 0; x < LEVEL_WIDTH; x++)
		{
			bLine &= (t_PlayingField[y * LEVEL_WIDTH + x]) != 0;
		}

		// If the line is full set the values to zero again
		if (bLine)
		{
			for (size_t i = 0; i < LEVEL_WIDTH; i++)
			{
				t_PlayingField[y * LEVEL_WIDTH + i] = 0;
			}
			lines.push_back(y);
		}
	}

	if (!lines.empty())
	{
		for (const auto& v : lines) 
		{
			for (int x = 0; x < LEVEL_WIDTH; x++)
			{
				// Move the entire grid down 
				for (size_t y = v; y > 0; y--)
				{
					t_PlayingField[y * LEVEL_WIDTH + x] = t_PlayingField[(y - 1) * LEVEL_WIDTH + x];
				}
				// Fill the top row
				t_PlayingField[x] = 0;
			}
		}

		// Add to the score
		t_Lines += lines.size();
		score += (int)round(93.3333 * pow(lines.size(), 3) - 490 * pow(lines.size(), 2) + 876.6667 * lines.size() - 440);
	}
}

void TetrisLevel::Draw(Screen& theScreen, int level, uint32_t score)
{
	// Draw the playing field 
	Color colours[7] = { Cyan(), Blue(), Orange(), Yellow(), Green(), Pink(), Red() };

	for (size_t i = 0; i < 200; i++)
	{
		if (t_PlayingField[i] != 0)
		{
			// transform the index into the x and y coordinates.
			uint32_t y = i / LEVEL_WIDTH;
			uint32_t x = i - y * LEVEL_WIDTH;

			Vector2D position = { static_cast<float>(x * TetrisBlock::BLOCK_WIDTH + t_LevelBoundary.GetTopLeftPoint().GetX()), static_cast<float>(y * TetrisBlock::BLOCK_HEIGHT + t_LevelBoundary.GetTopLeftPoint().GetY())  };
			Rectangle rect = {  position, TetrisBlock::BLOCK_WIDTH, TetrisBlock::BLOCK_HEIGHT };
			theScreen.Draw(rect, colours[t_PlayingField[i] - 1], true, colours[t_PlayingField[i] - 1]);
		}
	}

	// Draw the boundaries
	Rectangle newPieceEnclosure, scoreEnclosure;
	theScreen.Draw(t_LevelBoundary, White(), false);

	newPieceEnclosure = { Vector2D(t_LevelBoundary.GetBottomRightPoint().GetX() + 10, t_LevelBoundary.GetTopLeftPoint().GetY()), 6 * TetrisBlock::BLOCK_WIDTH, 4 * TetrisBlock::BLOCK_HEIGHT };
	theScreen.Draw(newPieceEnclosure, White(), false);
	
	float start = newPieceEnclosure.GetBottomRightPoint().GetY() + 5;

	// Transform the level to the real score
	level = (500 - level) / 50 + 1;

	// Write the score and the number of lines completed
	std::string textToPrint[3] = { "Level: " + std::to_string(level), "Lines: " + std::to_string(t_Lines), "Px: " + std::to_string(score) };
	

	// Draw the Rectangle for the next piece, score, level and lines completed
	for (size_t i = 0; i < 3; i++)
	{
		scoreEnclosure = { Vector2D(newPieceEnclosure.GetTopLeftPoint().GetX(), start), 6 * TetrisBlock::BLOCK_WIDTH, 2 * TetrisBlock::BLOCK_HEIGHT };
		theScreen.Draw(scoreEnclosure, White(), false);

		Vector2D textDrawPosition = t_Font.GetDrawPosition(textToPrint[i], scoreEnclosure, BmpFontXAlignment::BFXA_CENTER, BmpFontYAlignment::BFYA_CENTER);

		theScreen.Draw(t_Font, textToPrint[i], textDrawPosition, White());

		start = scoreEnclosure.GetBottomRightPoint().GetY();
	}
}

void TetrisLevel::AddPiece(const TetrisBlock& newPiece)
{
	// Get the piece location
	std::vector<Rectangle> signficantBlocks = newPiece.GetSignificantBlocks();
	float xCoord, yCoord;

	for (size_t i = 0; i < 4; i++)
	{
		int index = GetLevelIndex(signficantBlocks[i].GetTopLeftPoint().GetX(), signficantBlocks[i].GetTopLeftPoint().GetY());

		t_PlayingField[index] = static_cast<int>(newPiece.GetPieceType()) + 1;
	}
}

bool TetrisLevel::DoesPieceFit(TetrisBlock pieceToFit, const Vector2D& vector, int rotation)
{
	// We move the piece the modified location
	pieceToFit.Rotate(rotation);
	pieceToFit.MoveBy(vector);

	std::vector<uint32_t> significantIndices = pieceToFit.GetSignificantIndices();
	std::vector<Rectangle> pieceBlocks = pieceToFit.GetPieceBlocks();

	float xMinLoc, xMaxLoc, yMinLoc, yMaxLoc;

	for (const auto& i : significantIndices)
	{
		// Check if block is within the bounds of the field
		xMinLoc = pieceBlocks[i].GetTopLeftPoint().GetX();
		xMaxLoc = pieceBlocks[i].GetBottomRightPoint().GetX();
		yMinLoc = pieceBlocks[i].GetTopLeftPoint().GetY();
		yMaxLoc = pieceBlocks[i].GetBottomRightPoint().GetY();

		uint32_t levelIndex = GetLevelIndex(xMinLoc, yMinLoc);
		
		if (xMinLoc >= t_LevelBoundary.GetTopLeftPoint().GetX() && xMaxLoc <= t_LevelBoundary.GetBottomRightPoint().GetX())
		{
			if (yMinLoc >= t_LevelBoundary.GetTopLeftPoint().GetY() && yMaxLoc <= t_LevelBoundary.GetBottomRightPoint().GetY())
			{
				if (t_PlayingField[levelIndex] != 0) {
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	return true;
}

uint32_t TetrisLevel::GetLevelIndex(float x, float y)
{
	uint32_t xCoord = static_cast<uint32_t>(x - t_LevelBoundary.GetTopLeftPoint().GetX()) / TetrisBlock::BLOCK_WIDTH;
	uint32_t yCoord = static_cast<uint32_t>(y - t_LevelBoundary.GetTopLeftPoint().GetY()) / TetrisBlock::BLOCK_HEIGHT;

	int index = yCoord * LEVEL_WIDTH + xCoord;
	return index;
}