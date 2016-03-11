#pragma once

#include <assert.h>
#include <algorithm>
#include <type_traits>
#include <stdint.h>

void MyCircularBuffer_UnitTest();


/*
	This is from an interview I had.
	I like my constuctors to only do the bare, safe, minimum initialization to avoid uintended behaviours
	Things I don't like in my c-tors...
	- Creating threads
	- File operations
	- anything blocking
	- dynamic memory allocation
	- returning failures / throwing exceptions
	- any unexpected behaviour if someone were to use a generated copy c-tor
	I like to avoid them, but I will do them if there isn't a more elegant solution.
*/
class MyUncomfortableMovingAverage
{
public:
	MyUncomfortableMovingAverage(int win_size)
	{
		if (win_size < 1) {
			assert(!"don’t do that");
			throw -1;
		}
		m_seen = 0;
		m_window_size = win_size;
		m_history = new int[m_window_size];
		m_total = 0.0;
		memset(m_history, 0, sizeof(int)*m_window_size);
	}

	~MyUncomfortableMovingAverage()
	{
		delete[] m_history;
		m_history = nullptr;
	}

	double GetAvg(int new_val) 
	{
		if (m_seen >= m_window_size) {
			m_total -= m_history[m_seen % m_window_size];
		}
		m_total += new_val;

		m_history[m_seen++ % m_window_size] = new_val;

		return m_total / std::min(m_seen, m_window_size);
	}

protected:
	int m_seen;
	int m_window_size;
	int *m_history;
	double m_total;
};


template<typename TTypeA, typename TTypeB>
bool will_overflow_if_added(const TTypeA &a, const TTypeB &b)
{
	// It's super naive! <strike>effective!</strike>

	// TODO: Read up on how to best detect overflows. I doubt my method works across all systems, for larger value types
	if ((a + b) < a)
	{
		return true;
	}
	return false;
}


/*
	Slightly better moving average that doesn't bug my spidy sense AS much
	NOTE: There is a good chance that if the TWindowSize &/or value in the added integers are large enough
	      WE WILL OVERFLOW
		  In the event of possible overflow, added values WILL BE SET TO ZERO
		  It's inelegant - but it's a strategy.
*/
template <typename TIntegerType, size_t TWindowSize>
class MyMovingIntegerAverage
{
protected:
	size_t       m_position;
	size_t       m_size;
	double       m_total;
	double       m_average;
	TIntegerType m_history[TWindowSize];

public:
	MyMovingIntegerAverage()
		: m_position(0)
		, m_size(0)
		, size(m_size)
		, m_total(0.0)
		, m_average(0.0)
		, average(m_average)
		, capacity(TWindowSize)		
	{
		static_assert(TWindowSize > 0, "Must have a non-zero collection of elements");
		static_assert(TWindowSize < UINT16_MAX, "That's a mighty big TWindowSize you have there, this collection is not optimized for that range. check your template params");
		static_assert(std::numeric_limits<TIntegerType>::is_integer, "Integers only");
		static_assert(std::numeric_limits<TIntegerType>::digits <= 32, "Untested with ints more than 32bits in size");
	}

	// easy lookup
	const double & average;
	const size_t & capacity;
	const size_t & size;

	// add in a new value
	bool add(const TIntegerType &new_val)
	{
		bool result = false;

		if (m_size < TWindowSize)
		{
			m_size++;
		}
		else
		{
			m_total -= m_history[m_position % TWindowSize];
		}

		if (will_overflow_if_added(m_total, new_val))
		{
			// OVERFLOW PROTECTION!  OK - it's not the best protection. It's rather naive.
			// TODO: Read up on how to best detect overflows. I doubt my (a+b < a) method works across all systems, for larger int types
			assert(!"Overflow condition detected and prevented");
			m_history[m_position++ % TWindowSize] = 0;
			result = false;
		}
		else
		{
			// should be safe to add in
			m_total += new_val;
			m_history[m_position++ % TWindowSize] = new_val;
			result = true;
		}

		m_average = m_total / m_size;
		return result;
	}
};


/*
	For storing floating point values between 0.0 and 1.0
*/
template <size_t TWindowSize>
class MyMovingFloatAverage
{
protected:
	size_t       m_position;
	size_t       m_size;
	long double  m_total;
	double       m_average;
	float        m_history[TWindowSize];

public:
	MyMovingFloatAverage()
		: m_position(0)
		, m_size(0)
		, size(m_size)
		, m_total(0.0)
		, m_average(0.0)
		, average(m_average)
		, capacity(TWindowSize)
	{
		static_assert(TWindowSize > 0, "Must have a non-zero collection of elements");
		static_assert(TWindowSize < UINT16_MAX, "That's a mighty big TWindowSize you have there, this collection is not optimized for that range. check your template params");
	}

	// easy lookup
	const double & average;
	const size_t & capacity;
	const size_t & size;

	// add in a new value
	bool add(float value)
	{
		bool result = false;

		if (value < 0.0 || value > 1.0)
		{
			assert(!"param is out of range of zero to one");
			return result;
		}

		int ftype = fpclassify(value);
		if (ftype == FP_INFINITE || ftype == FP_NAN || ftype == FP_SUBNORMAL)
		{
			assert(!"Bad floating point clasification");
			return result;
		}

		if (m_size < TWindowSize)
		{
			m_size++;
		}
		else
		{
			m_total -= m_history[m_position % TWindowSize];
		}

		if (will_overflow_if_added(m_total, value))
		{
			assert(!"Overflow condition detected and prevented");
			m_history[m_position++ % TWindowSize] = 0.0;
			result = false;
		}
		else
		{
			// should be safe to add in
			m_total += value;
			m_history[m_position++ % TWindowSize] = value;
			result = true;
		}

		m_average = m_total / m_size;
		return result;
	}
};



#if 0 // not ready
template <typename TType, size_t TWindowSize>
class MyCircularBufferFixed
{
protected:
	TType m_buffer[TWindowSize];
	size_t m_position;
	size_t m_size;

public:
	const size_t &size;

	MyCircularBufferFixed()
		: m_position(0)
		, m_size(0)
		, size(m_size)
	{
		#pragma message("CAUTION: MyCircularBufferFixed is untested and experimental, waiting for unit tests")
	}

	void add(const TType &data)
	{
		m_buffer[m_position] = data;
		m_position = (m_position + 1) % TWindowSize;
		if (m_size < TWindowSize)
		{
			m_size++;
		}
	}

	bool get(size_t index, TType &result)
	{
		if (index >= m_size)
		{
			return false;
		}

		result = m_buffer[(m_position + index) % TWindowSize];
		return true;
	}
};
#endif //0 not ready