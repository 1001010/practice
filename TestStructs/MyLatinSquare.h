#pragma once

#include <vector>
#include <assert.h>

void MyLatinSquare_UnitTest();

enum SudokuGroupTypeEnum {
	SudokuGroupRow,
	SudokuGroupCol,
	SudokuGroupGrid,
	SudokuGroupType_Count,
};

#define WANT_SUDOKU_BOARD_ROTATION  0

template <size_t TGridSize>
class SudokuGameT
{
	/*
	Common Sudoku is a standard LatinSquare 9x9 grid of numbers 1-9 with nine grid regions.
	Basic rules
		A single number can only occur ONCE in 3 groups
			"row"   : a horizontal group of 9 numbers with no duplicates
			"column": a vertical group of 9 numbers with no duplicates
			"grid"  : a 3x3 square of 9 numbers with no duplicates, there are 9 regions in a tic-tac-toe layout
		Values:
			0    == field is empty
			1..9 == entered number
			-1   == error
	Implementation:
		Avoiding the hyper-optimized implementations & striving for readable code
	*/

public:
	enum {
		GRID_SIZE = TGridSize,
		CELLS = GRID_SIZE * GRID_SIZE,
		FIELD_EMPTY = 0,
		FIELD_ERROR = -1,
	};
	static_assert(CELLS > 0, "empty sudoku is not supported by this class");
	static_assert(GRID_SIZE >= 2, "tiny sudoku is not supported by this class");

protected:
	int m_board_x_y[CELLS][CELLS];

public:
	SudokuGameT();

	int GetValue(SudokuGroupTypeEnum groupType, int groupIndex, int offset) const;
	int GetValue(int x, int y) const;
	bool SetValue(int x, int y, int value);

	bool IsSolved(SudokuGroupTypeEnum groupType, int groupIndex) const;
	bool IsSolved() const;

	size_t FindPossibleAnswersFor(int x, int y, std::vector<int> &answers) const;

	void LoadTable(int(&table)[CELLS][CELLS]);

	bool Generate(int seed);

	void TransformBoardFlipX();
	void TransformBoardFlipY();

#if WANT_SUDOKU_BOARD_ROTATION
	void TransformBoardRotate90();
	void TransformBoardRotate180();
	void TransformBoardRotate270();
#endif

	void Clear();
};

//typedef SudokuGameT<0>  SudokuGame0;          // INVALID - WILL NOT WORK, here for testing static_assert
//typedef SudokuGameT<1>  SudokuGame2;          // INVALID - WILL NOT WORK, here for testing static_assert
typedef SudokuGameT<2>  SudokuGame4;            // Easy mode for users, and devs that want to debug the routines
typedef SudokuGameT<3>  SudokuGame9;            // What most players "expect" sudoku to be
typedef SudokuGameT<4>  SudokuGame16;
typedef SudokuGameT<5>  SudokuGame25;
typedef SudokuGameT<6>  SudokuGame36;
typedef SudokuGameT<7>  SudokuGame49;
typedef SudokuGameT<8>  SudokuGame64;
typedef SudokuGameT<9>  SudokuGame81;
typedef SudokuGameT<10> SudokuGame100;


