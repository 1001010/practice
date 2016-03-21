#include "stdafx.h"

#include "MyLatinSquare.h"
#include <set>
#include <random>


template <size_t TGridSize>
SudokuGameT<TGridSize>::SudokuGameT()
{
	Clear();
}


template <size_t TGridSize>
void SudokuGameT<TGridSize>::Clear()
{
	memset(&m_board_x_y, FIELD_EMPTY, sizeof(m_board_x_y));
}


// Allows me to support multiple group types through 1 interface
template <size_t TGridSize>
int SudokuGameT<TGridSize>::GetValue(SudokuGroupTypeEnum groupType, int groupIndex, int offset) const
{
	if (groupType >= SudokuGroupType_Count || groupIndex < 0 || groupIndex >= CELLS || offset < 0 || offset >= CELLS)
	{
		assert(!"Bad param");
		return FIELD_ERROR;
	}

	switch (groupType)
	{
	case SudokuGroupRow:
		return m_board_x_y[groupIndex][offset];

	case SudokuGroupCol:
		return m_board_x_y[offset][groupIndex];

	case SudokuGroupGrid:
	{
		// Find the top-left of the grid and use it as an offset
		int grid_x = (groupIndex / GRID_SIZE) * GRID_SIZE;
		int grid_y = (groupIndex % GRID_SIZE) * GRID_SIZE;
		int cell_x = (offset / GRID_SIZE) + grid_x;
		int cell_y = (offset % GRID_SIZE) + grid_y;
		assert(cell_x >= 0 && cell_x <= CELLS);
		assert(cell_y >= 0 && cell_y <= CELLS);
		return m_board_x_y[cell_x][cell_y];
	}
	break;

	default:
		assert(!"Bad SudokuGroupTypeEnum");
	}
	return FIELD_ERROR;
}


template <size_t TGridSize>
int SudokuGameT<TGridSize>::GetValue(int x, int y) const 
{ 
	return GetValue(SudokuGroupRow, x, y); 
}


template <size_t TGridSize>
bool SudokuGameT<TGridSize>::SetValue(int x, int y, int value)
{
	if (x < 0 || x >= CELLS || y < 0 || y >= CELLS || value < 0 || value > CELLS)
	{
		assert(!"bad params");
		return false;
	}

	m_board_x_y[x][y] = value;
	return true;
}


template <size_t TGridSize>
bool SudokuGameT<TGridSize>::IsSolved(SudokuGroupTypeEnum groupType, int groupIndex) const
{
	// Check all the cells in the group
	// for non-zero, valid, non-repeating numbers

	int counter[CELLS] = { 0 };
	int value = 0;

	for (int i = 0; i < CELLS; i++)
	{
		value = GetValue(groupType, groupIndex, i);
		if (value <= FIELD_EMPTY || value >= CELLS)
		{
			// Not a valid number
			return false;
		}

		// track how often we've seen this number
		counter[value]++;

		// Dupe check
		if (counter[value] > 1)
		{
			return false;
		}
	}

	return true;
}


template <size_t TGridSize>
bool SudokuGameT<TGridSize>::IsSolved() const
{
	for (int i = 0; i < CELLS; i++)
	{
		if (!IsSolved(SudokuGroupRow, i) || !IsSolved(SudokuGroupCol, i) || !IsSolved(SudokuGroupGrid, i))
		{
			return false;
		}
	}
	return true;
}


/*
	Fills a vector of possible answers for a given location
	Important: answers are always sorted ascending
*/
template <size_t TGridSize>
size_t SudokuGameT<TGridSize>::FindPossibleAnswersFor(int x, int y, std::vector<int> &answers) const
{
	answers.reserve(CELLS);
	answers.resize(0);

	if (x < 0 || x >= CELLS || y < 0 || y >= CELLS)
	{
		assert(!"bad location");
		return 0;
	}

	// It already has an answer
#if 0
	if (m_board_x_y[x][y])
	{
		answers.push_back(m_board_x_y[x][y]);
		return answers.size();
	}
#endif

	int row = x;
	int col = y;
	int grid = ((x / GRID_SIZE) * GRID_SIZE) + ((y / GRID_SIZE));
	int value = 0;

	// Get all the numbers that we can't use from the current row, column, and grid
	std::set<int> blocking;
	for (int position = 0; position < CELLS; position++)
	{
		value = GetValue(SudokuGroupRow, row, position);
		blocking.insert(value);

		value = GetValue(SudokuGroupCol, col, position);
		blocking.insert(value);

		value = GetValue(SudokuGroupGrid, grid, position);
		blocking.insert(value);
	}

	// whatever is left over is a possible answer
	// IMPORTANT: answers MUST be sorted so that seeded game generation is DETERMINISTIC!
	for (value = 0; value < CELLS + 1; value++)
	{
		if (blocking.find(value) == blocking.end())
		{
			answers.push_back(value);
		}
	}
	assert(answers.size() <= CELLS);

	return answers.size();
}


// Mostly for testing
template <size_t TGridSize>
void SudokuGameT<TGridSize>::LoadTable(int(&table)[CELLS][CELLS])
{
	for (int x = 0; x < CELLS; x++)
	{
		for (int y = 0; y < CELLS; y++)
		{
			m_board_x_y[x][y] = table[x][y];
		}
	}
}


template <size_t TGridSize>
void SudokuGameT<TGridSize>::TransformBoardFlipX()
{
	// horizontal, along the x axis (left and right)
	// 1243 -> 3421                      a234 -> 432a
	// 4321 -> 1234                      1b34 -> 43b1
	// 3412 -> 2143                      12c4 -> 4c21
	// 2134 -> 4312                      123d -> d321
	for (int x = 0; x < CELLS; x++)
	{
		int *start = m_board_x_y[x];
		int *end = start + CELLS;
		std::reverse(start, end);
	}
}


template <size_t TGridSize>
void SudokuGameT<TGridSize>::TransformBoardFlipY()
{
	// vertical, along the y axis (up and down)
	// 1243 \  / 2134                    a234 \  / 123d
	// 4321  \/  3412                    1b34  \/  12c4
	// 3412  /\  4321                    12c4  /\  1b34
	// 2134 /  \ 1243                    123d /  \ a234
	for (int x = 0; x < CELLS / 2; x++)
	{
		for (int y = 0; y < CELLS; y++)
		{
			int temp = m_board_x_y[x][y];
			m_board_x_y[x][y] = m_board_x_y[CELLS - x - 1][y];
			m_board_x_y[CELLS - x - 1][y] = temp;
		}
	}
}


#if WANT_SUDOKU_BOARD_ROTATION
template <size_t TGridSize>
void SudokuGameT<TGridSize>::TransformBoardRotate90()
{
	// rotate (rotation * 90deg) to the right
	// 1243 -> 2341                      a234 -> 111a
	// 4321 -> 1432                      1b34 -> 22b2
	// 3412 -> 3124                      12c4 -> 3c33
	// 2134 -> 4213                      123d -> d444

	TODO: implement and unit tests

	strategies: http ://stackoverflow.com/questions/42519/how-do-you-rotate-a-two-dimensional-array

	for each layer
		for each offset 0 to width
			do a 4 way swap of the corners+offset
				original_top_left = top_left
				top_left = bottom_left
				bottom_left = bottom_right
				bottom_right = top_right
				top_right = original_top_left
}
#endif


#if WANT_SUDOKU_BOARD_ROTATION
template <size_t TGridSize>
void SudokuGameT<TGridSize>::TransformBoardRotate180()
{
	// rotate twice to the right ( aka FlipX then FlipY )
	// 1243 -> 2341 -> 4312              a234 -> 111a -> d321
	// 4321 -> 1432 -> 2143              1b34 -> 22b2 -> 4c21
	// 3412 -> 3124 -> 1234              12c4 -> 3c33 -> 43b1
	// 2134 -> 4213 -> 3421              123d -> d444 -> 432a
	TransformBoardFlipX();
	TransformBoardFlipY();

	TODO: unit tests
}
#endif


#if WANT_SUDOKU_BOARD_ROTATION
template <size_t TGridSize>
void SudokuGameT<TGridSize>::TransformBoardRotate270()	
{
	// rotate thrice to the right (aka rotate90 then FlipX then FlipY)
	// 1243 -> 2341 -> 4312 -> 3124      a234 -> 111a -> d321 -> 444d
	// 4321 -> 1432 -> 2143 -> 4213      1b34 -> 22b2 -> 4c21 -> 33c3
	// 3412 -> 3124 -> 1234 -> 2341      12c4 -> 3c33 -> 43b1 -> 2b22
	// 2134 -> 4213 -> 3421 -> 1432      123d -> d444 -> 432a -> a111

	TODO: implement and unit tests
}
#endif


template <size_t TGridSize>
bool SudokuGameT<TGridSize>::Generate(int seed)
{
	Clear();

	// Use a seeded/determinisic psudorandom number generator
	std::mt19937 generator(seed);
	std::vector<int> answers;

	// put numbers in until we can't
	for (int x = 0; x < CELLS; x++)
	{
		for (int y = 0; y < CELLS; y++)
		{
			// Important: This returns SORTED answers, ascending
			FindPossibleAnswersFor(x, y, answers);
			if (answers.empty())
			{
				// This path is unsolveable
				return false;
			}
			// use the next number in the sequence as an array offset
			int position = generator() % answers.size();
			SetValue(x, y, answers[position]);
		}
	}

	return true;
}


void MyLatinSquare_UnitTest()
{
	////////////////////////////////////////
	// Generate a finished game
	// in production we would find good seeds ahead of time, put it in a DB and tell the client to use seed 'X'
	SudokuGame4 sg4_generate;
	for (int i = 0; i < 100; i++)
	{
		bool pass = sg4_generate.Generate(i);

		printf("generate sudokugame4 with seed: %d %s\n", i, (const char*)(pass ? "PASS" : "FAIL"));
	}

	// TODO: blank out some of the numbers to varying levels of difficulty
	//       difficulty is loosly consided to be a starting board with
	//       * ratio of unsolved to solved fields
	//       * most unsolved fields will have many possible answers
	//       * few unsolved fields will have few possible answers
	//       * is proramaticaly solveable
	//       * after solving the first few fields, the number of fields with low posible answer fields will stay low

	// TODO: flip/rotate the table for more variants

	/////////////////////////////////////////

	int table1[9][9] = {
		{ 6, 5, 0,  3, 0, 4,  8, 1, 2 },
		{ 0, 0, 1,  0, 0, 2,  0, 0, 0 },
		{ 0, 0, 9,  7, 0, 1,  4, 0, 0 },

		{ 8, 9, 0,  4, 0, 0,  6, 0, 0 },
		{ 0, 7, 5,  1, 0, 9,  2, 8, 0 },
		{ 0, 0, 3,  0, 0, 8,  0, 9, 4 },

		{ 0, 0, 8,  2, 0, 6,  9, 0, 0 },
		{ 0, 0, 0,  9, 0, 0,  3, 0, 0 },
		{ 9, 2, 4,  8, 0, 7,  0, 6, 5 },
	};

	int table2[9][9] = {
		{ 8, 4, 5,  9, 6, 2,  1, 3, 7 },
		{ 9, 1, 3,  7, 4, 5,  2, 8, 6 },
		{ 6, 7, 2,  3, 8, 1,  9, 5, 4 },

		{ 4, 2, 6,  1, 7, 3,  8, 9, 5 },
		{ 3, 8, 9,  4, 5, 6,  7, 1, 2 },
		{ 7, 5, 1,  8, 2, 9,  4, 6, 3 },

		{ 2, 3, 7,  5, 9, 8,  6, 4, 1 },
		{ 1, 6, 8,  2, 3, 4,  5, 7, 9 },
		{ 5, 9, 4,  6, 1, 7,  3, 2, 8 },
	};

	SudokuGame9 game;
	game.IsSolved();
	
	game.LoadTable(table1);
	assert(game.GetValue(SudokuGroupGrid, 0, 0) == 6);
	assert(game.GetValue(SudokuGroupGrid, 0, 1) == 5);
	assert(game.GetValue(SudokuGroupGrid, 0, 2) == 0);
	assert(game.GetValue(SudokuGroupGrid, 0, 3) == 0);
	assert(game.GetValue(SudokuGroupGrid, 0, 4) == 0);
	assert(game.GetValue(SudokuGroupGrid, 0, 5) == 1);
	assert(game.GetValue(SudokuGroupGrid, 0, 6) == 0);
	assert(game.GetValue(SudokuGroupGrid, 0, 7) == 0);
	assert(game.GetValue(SudokuGroupGrid, 0, 8) == 9);

	assert(game.GetValue(SudokuGroupRow, 0, 0) == 6);
	assert(game.GetValue(SudokuGroupRow, 0, 1) == 5);
	assert(game.GetValue(SudokuGroupRow, 0, 2) == 0);
	assert(game.GetValue(SudokuGroupRow, 0, 3) == 3);
	assert(game.GetValue(SudokuGroupRow, 0, 4) == 0);
	assert(game.GetValue(SudokuGroupRow, 0, 5) == 4);
	assert(game.GetValue(SudokuGroupRow, 0, 6) == 8);
	assert(game.GetValue(SudokuGroupRow, 0, 7) == 1);
	assert(game.GetValue(SudokuGroupRow, 0, 8) == 2);

	assert(game.GetValue(SudokuGroupCol, 0, 0) == 6);
	assert(game.GetValue(SudokuGroupCol, 0, 1) == 0);
	assert(game.GetValue(SudokuGroupCol, 0, 2) == 0);
	assert(game.GetValue(SudokuGroupCol, 0, 3) == 8);
	assert(game.GetValue(SudokuGroupCol, 0, 4) == 0);
	assert(game.GetValue(SudokuGroupCol, 0, 5) == 0);
	assert(game.GetValue(SudokuGroupCol, 0, 6) == 0);
	assert(game.GetValue(SudokuGroupCol, 0, 7) == 0);
	assert(game.GetValue(SudokuGroupCol, 0, 8) == 9);

	assert(game.GetValue(SudokuGroupGrid, 1, 0) == 3);
	assert(game.GetValue(SudokuGroupGrid, 1, 1) == 0);
	assert(game.GetValue(SudokuGroupGrid, 1, 2) == 4);
	assert(game.GetValue(SudokuGroupGrid, 1, 3) == 0);
	assert(game.GetValue(SudokuGroupGrid, 1, 4) == 0);
	assert(game.GetValue(SudokuGroupGrid, 1, 5) == 2);
	assert(game.GetValue(SudokuGroupGrid, 1, 6) == 7);
	assert(game.GetValue(SudokuGroupGrid, 1, 7) == 0);
	assert(game.GetValue(SudokuGroupGrid, 1, 8) == 1);

	assert(game.GetValue(SudokuGroupGrid, 8, 0) == 9);
	assert(game.GetValue(SudokuGroupGrid, 8, 1) == 0);
	assert(game.GetValue(SudokuGroupGrid, 8, 2) == 0);
	assert(game.GetValue(SudokuGroupGrid, 8, 3) == 3);
	assert(game.GetValue(SudokuGroupGrid, 8, 4) == 0);
	assert(game.GetValue(SudokuGroupGrid, 8, 5) == 0);
	assert(game.GetValue(SudokuGroupGrid, 8, 6) == 0);
	assert(game.GetValue(SudokuGroupGrid, 8, 7) == 6);
	assert(game.GetValue(SudokuGroupGrid, 8, 8) == 5);

	std::vector<int> answers;
	game.FindPossibleAnswersFor(0, 0, answers); // 6
	assert(answers.size() == 1);
	assert(answers[0] == 7);
	game.FindPossibleAnswersFor(0, 1, answers); // 0
	game.FindPossibleAnswersFor(1, 0, answers); // 5
	assert(answers.size() == 3);
	game.FindPossibleAnswersFor(1, 1, answers); // 0
	assert(answers.size() == 3);

	////////////////////////////////////////////////////////////////////
	int value = 0;
	game.LoadTable(table2);

	for (int x = 0; x < 9; x++)
	{
		for (int y = 0; y < 9; y++)
		{
			value = game.GetValue(x, y);
			assert(value == table2[x][y]);
			game.SetValue(x, y, 0);
			game.FindPossibleAnswersFor(x, y, answers);
			assert(answers.size() == 1);
			assert(answers[0] == value);
			game.SetValue(x, y, value);
		}
	}

	////////////////////////////////////////////////////////////////////

	//SudokuGame0   sg0;
	//SudokuGame2   sg2;
	SudokuGame4   sg4;
	SudokuGame9   sg9;
	SudokuGame16  sg16;
	SudokuGame25  sg25;
	SudokuGame36  sg36;
	SudokuGame49  sg49;
	SudokuGame64  sg64;
	SudokuGame81  sg81;
	SudokuGame100 sg100;

}