// TestStructs.cpp : Defines the entry point for the console application.
// This is not intended to be a usefull app or library for anyone 
//

#include "stdafx.h"
#include "MyList.h"
#include "MySearch.h"
#include "MyMap.h"
#include "MyCircularBuffer.h"
#include "MyHash.h"

int main()
{
	printf("Running unit tests\n");

	MyList_UnitTest();
	MySearch_UnitTest();
	MyMap_UnitTest();
	MyCircularBuffer_UnitTest();
	MyHash_UnitTest();

	printf("\nComplete.\n");
    return 0;
}

