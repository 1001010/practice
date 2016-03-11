#include "stdafx.h"

#include "MyCircularBuffer.h"
#include <assert.h>
#include <stdint.h>
#include <assert.h>
#include <list>
#include <algorithm>

void TestSingleAdd(MyUncomfortableMovingAverage &collection, int add, double expected, uint8_t precision)
{
	int factor = 1;
	for (uint8_t i = 0; i < precision; i++) 
	{
		factor *= 10;
	}

	double result = collection.GetAvg(add);

	// I don't trust floating point value comparisons
	int64_t int_expected = int64_t(expected * factor);
	int64_t int_result   = int64_t(result   * factor);

	assert(int_expected == int_result);
}


template <typename TMyMovingAverage, typename TAddType>
void Test_MyMovingAverage_AddOne(TMyMovingAverage &collection, TAddType add, double expected, uint8_t precision)
{
	int factor = 1;
	for (uint8_t i = 0; i < precision; i++)
	{
		factor *= 10;
	}

// BEGIN HACK, TODO: Remove the need for this
#pragma warning (disable: 4800)  // warning C4800: 'int': forcing value to bool 'true' or 'false' (performance warning)

	collection.add(add);

#pragma warning (default: 4800)
// END HACK

	// I don't trust floating point value comparisons
	int64_t int_expected = int64_t(expected * factor);
	int64_t int_average  = int64_t(collection.average * factor);

	assert(int_expected == int_average);
}

struct test_sample_int {
	int      m_add;
	double   m_expected;
	uint8_t  m_precision;
};

template <typename TMyMovingAverage>
void Test_MyMovingAverage_AddMany(TMyMovingAverage &collection, test_sample_int *samples, size_t num_samples)
{
	for (size_t i = 0; i < num_samples; i++)
	{
		Test_MyMovingAverage_AddOne(collection, samples[i].m_add, samples[i].m_expected, samples[i].m_precision);
	}
}

struct test_sample_double {
	float	m_add;
	double	m_expected;
	uint8_t	m_precision;
};

template <typename TMyMovingAverage>
void Test_MyMovingAverage_AddMany(TMyMovingAverage &collection, test_sample_double *samples, size_t num_samples)
{
	for (size_t i = 0; i < num_samples; i++)
	{
		Test_MyMovingAverage_AddOne(collection, samples[i].m_add, samples[i].m_expected, samples[i].m_precision);
	}
}

void MyCircularBuffer_UnitTest()
{
	//MyCircularBufferFixed<int32_t, 3> cbuf;
	
	MyUncomfortableMovingAverage uncomfortable(3);
	TestSingleAdd(uncomfortable, 7, 7.00, 2);
	TestSingleAdd(uncomfortable, 3, 5.00, 2);
	TestSingleAdd(uncomfortable, 9, 6.33, 2);
	TestSingleAdd(uncomfortable, 5, 5.66, 2);

	test_sample_int samples_for_3[] = {
		{ 7, 7.00, 2 },
		{ 3, 5.00, 2 },
		{ 9, 6.33, 2 },
		{ 5, 5.66, 2 },
	};
	size_t num_samples_for_3 = ARRAY_SIZE(samples_for_3);

	test_sample_int samples_for_3_bools[] = {
		{ 0, 0.00, 2 },
		{ 1, 0.50, 2 },
		{ 1, 0.66, 2 },
		{ 1, 1.00, 2 },
	};
	size_t num_samples_for_3_bools = ARRAY_SIZE(samples_for_3_bools);

	MyMovingIntegerAverage<bool,     3>  m0;
	MyMovingIntegerAverage<int,      3>  m1;
	MyMovingIntegerAverage<int8_t,   3>  m2;
	MyMovingIntegerAverage<int16_t,  3>  m3;
	MyMovingIntegerAverage<int32_t,  3>  m4;
	MyMovingIntegerAverage<uint8_t,  3>  m5;
	MyMovingIntegerAverage<uint16_t, 3>  m6;
	MyMovingIntegerAverage<uint32_t, 3>  m7;
	//MyMovingIntegerAverage <double, 5> moving_fail_double;
	//MyMovingIntegerAverage<std::stringbuf, 5> moving_fail_string;

	Test_MyMovingAverage_AddMany(m0, samples_for_3_bools, num_samples_for_3_bools);
	Test_MyMovingAverage_AddMany(m1, samples_for_3, num_samples_for_3);
	Test_MyMovingAverage_AddMany(m2, samples_for_3, num_samples_for_3);
	Test_MyMovingAverage_AddMany(m3, samples_for_3, num_samples_for_3);
	Test_MyMovingAverage_AddMany(m4, samples_for_3, num_samples_for_3);
	Test_MyMovingAverage_AddMany(m5, samples_for_3, num_samples_for_3);
	Test_MyMovingAverage_AddMany(m6, samples_for_3, num_samples_for_3);
	Test_MyMovingAverage_AddMany(m7, samples_for_3, num_samples_for_3);

	test_sample_double samples_for_3_floats[] = {
		{ 0.00f, 0.00, 2 },
		{ 1.00f, 0.50, 2 },
		{ 0.01f, 0.33, 2 },
		{ 0.99f, 0.66, 2 },
	};
	size_t num_samples_for_3_floats = ARRAY_SIZE(samples_for_3_floats);
	MyMovingFloatAverage<3> mf0;

	Test_MyMovingAverage_AddMany(mf0, samples_for_3_floats, num_samples_for_3_floats);
}