#ifndef GAMES_TETRIS_TETRISGAMEGRID__H__
#define GAMES_TETRIS_TETRISGAMEGRID__H__

#include "rectangle.h"
#include "color.h"

class Screen;
class Vector2D;

enum TetrominoType
{
	I_TYPE = 0,
	J_TYPE,
	L_TYPE,
	O_TYPE,
	S_TYPE,
	T_TYPE,
	Z_TYPE
};

enum class XBlockDirection
{
	LEFT = 0,
	RIGHT,
	STOP,
};

enum class YBlockDirection
{
	DOWN = 0,
	STOP
};

class TetrisBlock
{

public:

	TetrisBlock();
	TetrisBlock(const TetrisBlock& other);
	~TetrisBlock();

	void Init(TetrominoType type, const Rectangle& boundary, const Vector2D& startPosition);

	void MoveBy(const Vector2D& vector);
	void Rotate(int rotation);
	void Draw(Screen& theScreen);
	void Update(uint32_t dt);

	inline void SetXMovementDirection(XBlockDirection dir) { m_XDirection = dir; }
	inline void SetYMovementDirection(YBlockDirection dir) { m_YDirection = dir; }
	inline void SetPieceRotation(const uint8_t rotation) { m_Rotation = rotation; }
	
	std::vector<Rectangle> GetSignificantBlocks() const;

	int FindRotatedIndex(int index, int r);

	// Functions to see where the piece will move next
	Vector2D GetPositionChange() const;
	int GetRotationChange() const;

	// All blocks in the tetris game have a width and a height of 8 pixels
	static const uint32_t BLOCK_HEIGHT = 12;
	static const uint32_t BLOCK_WIDTH = 12;

	inline const bool IsBlockMoving() const{ return m_IsMoving; }
	inline std::vector<Rectangle> GetPieceBlocks() const{ return m_BlockData; }
	inline std::vector<unsigned int> GetSignificantIndices() const { return m_SignificantIndices; }
	inline const TetrominoType GetPieceType() const { return m_Type; }

private:
    // Each tetromino fits within a 4x4 array of squares
	std::vector<Rectangle> m_BlockData;
	TetrominoType m_Type;
	Color m_Colour;
	bool m_IsMoving;
	
	Rectangle m_Boundary;

	// All shapes will have 4 cubes getting drawn at once
	std::vector<unsigned int> m_SignificantIndices;

	// Possible directions of movement of the tetromino piece
	XBlockDirection m_XDirection;
	YBlockDirection m_YDirection;
	uint8_t m_Rotation;
	
	// Helper methods
	void SetInitialIndices();
};




#endif  //!GAMES_TETRIS_TETRISGAMEGRID__H__