#include "stdafx.h"

#include "MyHash.h"
#include <assert.h>
#include <stdint.h>
#include <assert.h>


void MyHash_UnitTest()
{
	printf("\nTESTING MyHash\n");
	MyHashTableOfStringsToStrings test;
	test.Set("Hello", "World");
	test.Set("Hello", "World");
	test.Set("a", "aaaa");
	test.Set("b", "bbbb");
	test.Set("c", "cccc");
	test.Set("d", "dddd");
	test.Set("e", "eeee");
	test.Set("f", "ffff");
	test.Set("g", "gggg");
	std::string value;
	assert(test.Lookup("Hello", value));
	assert(!test.Lookup("bogus", value));
	test.dump();
}