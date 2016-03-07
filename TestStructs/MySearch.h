#pragma once

#include <assert.h>

void MySearch_UnitTest();

/*
	binary search on sorted and assending data (left<=middle<=right)
	returns
		-1   Not found
		-2   bad non-sorted data
		>=0  index of searchValue 
*/
int32_t my_binary_search(int32_t *arrayPtr, size_t arrayLen, const int32_t &searchValue);


void my_quicksort();
