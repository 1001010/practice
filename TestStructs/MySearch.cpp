#include "stdafx.h"

#include "MySearch.h"
#include <assert.h>
#include <stdint.h>


int32_t my_binary_search(int32_t *arrayPtr, size_t arrayLen, const int32_t &searchValue)
{
	const int32_t FIRST_VALID =  0;
	const int32_t NOT_FOUND   = -1;
	const int32_t NOT_ORDERED = -2;

	// Empty?
	if (arrayPtr == nullptr || arrayLen == 0)
	{
		return NOT_FOUND;
	}

	int32_t midPosition = (int32_t)arrayLen / 2;

	// firstElement <= middleElement <= lastElement
	if ((arrayPtr[0] > arrayPtr[midPosition]) ||
		(arrayPtr[midPosition] > arrayPtr[arrayLen - 1])
		)
	{
		return NOT_ORDERED;
	}

	// Bounds check
	if (searchValue < arrayPtr[0] || searchValue > arrayPtr[arrayLen - 1])
	{
		return NOT_FOUND;
	}

	if (searchValue < arrayPtr[midPosition])
	{
		// Look on the left: 0..mid
		return my_binary_search(arrayPtr, midPosition, searchValue);
	}
	else if (searchValue > arrayPtr[midPosition])
	{
		// look on the right: mid..end
		if ((int32_t)arrayLen - midPosition < 0)
		{
			assert(!"Not supposed to happen");
		}
		int32_t result = my_binary_search(arrayPtr + midPosition, arrayLen - midPosition, searchValue);
		if (result < FIRST_VALID)
		{
			return result;
		}
		return result + midPosition;
	}

	// was in the middle all along
	return midPosition;
}

void MySearch_UnitTest()
{
	int32_t data_a[] = { 0, 1, 2, 3 };
	assert(my_binary_search(data_a, 4, -1) == -1);
	assert(my_binary_search(data_a, 4, 0) == 0);
	assert(my_binary_search(data_a, 4, 1) == 1);
	assert(my_binary_search(data_a, 4, 2) == 2);
	assert(my_binary_search(data_a, 4, 3) == 3);
	assert(my_binary_search(data_a, 4, 4) == -1);

	assert(my_binary_search(data_a, 3, 0) == 0);
	assert(my_binary_search(data_a, 3, 1) == 1);
	assert(my_binary_search(data_a, 3, 2) == 2);
	assert(my_binary_search(data_a, 3, 3) == -1);
	
	assert(my_binary_search(data_a, 2, 0) == 0);
	assert(my_binary_search(data_a, 2, 1) == 1);
	assert(my_binary_search(data_a, 2, 2) == -1);
	assert(my_binary_search(data_a, 2, 3) == -1);

	assert(my_binary_search(data_a, 1, 0) == 0);
	assert(my_binary_search(data_a, 1, 1) == -1);
	assert(my_binary_search(data_a, 1, 2) == -1);
	assert(my_binary_search(data_a, 1, 3) == -1);

	assert(my_binary_search(data_a, 0, 0) == -1);
	
	int32_t data_b[] = { 3, 2, 1, 0 };
	assert(my_binary_search(data_b, 4, 0) == -2);
	assert(my_binary_search(data_b, 4, 1) == -2);
	assert(my_binary_search(data_b, 4, 2) == -2);
	assert(my_binary_search(data_b, 4, 3) == -2);

	assert(my_binary_search(data_b, 3, 0) == -2);
	assert(my_binary_search(data_b, 3, 1) == -2);
	assert(my_binary_search(data_b, 3, 2) == -2);

	assert(my_binary_search(data_b, 2, 0) == -2);
	assert(my_binary_search(data_b, 2, 1) == -2);

	assert(my_binary_search(data_b, 1, 3) == 0);

	assert(my_binary_search(data_b, 0, 0) == -1);
}

void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

int choose_pivot(int i, int j)
{
	return ((i + j) / 2);
}

void my_quicksort(int list[], int m, int n)
{
	int key, i, j, pivot;
	if (m < n)
	{
		pivot = choose_pivot(m, n);
		swap(&list[m], &list[pivot]);
		key = list[m];
		i = m + 1;
		j = n;
		while (i <= j)
		{
			while ((i <= n) && (list[i] <= key))
			{
				i++;
			}
			while ((j >= m) && (list[j] > key))
			{
				j--;
			}
			if (i < j)
			{
				swap(&list[i], &list[j]);
			}
		}
		swap(&list[m], &list[j]);

		// go deeper
		my_quicksort(list, m, j - 1);
		my_quicksort(list, j + 1, n);
	}
}