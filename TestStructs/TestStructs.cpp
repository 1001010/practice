// TestStructs.cpp : Defines the entry point for the console application.
// This is not intended to be a usefull app or library for anyone 
//

#include "stdafx.h"
#include "MyList.h"
#include "MySearch.h"
#include "MyMap.h"
#include <assert.h>

int main()
{
	printf("Running unit tests\n");

	MyList_UnitTest();
	MySearch_UnitTest();
	
	MyBinaryTree<int,int> bt;
	int bt_seed_data[] = { 5, 3, 1, 9, 2, 7, 6, 8, 0, 4, 5, 5, 5 };
	for (auto i : bt_seed_data)
	{
		bt.set(i, i * 10);
	}
	assert(bt.size() == 10);

	for (auto i : bt_seed_data)
	{
		assert(bt.contains(i));
	}

	bt.iterate([](int key, int value)
	{
		printf("%d == %d\n", key, value);
	}
	);

	printf("\nComplete.\n");
    return 0;
}

