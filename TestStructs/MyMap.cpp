#include "stdafx.h"

#include "MyMap.h"
#include <assert.h>
#include <stdint.h>

bool MyBinaryTree_UnitTest()
{
	printf("\nTESTING: MyBinaryTree");

	MyBinaryTree<int, int> bt;
	int bt_seed_data[] = { 5, 3, 1, 9, 2, 7, 6, 8, 0, 4, 5, 5, 5 };

	/*
		Should create a tree like this
		          5
		      /       \
		     3         9
		   /  \       /
		  1    4     7
		 / \        / \
		0   2      6   8
	*/
	int bt_delete_order[] = { 0, 2, 3, 7, 5, 6, 4, 8, 9, 1 };
	int bt_unique_count = 10;
	assert(sizeof(bt_delete_order) / sizeof(bt_delete_order)[0] == bt_unique_count);  // needs to be a static_assert

	// Put elements in
	for (auto i : bt_seed_data)
	{
		bt.set(i, i * 10);
	}

	// tree doesn't allow duplicates
	if (bt.size() != bt_unique_count)
	{
		assert(!"Wrong number of elements");
		return false;
	}

	// all the things we added should be there
	for (auto i : bt_seed_data)
	{
		if (!bt.contains(i))
		{
			assert(!"unable to find a key");
			return false;
		}

		int value;
		if (!bt.get(i, value))
		{
			assert(!"unable to get a value for a key");
			return false;
		}

		if (value != i * 10)
		{
			assert(!"That key has the wrong value");
			return false;
		}
	}

	printf("\n");
	bt.iterate([](int key, int value)
	{
		printf("(%d:%d) ", key, value);
	});
	//printf("\n");

	bt.dump();

	for (int i = 0; i < bt_unique_count; i++)
	{
		printf("\nRemoving %d\n", bt_delete_order[i]);

		if (!bt.contains(bt_delete_order[i]))
		{
			assert(!"That should be in there");
			return false;
		}

		bt.remove(bt_delete_order[i]);

		bt.dump();

		if (bt.contains(bt_delete_order[i]))
		{
			//bt.dump();
			assert(!"Didn't I just remove that?");
			return false;
		}
	}
	if (bt.size() != 0)
	{
		bt.dump();
		assert(!"should be empty");
		return false;
	}

	bt.set(1, 1);

	printf("\nPASS");

	return true;
}

void MyMap_UnitTest()
{
	MyBinaryTree_UnitTest();
}