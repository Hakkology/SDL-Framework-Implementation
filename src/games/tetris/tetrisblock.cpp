#include <cassert>
#include <iostream>

#include "tetrisblock.h"
#include "screen.h"
#include "color.h"
#include "vector2D.h"


TetrisBlock::TetrisBlock() : m_SignificantIndices(4, 0)
{
	m_Colour = Black();
	m_Type = TetrominoType::I_TYPE;
	m_XDirection = XBlockDirection::STOP;
	m_YDirection = YBlockDirection::STOP;
	m_IsMoving = true;
	m_Rotation = 0;

	// Fill mBlockData with empty rectangle
	Rectangle emptyRectangle = { Vector2D::Zero, Vector2D::Zero };
	for (size_t i = 0; i < 16; i++)
	{
		m_BlockData.push_back(emptyRectangle);
	}

};

TetrisBlock::TetrisBlock(const TetrisBlock& other)
{
	m_Colour = other.m_Colour;
	m_Type = other.m_Type;
	m_XDirection = other.m_XDirection;
	m_YDirection = other.m_YDirection;
	m_IsMoving = other.m_IsMoving;
	m_Rotation = other.m_Rotation;

	for (size_t i = 0; i < 16; i++)
	{
		m_BlockData.push_back(other.m_BlockData[i]);
	}

	for (size_t i = 0; i < 4; i++)
	{
		m_SignificantIndices.push_back(other.m_SignificantIndices[i]);
	}
}

TetrisBlock::~TetrisBlock() {

}

void TetrisBlock::Init(TetrominoType type, const Rectangle& boundary, const Vector2D& startPosition)
{
	m_Type = type;
	m_Boundary = boundary;

	Vector2D yOffset = Vector2D::Zero;
	Vector2D xOffset = Vector2D::Zero;
	Rectangle block;

	for (size_t i = 0; i < 16; i++)
	{
		// Calculate the offset of each block
		if (i % 4 != 0)
		{
			xOffset += Vector2D(TetrisBlock::BLOCK_WIDTH, 0.0f);
		}
		else if (i != 0)
		{
			xOffset = Vector2D::Zero;
			yOffset += Vector2D(0.0f, TetrisBlock::BLOCK_HEIGHT);
		}

		m_BlockData[i] = { startPosition + xOffset + yOffset, TetrisBlock::BLOCK_WIDTH, TetrisBlock::BLOCK_HEIGHT };
	}

	// Set the indices for the specified bloack type
	SetInitialIndices();
}

void TetrisBlock::MoveBy(const Vector2D& vector)
{
	for (size_t i = 0; i < 16; i++)
	{
		m_BlockData[i].MoveBy(vector);
	}
}

void TetrisBlock::Rotate(int rotation)
{
	// Rotate the significant indices
	for (size_t i = 0; i < 4; i++)
	{
		m_SignificantIndices[i] = FindRotatedIndex(m_SignificantIndices[i], rotation);
	}
}

void TetrisBlock::Draw(Screen& theScreen)
{
	for (size_t i = 0; i < 4; i++)
	{
		unsigned int index = m_SignificantIndices[i];
		theScreen.Draw(m_BlockData[index], White(), true, m_Colour);
	}
}

// We will only run this if the tetromino can move to a possible location
void TetrisBlock::Update(uint32_t dt)
{
	MoveBy(GetPositionChange());
	Rotate(GetRotationChange());

	m_XDirection = XBlockDirection::STOP;
	m_YDirection = YBlockDirection::STOP;
	m_Rotation = 0;
}

void TetrisBlock::SetInitialIndices()
{
	// Set the array with the significant indices.
	switch (m_Type)
	{
	case TetrominoType::I_TYPE:
	{
		m_SignificantIndices = { 8, 9, 10, 11 };
		m_Colour = Cyan();
		break;
	}
	case TetrominoType::J_TYPE:
	{
		m_SignificantIndices = { 5, 6, 7, 11 };
		m_Colour = Blue();
		break;
	}
	case TetrominoType::L_TYPE:
	{
		m_SignificantIndices = { 5, 6, 7, 9 };
		m_Colour = Orange();
		break;
	}
	case TetrominoType::O_TYPE:
	{
		m_SignificantIndices = { 5, 6, 9, 10 };
		m_Colour = Yellow();
		break;
	}
	case TetrominoType::S_TYPE:
	{
		m_SignificantIndices = { 8, 9, 5, 6 };
		m_Colour = Green();
		break;
	}
	case TetrominoType::T_TYPE:
	{
		m_SignificantIndices = { 4, 5, 6, 9 };
		m_Colour = Pink();
		break;
	}
	case TetrominoType::Z_TYPE:
	{
		m_SignificantIndices = { 4, 5, 9, 10 };
		m_Colour = Red();
		break;
	}
	}
}

std::vector<Rectangle> TetrisBlock::GetSignificantBlocks() const
{
	std::vector<Rectangle> significantBlocks;

	int j = 0;

	for (const auto& i : m_SignificantIndices)
	{
		significantBlocks.push_back(m_BlockData[i]);
	}
	
	return significantBlocks;
}

int TetrisBlock::FindRotatedIndex(int index, int r)
{
	// transform the index into the x and y coordinates.
	int y = index / 4;
	int x = index - y * 4;

	switch (r % 4)
	{
	case 0: return y * 4 + x;			// 0 degrees
	case 1: return 12 + y - (x * 4);	// 90 degrees
	case 2: return 15 - (y * 4) - x;	// 180 degrees
	case 3: return 3 - y + (x * 4);		// 270 degrees
	}

	return 0;
}

Vector2D TetrisBlock::GetPositionChange() const
{
	Vector2D dir = Vector2D::Zero;
	if (m_XDirection != XBlockDirection::STOP)
	{
		if (m_XDirection == XBlockDirection::RIGHT)
		{
			dir += Vector2D(1.0f, 0.0f);
		}
		else
		{
			dir += Vector2D(-1.0f, 0.0f);
		}
	}

	if (m_YDirection != YBlockDirection::STOP)
	{
		if (m_YDirection == YBlockDirection::DOWN)
		{
			dir += Vector2D(0.0f, 1.0f);
		}
	}

	Vector2D dPos = dir * (float)BLOCK_HEIGHT;

	return dPos;
}

int TetrisBlock::GetRotationChange() const
{
	return m_Rotation;
}