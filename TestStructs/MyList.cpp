#include "stdafx.h"

#include "MyList.h"
#include <assert.h>
#include <stdint.h>


/****************************************************************************
* Unit tests for the collections
*/

struct SimpleObj
{
	SimpleObj(size_t value = 0)
		: m_value(value)
	{}

	size_t m_value;

	inline bool operator==(const SimpleObj& other) { return other.m_value == m_value; }
	inline bool operator!=(const SimpleObj& other) { return other.m_value != m_value; }
};

template<typename TType, size_t TSize>
bool Test_stack_from_array(const TType(&simpleArray)[TSize])
{
	MyStack<TType> stack;
	TType data;

	// add it left to right
	for (size_t i = 0; i < TSize; i++)
	{
		stack.Push(simpleArray[i]);
	}

	if (stack.Size() != TSize)
	{
		assert(!"Not all the elements went into the stack");
		return false;
	}

	if (!stack.Validate())
	{
		assert(!"size integrety fail");
		return false;
	}

	for (size_t i = 0; i < TSize; i++)
	{
		if (!stack.FindValueNPositionsFromTheHead(data, i))
		{
			assert(!"Data is not where we expect it to be from the head");
			return false;
		}
		if (data != simpleArray[TSize - i - 1])
		{
			assert(!"Didn't get back the expected value from N from head");
			return false;
		}

		if (!stack.FindValueNPositionsFromTheTail(data, i))
		{
			assert(!"Data is not where we expect it to be from the tail");
			return false;
		}
		if (data != simpleArray[i])
		{
			assert(!"Didn't get back the expected value from N from tail");
			return false;
		}
	}

	if (stack.FindValueNPositionsFromTheHead(data, TSize))
	{
		assert(!"Should not have been able to access an element with that index from the head");
		return false;
	}

	if (stack.FindValueNPositionsFromTheTail(data, TSize))
	{
		assert(!"Should not have been able to access an element with that index from the tail");
		return false;
	}

	// pop it and walk our source array right to left
	for (size_t i = TSize; i > 0; i--)
	{
		if (!stack.Pop(data))
		{
			assert(!"Unable to retrieve data");
			return false;
		}

		if (data != simpleArray[i-1])
		{
			assert(!"mismatched data!");
			return false;
		}
	}

	// should fail
	if (stack.Pop(data))
	{
		assert(!"That should have failed");
	}

	if (stack.Size())
	{
		assert(!"The stack should be empty, but it's not");
		return false;
	}

	if (!stack.Validate())
	{
		assert(!"size integrety fail");
		return false;
	}

	return true;
}

template<typename TType, size_t TSize>
bool Test_dlist_from_array(const TType(&simpleArray)[TSize])
{
	MyDoubleLinkedList<TType> dlist;
	TType data;

	/////////////////////////////
	// Add it to the head
	/////////////////////////////

	// add it left to right
	for (size_t i = 0; i < TSize; i++)
	{
		dlist.PushHead(simpleArray[i]);
	}

	if (dlist.Size() != TSize)
	{
		assert(!"Not all the elements went into the stack");
		return false;
	}

	if (!dlist.Validate())
	{
		assert(!"size integrety fail");
		return false;
	}

	// pop it and walk our source array right to left
	for (size_t i = TSize; i > 0; i--)
	{
		if (!dlist.PopHead(data))
		{
			assert(!"Unable to retrieve data");
			return false;
		}

		if (data != simpleArray[i - 1])
		{
			assert(!"mismatched data!");
			return false;
		}
	}

	// should fail
	if (dlist.PopHead(data))
	{
		assert(!"should of failed, but didn't?");
	}

	if (!dlist.Validate())
	{
		assert(!"size integrety fail");
		return false;
	}

	if (dlist.Size())
	{
		assert(!"The collection should be empty, but it's not");
		return false;
	}

	//////////////////////////////////
	// Add it to the end this time
	//////////////////////////////////
	
	// add it right to left
	for (size_t i = TSize; i > 0; i--)
	{
		dlist.PushTail(simpleArray[i - 1]);
	}

	if (dlist.Size() != TSize)
	{
		assert(!"Not all elements added");
	}

	if (!dlist.Validate())
	{
		assert(!"size integrety fail");
		return false;
	}

	// Pop it left to right
	for (size_t i = 0; i < TSize; i++)
	{
		TType data;
		if (!dlist.PopTail(data))
		{
			assert(!"unable to get the tail element");
		}

		if (data != simpleArray[i])
		{
			assert(!"data mismatch");
		}
	}

	if (!dlist.Validate())
	{
		assert(!"size integrety fail");
		return false;
	}

	if (dlist.Size())
	{
		assert(!"The collection should be empty, but it's not");
		return false;
	}

	return true;
}


void MyStack_UnitTest()
{
	////////////////////////////////////////////////
	uint64_t stack_data_uint8[] = {
		0, 1, 2, 3, UINT8_MAX
	};

	printf("\nTESTING: Stack of uint8_t from array");
	if (Test_stack_from_array(stack_data_uint8)) {
		printf("\nPASS");
	}
	else {
		printf("\nFAIL");
	}

	

	////////////////////////////////////////////////
	uint64_t stack_data_uint64[] = {
		0, 1, 2, 3, UINT8_MAX, UINT16_MAX, UINT32_MAX, UINT64_MAX
	};

	printf("\nTESTING: Stack of uint64_t from array");
	if (Test_stack_from_array(stack_data_uint64)) {
		printf("\nPASS");
	}
	else {
		printf("\nFAIL");
	}

	////////////////////////////////////////////////
	double stack_data_double[] = {
		0.0, 1.0, 0.2, 3.0
	};

	printf("\nTESTING: Stack of double from array");
	if (Test_stack_from_array(stack_data_double)) {
		printf("\nPASS");
	}
	else {
		printf("\nFAIL");
	}

	////////////////////////////////////////////////
	SimpleObj stack_data_simpleobj[] = { SimpleObj(1), 2, 3, 4 };

	printf("\nTESTING: Stack of SimpleObj from array");
	if (Test_stack_from_array(stack_data_simpleobj)) {
		printf("\nPASS");
	}
	else {
		printf("\nFAIL");
	}
}

void MyDoubleLinkedList_UnitTest()
{
	////////////////////////////////////////////////
	printf("\nTESTING: MyDoubleLinkedList from array of uint8_t");

	uint64_t dlist_data_uint8[] = {
		1, 2, 3
	};

	if (Test_dlist_from_array(dlist_data_uint8)) {
		printf("\nPASS");
	}
	else {
		printf("\nFAIL");
	}


	////////////////////////////////////////////////
	printf("\nTESTING: MyDoubleLinkedList from array of SimpleObj");

	SimpleObj dlist_data_simpleobj[] = { SimpleObj(1), 2, 3, 4 };

	if (Test_dlist_from_array(dlist_data_simpleobj)) {
		printf("\nPASS");
	}
	else {
		printf("\nFAIL");
	}
}

void MyList_UnitTest()
{
	MyStack_UnitTest();
	MyDoubleLinkedList_UnitTest();
}
