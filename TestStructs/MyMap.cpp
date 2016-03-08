#include "stdafx.h"

#include "MyMap.h"
#include <assert.h>
#include <stdint.h>

bool MyBinaryTree_UnitTest()
{
	MyBinaryTree<int, int> bt;
	int bt_seed_data[] = { 5, 3, 1, 9, 2, 7, 6, 8, 0, 4, 5, 5, 5 };
	int bt_normalized[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int bt_unique_count = 10;
	for (auto i : bt_seed_data)
	{
		bt.set(i, i * 10);
	}
	if (bt.size() != bt_unique_count)
	{
		assert(!"Wrong number of elements");
		return false;
	}

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
	}

	printf("\n");
	bt.iterate([](int key, int value)
	{
		printf("(%d:%d) ", key, value);
	});
	printf("\n");

	printf("\n");
	bt.dump();

	for (int i = 0; i < bt_unique_count; i++)
	{
		printf("\nRemoving %d\n", i);

		if (!bt.contains(i))
		{
			assert(!"That should be in there");
			return false;
		}

		bt.remove(i);

		bt.dump();

		if (bt.contains(i))
		{
			assert(!"Didn't I just remove that?");
			return false;
		}
	}
	if (bt.size() != 0)
	{
		assert(!"should be empty");
		return false;
	}

	

	return true;
}

void MyMap_UnitTest()
{
	MyBinaryTree_UnitTest();
}