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

	inline void SetXMovementDirection(XBlockDirection dir) { t_XDirection = dir; }
	inline void SetYMovementDirection(YBlockDirection dir) { t_YDirection = dir; }
	inline void SetPieceRotation(const uint8_t rotation) { t_Rotation = rotation; }
	
	std::vector<Rectangle> GetSignificantBlocks() const;

	int FindRotatedIndex(int index, int r);

	// Functions to see where the piece will move next
	Vector2D GetPositionChange() const;
	int GetRotationChange() const;

	// All blocks in the tetris game have a width and a height of 8 pixels
	static const uint32_t BLOCK_HEIGHT = 12;
	static const uint32_t BLOCK_WIDTH = 12;

	inline const bool IsBlockMoving() const{ return t_IsMoving; }
	inline std::vector<Rectangle> GetPieceBlocks() const{ return t_BlockData; }
	inline std::vector<unsigned int> GetSignificantIndices() const { return t_SignificantIndices; }
	inline const TetrominoType GetPieceType() const { return t_Type; }

private:
    // Each tetromino fits within a 4x4 array of squares
	std::vector<Rectangle> t_BlockData;
	TetrominoType t_Type;
	Color t_Colour;
	bool t_IsMoving;
	
	Rectangle t_Boundary;

	// All shapes will have 4 cubes getting drawn at once
	std::vector<unsigned int> t_SignificantIndices;

	// Possible directions of movement of the tetromino piece
	XBlockDirection t_XDirection;
	YBlockDirection t_YDirection;
	uint8_t t_Rotation;
	
	// Helper methods
	void SetInitialIndices();
};




#endif  //!GAMES_TETRIS_TETRISGAMEGRID__H__