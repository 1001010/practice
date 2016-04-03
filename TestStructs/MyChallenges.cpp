#include "stdafx.h"
#include "MyChallenges.h"
#include <assert.h>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <list>
#include <set>

class Solution_leet_code_242 
{
public:
	bool isAnagram(std::string s, std::string t)
	{
		if (s.length() != t.length())
			return false;

		std::map<char, size_t> ms, mt;
		for (auto a : s) {
			ms[a] += 1;
		}
		for (auto a : t) {
			mt[a] += 1;
		}
		return ms == mt;
	}

	Solution_leet_code_242()
	{
		printf("Solution_leet_code_242\n");
		/*
		Given two strings s and t, write a function to determine if t is an anagram of s.

		For example,
		s = "anagram", t = "nagaram", return true.
		s = "rat", t = "car", return false.
		*/
		assert(false == isAnagram("race", "carr"));
		assert(true == isAnagram("bob", "obb"));
	}
};

class Solution_leet_code_27 {
public:
	int removeElement(std::vector<int>& nums, int val) {
		nums.erase(
			std::remove_if(nums.begin(), nums.end(), [&](int v) {
			return v == val;
		}),
			nums.end());
		return (int)nums.size();
	}

	Solution_leet_code_27()
	{
		printf("Solution_leet_code_27\n");
		/*
		Given an array and a value, remove all instances of that value in place and return the new length.

		Do not allocate extra space for another array, you must do this in place with constant memory.

		The order of elements can be changed. It doesn't matter what you leave beyond the new length.

		Example:
		Given input array nums = [3,2,2,3], val = 3

		Your function should return length = 2, with the first two elements of nums being 2.
		*/
		std::vector<int> nums = { 3,2,2,3 };
		removeElement(nums, 3);
		assert(nums.size() == 2);
		assert(nums[0] == 2);
		assert(nums[1] == 2);
	}
};

class Solution_leet_code_283 {
public:
	void moveZeroes(std::vector<int>& nums) {
		size_t count = nums.size();
		for (size_t i = 0; i < count; i++)
		{
			if (nums[i])
				continue;

			// We are at a zero, scan ahead to the next non-zero
			size_t next = i + 1;
			while (next < count && !nums[next])
			{
				next++;
			}

			if (next >= count)
			{
				break;
			}

			nums[i] = nums[next];
			nums[next] = 0;
		}
	}

	Solution_leet_code_283()
	{
		printf("Solution_leet_code_283\n");
		/*
		Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.

		For example, given nums = [0, 1, 0, 3, 12], after calling your function, nums should be [1, 3, 12, 0, 0].

		Note:
		You must do this in-place without making a copy of the array.
		Minimize the total number of operations.
		*/

		std::vector<int> nums = { 0, 1, 0, 3, 12 };
		moveZeroes(nums);
		assert(nums.size() == 5);
		assert(nums[0] == 1);
		assert(nums[1] == 3);
		assert(nums[2] == 12);
		assert(nums[3] == 0);
		assert(nums[4] == 0);
	}
};

class Solution_leet_code_258 {
public:
	int addDigits(int num) {
		if (num < 10)
		{
			return num;
		}
		int sum = 0;
		int digit = 0;
		while (num)
		{
			digit = num % 10;
			sum += digit;
			num -= digit;
			num /= 10;
		}
		return addDigits(sum);
	}

	Solution_leet_code_258()
	{
		printf("Solution_leet_code_258\n");
		/*
		Given a non-negative integer num, repeatedly add all its digits until the result has only one digit.

		For example:

		Given num = 38, the process is like: 3 + 8 = 11, 1 + 1 = 2. Since 2 has only one digit, return it.
		*/
		assert(addDigits(38) == 2);
	}
};

class Solution_leet_code_65 {
public:
	bool isNumber(std::string s) {
#if 0
		char *start_ptr = (char *)s.c_str();
		char *end_ptr = nullptr;
		double res = strtod(start_ptr, &end_ptr);
		return start_ptr != end_ptr && end_ptr && *end_ptr == 0;
#else
		// trim the string
		while (!s.empty() && s[0] == ' ')
		{
			s.erase(0, 1);
		}
		while (!s.empty() && s[s.length() - 1] == ' ')
		{
			s.erase(s.length() - 1, 1);
		}

		const size_t s_length = s.length();

		int pos_period = -1;
		int pos_exponent = -1;
		size_t num_digits = 0;
		
		for (int i = 0; i < (int)s_length; i++)
		{
			// Is it a digit?
			if (s[i] >= '0' && s[i] <= '9')
			{
				num_digits++;
				continue;
			}
			else if (s[i] == '.')
			{
				if (pos_period != -1)
					return false;
				pos_period = i;
			}
			else if (s[i] == 'e')
			{
				if (pos_exponent != -1)
					return false;
				if (num_digits == 0)
					return false;
				pos_exponent = i;
			}
			else if (s[i] == '-')
			{
				if (i == 0)
					continue;
				if (i == pos_exponent + 1)
					continue;
				return false;
			}
			else if (s[i] == '+')
			{
				if (i == 0)
					continue;
				if (i == pos_exponent + 1)
					continue;
				return false;
			}
			else
			{
				return false;
			}
		}

		if (pos_period >= 0 && pos_exponent >= 0)
		{
			if (pos_period == 0 && abs(pos_exponent - pos_period) == 1)
			{
				return false;
			}

			if (pos_exponent < pos_period)
			{
				return false;
			}
		}

		if (pos_exponent == 0 || pos_exponent == s_length - 1)
		{
			return false;
		}

		// no trailing sign
		if (s[s_length - 1] == '-' || s[s_length - 1] == '+')
		{
			return false;
		}

		if (num_digits < 1)
			return false;
		
		return true;
#endif
	}

	Solution_leet_code_65()
	{
		printf("Solution_leet_code_65\n");
		/*
		Validate if a given string is numeric.

		Some examples:
		"0" => true
		" 0.1 " => true
		"abc" => false
		"1 a" => false
		"2e10" => true
		Note: It is intended for the problem statement to be ambiguous. You should gather all requirements up front before implementing one.
		*/

		assert(isNumber("0") == true);
		assert(isNumber(" 0.1 ") == true);
		assert(isNumber("abc") == false);
		assert(isNumber("1 a") == false);
		assert(isNumber("2e10") == true);
		assert(isNumber("0e") == false);
		assert(isNumber("1 ") == true);
		assert(isNumber(" ") == false);
		assert(isNumber(".1") == true);
		assert(isNumber("3.") == true);
		assert(isNumber(". 1") == false);
		assert(isNumber(".e1") == false);
		assert(isNumber("1 .") == false);
		assert(isNumber(".") == false);
		assert(isNumber(" . ") == false);
		assert(isNumber("0e ") == false);
		assert(isNumber("te1") == false);
		assert(isNumber("-1.") == true);
		assert(isNumber("6+1") == false);
		assert(isNumber("6-1") == false);
		assert(isNumber("+.8") == true);
		assert(isNumber("46.e3") == true);
		assert(isNumber("1e.") == false);
		assert(isNumber(" 005047e+6") == true);
		assert(isNumber(" 005047e-6") == true);
		assert(isNumber("4e+") == false);
	}
};

class Solution_random_1
{
public:
	template<typename TFunc>
	int findBrokenBuild(int first, int second, TFunc didItGetWorse)
	{
		/*
		NOTE: This is inspired by a telephone interview question, context has been changed, but the strategy of a similar problem remains the same
		There were N*1000 builds made over the last year.  At some point, perf dropped. Find the build where it got worse.
		Since we don't have the power of paralleizing all the comparisons across an EC2 site AND each comparison is time consuming - we have to be frugal with our comparisons
		A binary search will sufice
		*/
		
		if (first >= second)
		{
			//assert(!"Huh?");
			return -1;
		}

		int middle = first + (second - first) / 2;
		
		if (didItGetWorse(first, middle))
		{
			// it's on the left
			if (middle - first == 1)
				return middle;
			return findBrokenBuild(first, middle, didItGetWorse);
		}
		else
		{
			// it's on the right
			if (second - middle == 1)
				return second;
			return findBrokenBuild(middle, second, didItGetWorse);
		}
	}

	Solution_random_1()
	{
		printf("Solution_random_1\n");
		// pretend that this lambda/data set is the code that deploys 2 builds, runs them, and compares the results
		std::vector<int> values;
		int count = 0;
		auto isLastWorseThanFirst = [&](int first, int last) {
			count++;
			assert(first >= 0 && first < (int)values.size());
			assert(last >= 0 && last < (int)values.size());
			if (values[last] > values[first])
				return true;
			return false;
		};

		int brokeBuild = -1;

		////////////////////////
		values = { 1 };
		for (int i = 0; i < 12; i++)
		{
			values.insert(values.begin(), 0);
			count = 0;
			brokeBuild = findBrokenBuild(0, (int)values.size() - 1, isLastWorseThanFirst);
			assert(brokeBuild == i + 1);
			printf("%d, %d\n", brokeBuild, count);
		}

		/////////////////////
		values = { 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
		count = 0;
		brokeBuild = findBrokenBuild(0, (int)values.size() - 1, isLastWorseThanFirst);
		assert(brokeBuild == 4);
		printf("%d, %d\n", brokeBuild, count);

		/////////////////////
		values = { 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
		count = 0;
		brokeBuild = findBrokenBuild(0, (int)values.size() - 1, isLastWorseThanFirst);
		assert(brokeBuild == 5);
		printf("%d, %d\n", brokeBuild, count);

		/////////////////////
		values = { 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
		count = 0;
		brokeBuild = findBrokenBuild(0, (int)values.size() - 1, isLastWorseThanFirst);
		assert(brokeBuild == 6);
		printf("%d, %d\n", brokeBuild, count);

		////////////////////
		values = { 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
		count = 0;
		brokeBuild = findBrokenBuild(0, (int)values.size() - 1, isLastWorseThanFirst);
		assert(brokeBuild == 7);
		printf("%d, %d\n", brokeBuild, count);

		while (values.size() > 7)
		{
			count = 0;
			brokeBuild = findBrokenBuild(0, (int)values.size() - 1, isLastWorseThanFirst);
			assert(brokeBuild == 7);
			printf("%d, %d\n", brokeBuild, count);
			values.resize(values.size() - 1);
		}

		for (int i = 0; i < 500; i++)
		{
			values.push_back(1);
		}

		//while (values.size() > 7)
		{
			count = 0;
			brokeBuild = findBrokenBuild(0, (int)values.size() - 1, isLastWorseThanFirst);
			assert(brokeBuild == 7);
			printf("%d, %d\n", brokeBuild, count);
			values.resize(values.size() - 1);
		}

		////////////////////
		values = { 0 };
		count = 0;
		brokeBuild = findBrokenBuild(0, (int)values.size() - 1, isLastWorseThanFirst);
		assert(brokeBuild == -1);
		printf("%d, %d\n", brokeBuild, count);
	}
};

class Solution_leet_code_229 {
public:
	std::vector<int> majorityElement(std::vector<int>& nums) 
	{
		// 28ms
		typedef std::map<int, int> ValueToCount;
		ValueToCount track;
		for (size_t index = 0; index < nums.size(); index++)
		{
			track[nums[index]]++;
		}

		std::vector<int> result;
		result.reserve(nums.size());

		size_t threshold = nums.size() / 3;

		for (ValueToCount::iterator it = track.begin(); it != track.end(); it++)
		{
			if (it->second > (int)threshold)
			{
				result.push_back(it->first);
			}
		}

		return result;
	}

	Solution_leet_code_229()
	{
		printf("Solution_leet_code_229\n");
		/*
		Given an integer array of size n, find all elements that appear more than [n/3] times. The algorithm should run in linear time and in O(1) space
		*/

		{
			std::vector<int> nums = { 1, 1, 1, 1, 2, 2, 3, 3 };
			std::vector<int> result = majorityElement(nums);
			assert(result.size() == 1);
			assert(result[0] == 1);
		}

		{
			std::vector<int> nums = { 2,2 };
			std::vector<int> result = majorityElement(nums);
			assert(result.size() == 1);
			assert(result[0] == 2);
		}
	}
};

class Solution_leet_code_151 {
public:
	// 8ms, Medium
	void reverseWords(std::string &s) {
		/*
		Note: The naive python way is
		s = " ".join(s.split(" ")[::-1])
		*/

		// Keep track of the positions of all the words/spaces in the source string
		struct Node {
			size_t pos;
			size_t len;
			int is_space;

			Node() 
			{ 
				reset(); 
			}
			void reset() 
			{
				pos = len = std::string::npos;
				is_space = -1;
			}
		};
		std::list<Node> nodes;

		Node node;
		for (size_t i = 0; i < s.length(); i++)
		{
			int is_space = (s[i] == ' ');
		
			if (node.is_space != is_space)
			{
				// change in state
				if (node.pos != std::string::npos)
				{
					node.len = i - node.pos;
					nodes.push_front(node);
					node.reset();
				}

				// start the next node
				node.pos = i;
				node.is_space = is_space;
			}
		}
		if (node.pos != std::string::npos && node.is_space == 0)
		{
			node.len = s.length() - node.pos;
			nodes.push_front(node);
		}

		std::string result;
		for (auto it = nodes.begin(); it != nodes.end(); it++)
		{
			if (it->is_space)
			{
				// no leading/trailing spaces
				if (it == nodes.begin() || it == --nodes.end() )
					continue;

				// spaces get shortened? seems odd, but whatever
				it->len = 1;
			}

			result.append(s.c_str() + it->pos, it->len);
		}

		// update the param with the new result
		s = result;
	}

	Solution_leet_code_151()
	{
		printf("Solution_leet_code_151\n");
		/*
		Given an input string, reverse the string word by word.

		For example,
		Given s = "the sky is blue",
		return "blue is sky the".
		*/

		{
			std::string value = "the sky is blue";
			std::string expected = "blue is sky the";
			reverseWords(value);
			assert(value == expected);
		}

		{
			std::string before = "";
			std::string after = "";
			reverseWords(before);
			assert(before == after);
		}

		{
			std::string before = "a";
			std::string after = "a";
			reverseWords(before);
			assert(before == after);
		}

		{
			std::string before = " ";
			std::string after = "";
			reverseWords(before);
			assert(before == after);
		}

		{
			std::string before = " 1";
			std::string after = "1";
			reverseWords(before);
			assert(before == after);
		}

		{
			std::string before = "1 ";
			std::string after = "1";
			reverseWords(before);
			assert(before == after);
		}
	}
};

class Solution_leet_code_75 {
	// Sort Colorts
	// Medium
	// 6ms
public:
	void sortColors(std::vector<int>& nums) 
	{
		// sort the array, descending
		// 2 options: use a premade sort or implement a sort
		// since I'd rather use something premade and I can't - just do a horrible bubble sort  O(n^2)

		for (size_t c = 0; c < (nums.size() - 1); c++)
		{
			for (size_t d = 0; d < nums.size() - c - 1; d++)
			{
				if (nums[d] > nums[d + 1])
				{
					int swap = nums[d];
					nums[d] = nums[d + 1];
					nums[d + 1] = swap;
				}
			}
		}
	}

	Solution_leet_code_75()
	{
		printf("Solution_leet_code_75\n");
		/*
		Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, with the colors in the order red, white and blue.

		Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

		Note:
		You are not suppose to use the library's sort function for this problem.
		*/

		std::vector<int> nums = { 1,0,2,0,1 };
		sortColors(nums);
	}
};

class Solution_random_2
{
public:
	bool IncrementLicensePlate(std::string &lastPlate)
	{
		for (auto it = lastPlate.rbegin(); it != lastPlate.rend(); it++)
		{
			switch (*it)
			{
			case 'Z':
				*it = 'A';
				break;

			case 'z':
				*it = 'a';
				break;

			case '9':
				*it = '0';
				break;

			default:
				if (!isdigit(*it) && !isalpha(*it))
				{
					//assert(!"unable to handle specialty symbol plates at this time");
					return false;
				}
				(*it)++;
				return true;
			}	
		}
		return false;
	}

	Solution_random_2()
	{
		printf("Solution_random_2\n");
		/*
		Given a vehicle license plate from the state DMV, get the next plate in the sequence.
		Don't take too long, those prisoners get anxious when they have nothing to do.
		Note: Plates have a fixed number of symbols and each position can be 0-9 or A-Z
		*/
		struct Test {
			std::string convert;
			std::string expected;
			bool shouldPass;
		};
		Test test_cases[] = {
			{ "1ABC1234", "1ABC1235", true  },
			{ "1",        "2",        true  },
			{ "9",        "9",        false },
			{ "A",        "B",        true  },
			{ "Z",        "Z",        false },
			{ "1ABC9999", "1ABD0000", true  },
			{ "1ZZZ9999", "2AAA0000", true  },
			{ "9ZZZ9999", "9ZZZ9999", false },
			{ "?ZZZ9999", "?ZZZ9999", false },
		};

		for (int i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); i++)
		{
			std::string temp = test_cases[i].convert;
			bool result = IncrementLicensePlate(temp);
			if (test_cases[i].shouldPass) 
			{
				assert(result);
				assert(temp == test_cases[i].expected);
			}
			else 
			{
				assert(!result);
			}
		}
	}
};

class Solution_leet_code_287 {
	// Find the Duplicate Number
	// Hard?
	// 36ms
public:
	int findDuplicate(std::vector<int>& nums) {
		std::set<int> dupecheck;
		for (auto value : nums)
		{
			// add it to the set & if it's already in there - we found the dupe
			auto result = dupecheck.insert(value);
			if (result.second == false)
			{
				return value;
			}
		}
		// Don't like this _at_ _all_
		// maybe change the result to a boolean and make the &value ref param? or return a pair<value,success>?
		return -1;
	}

	Solution_leet_code_287()
	{
		printf("Solution_leet_code_287\n");
		/*
		Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive), prove that at least one duplicate number must exist. Assume that there is only one duplicate number, find the duplicate one.

		Note:
		You must not modify the array (assume the array is read only).
		You must use only constant, O(1) extra space.
		Your runtime complexity should be less than O(n2).
		There is only one duplicate number in the array, but it could be repeated more than once.
		*/

		std::vector<int> nums = { 1,2,3,2,2,4 };
		assert( 2 == findDuplicate(nums));
	}
};

class Solution_random_3
{
public:
	bool FlipBit(uint8_t *bytes, size_t byte_len, int16_t offset)
	{
		if (!bytes || !byte_len || offset < 0)
		{
			//assert(!"Bad params");
			return false;
		}

		size_t byte_pos = offset / 8;
		if (byte_pos >= byte_len)
		{
			//assert(!"offset is out of bounds");
			return false;
		}

		int bitmask = 1 << (offset % 8);

		bytes[byte_pos] ^= bitmask;

		return true;
	}

	bool TestFlipBit(std::vector<uint8_t> &modify, int16_t offset, const std::vector<uint8_t> &expected_collection, bool expected_result)
	{
		bool result = FlipBit(&modify[0], modify.size(), offset);
		if (result != expected_result)
		{
			assert(!"That is not the result I was expecting");
			return false;
		}

		if (result)
		{
			if (modify.size() != expected_collection.size())
			{
				assert(!"Why did the size change?");
				return false;
			}

			for (size_t index = 0; index < modify.size(); index++)
			{
				if (modify[index] != expected_collection[index])
				{
					assert(!"That was not expected, the wrong bit was changed!");
					return false;
				}
			}
		}
		return result;
	}

	Solution_random_3()
	{
		printf("Solution_random_3\n");
		// Flip a bit at an offset in a byte array

		{
			std::vector<uint8_t> modify   = { 0x00 };
			std::vector<uint8_t> expected = { 0x01 };
			TestFlipBit(modify, 0, expected, true);
		}

		{
			std::vector<uint8_t> modify   = { 0x01 };
			std::vector<uint8_t> expected = { 0x00 };
			TestFlipBit(modify, 0, expected, true);
		}

		{
			std::vector<uint8_t> modify = { 0x01 };
			std::vector<uint8_t> expected = { 0x00 };
			TestFlipBit(modify, -1, expected, false);
		}

		{
			std::vector<uint8_t> modify = { 0x00, 0x00 };
			std::vector<uint8_t> expected = { 0x00, 0x01 };
			TestFlipBit(modify, 8, expected, true);
		}

		{
			std::vector<uint8_t> modify = { 0x00, 0x00 };
			std::vector<uint8_t> expected = { 0x00, 0x01 };
			TestFlipBit(modify, 16, expected, false);
		}
	}
};


class Solution_turtle_simulator
{
	/*
		Let's play with Turtle! (or anti-nascar slow tron light cycles without a tail wall)
		Each exposed explicit movement action will log the movement for undo
		Actions
			MoveForward
				Based upon the direction, will move the turtle forward
			TurnRight
				Changes direction 90deg to the right
			ExecuteSequence
				Allows for programmed sequences of commands
				Samples
					FFR   = Forward Forward TurnRight
					3F    = Forward Forward Forward
					3[FR] = Forward TurnRight Forward TurnRight Forward TurnRight
					2[RF2[F]2R]2[RR] can be nested
	*/
public:
	struct Point 
	{
		int32_t x;
		int32_t y;
		Point(int32_t x = 0, int32_t y = 0) 
			: x(x)
			, y(y)
		{}
		Point operator-(const Point &other) const
		{
			return Point(x - other.x, y - other.y);
		}
		Point operator+(const Point &other) const
		{
			return Point(x + other.x, y + other.y);
		}
		bool operator!=(const Point &other) const
		{
			return x != other.x || y != other.y;
		}
		bool operator==(const Point &other) const
		{
			return x == other.x && y == other.y;
		}
		Point& operator+=(const Point &other)
		{
			x += other.x;
			y += other.y;
			return *this;
		}
		Point& operator-=(const Point &other)
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}
	};

	enum class Rotation {
		North = 0,
		East  = 90,
		South = 180,
		West  = 270,
		FULL_CIRCLE = 360,
	};

	struct Direction
	{
		// Operators on an 'enum class' are not allowed, so we wrap it and put the operators here
		Rotation angle = Rotation::North;

		Rotation AddRotations(const Rotation &lhs, const Rotation &rhs) const
		{
			int value = ((int)lhs + (int)rhs) % (int)Rotation::FULL_CIRCLE;
			if (value < 0)
			{
				value += (int)Rotation::FULL_CIRCLE;
			}
			return (Rotation)value;
		}

		Direction(Rotation r = Rotation::North) : angle(r) {}
		Direction(const Direction &copy) : angle(copy.angle) {}

		Direction operator+(const Direction &other) const
		{
			return AddRotations(angle, other.angle);
		}

		Direction operator-(const Direction &other) const
		{
			return AddRotations(angle, (Rotation)-(int)other.angle);
		}

		bool operator!=(const Direction &other) const
		{
			return angle != other.angle;
		}

		bool operator==(const Direction &other) const
		{
			return angle == other.angle;
		}
	};

protected:
	Point     m_point;
	Direction m_direction;

	struct PositionState
	{
		Point     m_point;
		Direction m_direction;
		uint32_t  m_modifiedMask;

		enum Modified {
			MPOINT     = 0x01,
			MDIRECTION = 0x02,
		};

		PositionState()                             : m_modifiedMask(0) {}
		PositionState(const Point &pt, Direction d) : m_modifiedMask(MPOINT|MDIRECTION), m_point(pt), m_direction(d) {}

		bool HasModifiedMember(Modified mask) const 
		{ 
			return (m_modifiedMask & mask) == mask;
		}
	};
	std::list<PositionState> m_undoLog;

	// success, delta
	typedef std::pair<bool, PositionState> ResultPair;

	// helper for getting deltas to put in the m_undoLog
	PositionState internalCalcDelta(const Point &oldPoint, Direction oldDirection)
	{
		PositionState result;

		if (oldPoint != m_point)
		{
			result.m_modifiedMask |= PositionState::Modified::MPOINT;
			result.m_point = Point(oldPoint - m_point);
		}

		if (oldDirection != m_direction)
		{
			result.m_modifiedMask |= PositionState::Modified::MDIRECTION;
			result.m_direction = (oldDirection - m_direction);
		}

		return result;
	};

	// Does not log history
	ResultPair internalMoveForward()
	{
		Point oldPoint = m_point;
		bool success = true;

		switch (m_direction.angle)
		{
		case Rotation::North: m_point.x++; break;
		case Rotation::East:  m_point.y++; break;
		case Rotation::South: m_point.x--; break;
		case Rotation::West:  m_point.y--; break;
		default:
			assert(!"unsupported rotation");
			success = false;
		}

		// there was talk of limiting movement to the visible screen
		if (m_point.x < 0 || m_point.y < 0)
		{
			success = false;
		}

		return ResultPair(success, internalCalcDelta(oldPoint, m_direction));
	}

	// Does not log history
	ResultPair internalTurnRight()
	{
		Direction oldDirection = m_direction;
		m_direction = m_direction + Rotation::East;
		return ResultPair(true, internalCalcDelta(m_point, oldDirection));
	}

	// Does not log history
	ResultPair internalExecuteSequence(const std::string &commands)
	{
		// Sample command sequences
		// FFR   = Forward Forward TurnRight
		// 3F    = Forward Forward Forward
		// 3[FR] = Forward TurnRight Forward TurnRight Forward TurnRight
		// 2[RF2[F]2R]2[RR] can be nested

		// Save off our current state
		Point oldPoint = m_point;
		Direction oldDirection = m_direction;

		// iterate over the command string
		size_t count = 0;
		for (size_t index = 0; index < commands.size(); index++)
		{
			if (count > UINT16_MAX)
			{
				assert(!"Taking a wild stab in the dark & presuming that this is a bug");
				return ResultPair(false, internalCalcDelta(oldPoint, oldDirection));
			}

			// Leading base 10 number?
			if (commands[index] >= '0' && commands[index] <= '9')
			{
				// multidigit number?
				if (count > 0)
				{
					count *= 10;
				}

				count += commands[index] - '0';
				continue;
			}

			// Implicit One
			if (count < 1)
			{
				count = 1;
			}

			if (commands[index] == ']')
			{
				assert(!"We should never hit this");
				return ResultPair(false, internalCalcDelta(oldPoint, oldDirection));
			}

			if (commands[index] == '[')
			{
				// we need to run this next block 'count' times
				// scan ahead to find end of this block
				int depth = 1;
				size_t search = index + 1;
				while (depth && search < commands.size())
				{
					if (commands[search] == '[')
					{
						depth++;
					}
					else if (commands[search] == ']')
					{
						depth--;
					}
					search++;
				}
				if (depth)
				{
					assert(!"mismatched braces!");
					return ResultPair(false, internalCalcDelta(oldPoint, oldDirection));
				}

				// get the substring [between the braces] and execute it recursively
				std::string substring(commands.c_str() + 1 + index, search - index - 2);
				while (count)
				{
					count--;
					internalExecuteSequence(substring);
				}

				// set index to the last brace, to be skipped over in the outer for-loop
				index = search - 1;
				continue;
			}

			// Finaly do the work of moving the turtle about
			while (count)
			{
				count--;

				switch (commands[index])
				{
				case 'F':
					internalMoveForward();
					break;

				case 'R':
					internalTurnRight();
					break;

				default:
					assert(!"that was unexpected");
					return ResultPair(false, internalCalcDelta(oldPoint, oldDirection));
				}
			}
		}

		return ResultPair(true, internalCalcDelta(oldPoint, oldDirection));
	}

public:

	Point CurrentLocation() const
	{
		return m_point;
	}

	Rotation CurrentRotation() const
	{
		return m_direction.angle;
	}

	//
	// Turtles are slow, they move 1 position at a time
	//
	void MoveForward()
	{
		// Make the change and log it
		PositionState rollback(m_point, m_direction);
		ResultPair result = internalMoveForward();
		if (result.first)
		{
			m_undoLog.push_front(result.second);
		}
		else
		{
			// invalid movement, put it back
			m_point = rollback.m_point;
			m_direction = rollback.m_direction;
		}
	}

	//
	// Rotate 90deg to the right
	//
	void TurnRight()
	{
		// Make the change and log it
		ResultPair result = internalTurnRight();
		m_undoLog.push_front(result.second);
	}

	//
	// Provide a command string instead of making manual turn and move calls yourself
	//
	void ExecuteSequence(const std::string &commands)
	{
		PositionState rollback(m_point, m_direction);
		ResultPair result = internalExecuteSequence(commands);
		if (result.first)
		{
			m_undoLog.push_front(result.second);
		}
		else
		{
			// invalid movement, put it back
			m_point = rollback.m_point;
			m_direction = rollback.m_direction;
		}
	}

	bool IsUndoEmpty() const
	{
		return m_undoLog.empty();
	}

	void UndoAll()
	{
		while (!IsUndoEmpty())
		{
			Undo();
		}
	}

	void Reset()
	{
		m_direction.angle = Rotation::North;
		m_point.x = m_point.y = 0;
		m_undoLog.clear();
	}

	//
	// Pop the stack of TurnRight, MoveForward, and ExecuteSequence calls
	//
	void Undo()
	{
		auto it = m_undoLog.begin();
		if (it == m_undoLog.end())
		{
			// nothing to undo
			return;
		}

		// pop the delta off the history
		PositionState change = *it;
		m_undoLog.erase(it);

		// apply the delta
		if (change.HasModifiedMember(PositionState::Modified::MDIRECTION))
		{
			m_direction = m_direction + change.m_direction;
		}

		if (change.HasModifiedMember(PositionState::Modified::MPOINT))
		{
			m_point += change.m_point;
		}
	}

	Solution_turtle_simulator()
	{
		printf("Solution_turtle_simulator\n");

		Reset();

		auto VerifyUndoAll = [&]() {
			UndoAll();
			assert(CurrentRotation() == Rotation::North);
			assert(CurrentLocation() == Point(0, 0));
		};

		assert(CurrentRotation() == Rotation::North);
		assert(CurrentLocation() == Point(0, 0));
		MoveForward();
		assert(CurrentRotation() == Rotation::North);
		assert(CurrentLocation() == Point(1, 0));
		TurnRight();
		assert(CurrentRotation() == Rotation::East);
		TurnRight();
		assert(CurrentRotation() == Rotation::South);
		TurnRight();
		assert(CurrentRotation() == Rotation::West);
		TurnRight();
		assert(CurrentRotation() == Rotation::North);
		Undo();
		assert(CurrentRotation() == Rotation::West);
		TurnRight();
		assert(CurrentRotation() == Rotation::North);

		UndoAll();
		assert(CurrentRotation() == Rotation::North);
		assert(CurrentLocation() == Point(0, 0));

		// command sequences
		ExecuteSequence("F");
		assert(CurrentRotation() == Rotation::North);
		assert(CurrentLocation() == Point(1, 0));

		VerifyUndoAll();
		ExecuteSequence("FF");
		assert(CurrentRotation() == Rotation::North);
		assert(CurrentLocation() == Point(2, 0));

		VerifyUndoAll();
		ExecuteSequence("2F");
		assert(CurrentRotation() == Rotation::North);
		assert(CurrentLocation() == Point(2, 0));

		VerifyUndoAll();
		ExecuteSequence("R");
		assert(CurrentRotation() == Rotation::East);
		assert(CurrentLocation() == Point(0, 0));

		VerifyUndoAll();
		ExecuteSequence("RR");
		assert(CurrentRotation() == Rotation::South);
		assert(CurrentLocation() == Point(0, 0));

		VerifyUndoAll();
		ExecuteSequence("2R");
		assert(CurrentRotation() == Rotation::South);
		assert(CurrentLocation() == Point(0, 0));

		VerifyUndoAll();
		ExecuteSequence("4R");
		assert(CurrentRotation() == Rotation::North);
		assert(CurrentLocation() == Point(0, 0));

		VerifyUndoAll();
		ExecuteSequence("1F1RF");
		assert(CurrentRotation() == Rotation::East);
		assert(CurrentLocation() == Point(1, 1));

		VerifyUndoAll();
		ExecuteSequence("3[F]");
		assert(CurrentRotation() == Rotation::North);
		assert(CurrentLocation() == Point(3, 0));

		VerifyUndoAll();
		ExecuteSequence("3[F]2R");
		assert(CurrentRotation() == Rotation::South);
		assert(CurrentLocation() == Point(3, 0));

		VerifyUndoAll();
		ExecuteSequence("3[F]1R10[F]5F");
		assert(CurrentRotation() == Rotation::East);
		assert(CurrentLocation() == Point(3, 15));

		// Put it all back
		VerifyUndoAll();
	}
};

class Solution_BreakingBad_name_finder
{
public:
	struct ElementDetail {
		int16_t      number;
		double       weight;
		std::string  name;
		std::string  symbol;
	} m_elementDetails[119] = {
		{ 0,     0.0000, "",               ""    },  // skip for sanity. Rest pulled from http://www.science.co.il/PTelements.asp & https://en.wikipedia.org/wiki/List_of_elements
		{ 1,     1.0079, "Hydrogen",       "H"   },
		{ 2,     4.0026, "Helium",         "He"  },
		{ 3,     6.9410, "Lithium",  	   "Li"  },
		{ 4,     9.0122, "Beryllium",	   "Be"  },
		{ 5,    10.8110, "Boron",   	   "B"   },
		{ 6,    12.0107, "Carbon",  	   "C"   },
		{ 7,    14.0067, "Nitrogen",	   "N"   },
		{ 8,    15.9994, "Oxygen",  	   "O"   },
		{ 9,    18.9984, "Fluorine",	   "F"   },
		{ 10,   20.1797, "Neon",           "Ne"  },
		{ 11,   22.9897, "Sodium",  	   "Na"  },
		{ 12,   24.3050, "Magnesium",	   "Mg"  },
		{ 13,   26.9815, "Aluminum",	   "Al"  },
		{ 14,   28.0855, "Silicon",  	   "Si"  },
		{ 15,   30.9738, "Phosphorus",	   "P"   },
		{ 16,   32.0650, "Sulfur",  	   "S"   },
		{ 17,   35.4530, "Chlorine",	   "Cl"  },
		{ 18,   39.9480, "Argon",    	   "Ar"  },
		{ 19,   39.0983, "Potassium",	   "K"   },
		{ 20,   40.0780, "Calcium",  	   "Ca"  },
		{ 21,   44.9559, "Scandium",	   "Sc"  },
		{ 22,   47.8670, "Titanium",	   "Ti"  },
		{ 23,   50.9415, "Vanadium",	   "V"   },
		{ 24,   51.9961, "Chromium",	   "Cr"  },
		{ 25,   54.9380, "Manganese",	   "Mn"  },
		{ 26,   55.8450, "Iron",    	   "Fe"  },
		{ 27,   58.9332, "Cobalt",   	   "Co"  },
		{ 28,   58.6934, "Nickel",	       "Ni"  },
		{ 29,   63.5460, "Copper",	       "Cu"  },
		{ 30,   65.3900, "Zinc",	       "Zn"  },
		{ 31,   69.7230, "Gallium",	       "Ga"  },
		{ 32,   72.6400, "Germanium",	   "Ge"  },
		{ 33,   74.9216, "Arsenic",  	   "As"  },
		{ 34,   78.9600, "Selenium",	   "Se"  },
		{ 35,   79.9040, "Bromine",  	   "Br"  },
		{ 36,   83.8000, "Krypton",  	   "Kr"  },
		{ 37,   85.4678, "Rubidium",	   "Rb"  },
		{ 38,   87.6200, "Strontium",	   "Sr"  },
		{ 39,   88.9059, "Yttrium", 	   "Y"   },
		{ 40,   91.2240, "Zirconium",	   "Zr"  },
		{ 41,   92.9064, "Niobium",  	   "Nb"  },
		{ 42,   95.9400, "Molybdenum",	   "Mo"  },
		{ 43,   98.0000, "Technetium",	   "Tc"  },
		{ 44,  101.0700, "Ruthenium",	   "Ru"  },
		{ 45,  102.9055, "Rhodium", 	   "Rh"  },
		{ 46,  106.4200, "Palladium",	   "Pd"  },
		{ 47,  107.8682, "Silver",  	   "Ag"  },
		{ 48,  112.4110, "Cadmium",  	   "Cd"  },
		{ 49,  114.8180, "Indium",   	   "In"  },
		{ 50,  118.7100, "Tin",     	   "Sn"  },
		{ 51,  121.7600, "Antimony",	   "Sb"  },
		{ 52,  127.6000, "Tellurium",	   "Te"  },
		{ 53,  126.9045, "Iodine",     	   "I"   },
		{ 54,  131.2930, "Xenon", 	       "Xe"  },
		{ 55,  132.9055, "Cesium",     	   "Cs"  },
		{ 56,  137.3270, "Barium",     	   "Ba"  },
		{ 57,  138.9055, "Lanthanum",	   "La"  },
		{ 58,  140.1160, "Cerium",   	   "Ce"  },
		{ 59,  140.9077, "Praseodymium",   "Pr"  },
		{ 60,  144.2400, "Neodymium",	   "Nd"  },
		{ 61,  145.0000, "Promethium",	   "Pm"  },
		{ 62,  150.3600, "Samarium",	   "Sm"  },
		{ 63,  151.9640, "Europium",	   "Eu"  },
		{ 64,  157.2500, "Gadolinium",	   "Gd"  },
		{ 65,  158.9253, "Terbium",  	   "Tb"  },
		{ 66,  162.5000, "Dysprosium",	   "Dy"  },
		{ 67,  164.9303, "Holmium",        "Ho"  },
		{ 68,  167.2590, "Erbium",	       "Er"  },
		{ 69,  168.9342, "Thulium",  	   "Tm"  },
		{ 70,  173.0400, "Ytterbium",	   "Yb"  },
		{ 71,  174.9670, "Lutetium",	   "Lu"  },
		{ 72,  178.4900, "Hafnium",  	   "Hf"  },
		{ 73,  180.9479, "Tantalum",	   "Ta"  },
		{ 74,  183.8400, "Tungsten",	   "W "  },
		{ 75,  186.2070, "Rhenium",  	   "Re"  },
		{ 76,  190.2300, "Osmium",  	   "Os"  },
		{ 77,  192.2170, "Iridium",  	   "Ir"  },
		{ 78,  195.0780, "Platinum",	   "Pt"  },
		{ 79,  196.9665, "Gold",    	   "Au"  },
		{ 80,  200.5900, "Mercury",  	   "Hg"  },
		{ 81,  204.3833, "Thallium",	   "Tl"  },
		{ 82,  207.2000, "Lead",    	   "Pb"  },
		{ 83,  208.9804, "Bismuth",  	   "Bi"  },
		{ 84,  209.0000, "Polonium",	   "Po"  },
		{ 85,  210.0000, "Astatine",	   "At"  },
		{ 86,  222.0000, "Radon",   	   "Rn"  },
		{ 87,  223.0000, "Francium",	   "Fr"  },
		{ 88,  226.0000, "Radium",   	   "Ra"  },
		{ 89,  227.0000, "Actinium",	   "Ac"  },
		{ 90,  232.0381, "Thorium",  	   "Th"  },
		{ 91,  231.0359, "Protactinium",   "Pa"  },
		{ 92,  238.0289, "Uranium", 	   "U2"  },
		{ 93,  237.0000, "Neptunium",	   "Np"  },
		{ 94,  244.0000, "Plutonium",	   "Pu"  },
		{ 95,  243.0000, "Americium",	   "Am"  },
		{ 96,  247.0000, "Curium",   	   "Cm"  },
		{ 97,  247.0000, "Berkelium",	   "Bk"  },
		{ 98,  251.0000, "Californium",	   "Cf"  },
		{ 99,  252.0000, "Einsteinium",	   "Es"  },
		{ 100, 257.0000, "Fermium",  	   "Fm"  },
		{ 101, 258.0000, "Mendelevium",	   "Md"  },
		{ 102, 259.0000, "Nobelium",       "No"  },
		{ 103, 262.0000, "Lawrencium",     "Lr"  },
		{ 104, 261.0000, "Rutherfordium",  "Rf"  },
		{ 105, 262.0000, "Dubnium",        "Db"  },
		{ 106, 266.0000, "Seaborgium",     "Sg"  },
		{ 107, 264.0000, "Bohrium",        "Bh"  },
		{ 108, 269.0000, "Hassium",        "Hs"  },
		{ 109, 278.0000, "Meitnerium",     "Mt"  },
		{ 110, 281.0000, "Darmstadtium",   "Ds"  },
		{ 111, 282.0000, "Roentgenium",    "Rg"  },
		{ 112, 285.0000, "Copernicium",    "Cn"  },
		{ 113, 286.0000, "Ununtrium",      "Uut" },
		{ 114, 289.0000, "Flerovium",      "Fl"  },
		{ 115, 289.0000, "Ununpentium",    "Uup" },
		{ 116, 293.0000, "Livermorium",    "Lv"  },
		{ 117, 294.0000, "Ununseptium",    "Uus" },
		{ 118, 294.0000, "Ununoctium",     "Uuo" },
	};

	std::map<std::string, uint16_t> m_symbolToNumber;
	std::set<size_t> m_symbolLengths;

	void MakeLower(std::string &value)
	{
#if 0
		// NOTE: This is Unicode HOSTILE and will break
		std::transform(value.begin(), value.end(), value.begin(), ::tolower);
#else
		// There has to be a cleaner way to do this the "right way" :-/
		auto & f = std::use_facet<std::ctype<std::string::traits_type::char_type>>(std::locale());
		f.tolower(&value[0], &value[0] + value.size());
#endif
	}

	void Init()
	{
		// load the map of symbol to number from the loading array
		for (auto &element : m_elementDetails)
		{
			if (element.symbol.empty())
				continue;
			std::string lower_case = element.symbol;
			MakeLower(lower_case);
			assert(m_symbolToNumber.find(lower_case) == m_symbolToNumber.end() && "There is a duplicate in the seed data");
			m_symbolToNumber[lower_case] = element.number;
			m_symbolLengths.insert(lower_case.size());
		}
	}

	//
	// Strict is the original implementation that requires a string to be made completely of elements
	//

	typedef std::list<int16_t>         ElementSequence;
	typedef std::list<ElementSequence> ElementSequenceResults;

	/*
		fill 'results' with all the atomicNumbers (for atomicSymbols) that comprise 'source'
		i.e. "bacon" will create 3 seperate variations for 'results'
		'history' is a local stack of partial atomicNumbers that we carry along with each recursive call.
	*/
	void ElementTokenizerStrict(const std::string &source, ElementSequenceResults &results, ElementSequence &history)
	{
		for (auto symbol_length : m_symbolLengths)
		{
			// Symbol to look for
			std::string searchSymbol(source.c_str(), symbol_length);
			if (searchSymbol.size() < symbol_length || searchSymbol.empty())
				continue;

			// Search for it
			auto itFinder = m_symbolToNumber.find(searchSymbol);
			if (itFinder == m_symbolToNumber.end())
				continue;

			// add what we got
			history.push_back(itFinder->second);

			// Get the rest of the string for a recursive call
			std::string remainder(source.c_str() + symbol_length);
			if (remainder.empty())
			{
				// Nothing left. We made it to the end of the source string
				results.push_back(history);
			}
			else
			{
				// look deeper
				ElementTokenizerStrict(remainder, results, history);
			}

			// stop tracking it
			history.pop_back();
		}
	}


	//
	// More flexible implementation that allows for partial matches that would normally be discarded immediatly.
	// These partial matches INCREASE EXECUTION TIME CONSIDERABLY.
	// DO NOT USE IN PRODUCTION!
	// Why? ElementTokenizerStrict ignores bad paths. This one can do ALL the paths/combos.  O(lastTimeLord)
	//
	// Word                  Partial  Results  Iterations  Profiler
	// beer                  no       1        3                4ms
	// jason                 true     11       94              20ms
	// bacon                 no       3        8                9ms
	// banana                no       1        6                7ms
	// hell                  true     2        31              20ms
	// breaking              true     49       1606           397ms
	// breaking              no       0        4                2ms
	// bad                   true     2        10              11ms
	// bad                   no       0        3                6ms
	// America               no       1        5                6ms        
	// America               true     23       514            107ms
	// Internationalization  no       0        24               6ms
	// Internationalization  true     n/a      n/a          ! manually killed test at 15 minutes !
	// abcdefgh              true     23       2551           621ms
	// abcdefghi             true     47       7654          2107ms
	// abcdefghij            true     47       22963         6351ms
	//

	// Instead of a simple list of atomicNumbers, we need to track the char that didn't match
	struct Token 
	{
		int16_t atomicNumber;
		char    noMatchChar;
		Token() 
			: atomicNumber(0)
			, noMatchChar(0) 
		{}
		bool operator<(const Token & other) const
		{
			if (atomicNumber < other.atomicNumber)
				return true;
			else if (atomicNumber == other.atomicNumber && noMatchChar < other.noMatchChar)
				return true;
			return false;
		}
	};

	typedef std::list<Token>        TokenSequence;
	typedef std::set<TokenSequence> TokenSequenceResults;

	// profiling helper: returns the number of recursive ElementTokenizer calls made
	size_t ElementTokenizerExperimental(const std::string &source, TokenSequenceResults &results, TokenSequence &history, bool allow_partial)
	{
		size_t call_count = 1;

		if (allow_partial && source.length() >= 10)
		{
			assert(!"don't be so inefficent! Long words are not worth the heat death of the universe");
			return call_count;
		}

		for (auto symbol_length : m_symbolLengths)
		{
			// Symbol to look for
			std::string searchSymbol(source.c_str(), symbol_length);
			if (searchSymbol.size() < symbol_length || searchSymbol.empty())
				continue;

			// Search for it
			auto itFinder = m_symbolToNumber.find(searchSymbol);

			// track it
			Token token;
			if (itFinder != m_symbolToNumber.end())
			{
				token.atomicNumber = itFinder->second;
			}
			else if (allow_partial)
			{
				symbol_length = 1;
				token.noMatchChar = searchSymbol[0];
			}
			else
			{
				continue;
			}

			// add what we got
			history.push_back(token);

			// Get the rest of the string for a recursive call
			std::string remainder(source.c_str() + symbol_length);
			if (remainder.empty())
			{
				// Nothing left. We made it to the end of the source string
				results.insert(history);
			}
			else
			{
				// look deeper
				call_count += ElementTokenizerExperimental(remainder, results, history, allow_partial);
			}

			// stop tracking it
			history.pop_back();
		}

		return call_count;
	}

	// returns the number of ElementTokenizer calls made
	size_t MakeElemental(std::string source_word, std::list<std::string> &result_list, bool allow_partials)
	{
		size_t result_call_count = 0;
		MakeLower(source_word);
		if (source_word.empty())
			return result_call_count;

		// Tokenize it!
		TokenSequenceResults sequenceResults;
		TokenSequence recentHistory;
		result_call_count = ElementTokenizerExperimental(source_word, sequenceResults, recentHistory, allow_partials);
		
		assert(recentHistory.empty());

		// Build out the human readable strings!
		for (auto &sequence : sequenceResults)
		{
			std::string elemental_word;
			size_t element_count = 0;

			for (auto &token : sequence)
			{
				if (token.noMatchChar)
				{
					elemental_word.append(1, token.noMatchChar);
				}
				else if(token.atomicNumber)
				{
					element_count++;

					if (token.atomicNumber < 0 || token.atomicNumber >= sizeof(m_elementDetails) / sizeof(m_elementDetails[0]))
					{
						assert(!"Bad atomicNumber?");
						return result_call_count;
					}

					// Pretty print partials by wrapping [symbols] to distinguish them from non-matches
					if (allow_partials)
					{
						elemental_word.append("[");
					}

					elemental_word.append(m_elementDetails[token.atomicNumber].symbol);

					if (allow_partials)
					{
						elemental_word.append("]");
					}
				}
				else
				{
					assert(!"that was unexpected");
				}
			}

			// only allow results that have at least 1 element in them
			if (element_count)
			{
				result_list.push_back(elemental_word);
			}
		}
		return result_call_count;
	}

	Solution_BreakingBad_name_finder()
	{
		/*
			A few years back it was trendy to make title screens with select sub groupings of letters to be replaced with Peiodic Table element names
			There were t-shirts that read "[Be][Er]" (for Beryllium(4) and Erbium(68)) that those that didn't take chem101 would read as "Beer"

			Let's find all the plausable strings that can be made from element names
			"Beer"   -> "[Be][Er]"
			"Banana" -> "[Ba][Na][Na]"
			"Hell"   -> "[He]ll"       = PARTIAL & possibly invalid
			"Bacon"  -> "[Ba][Co][N]", [B][Ac][O][N], [Ba][C][O][N] = MULTIPLE
		*/
		printf("Solution_BreakingBad_name_finder\n");
		Init();

		auto TestFunc = [&](const char *name, bool partials) {
			std::list<std::string> name_list;
			size_t count = MakeElemental(name, name_list, partials);
			printf("Element conversion of [%s] yields [%zd] strings, partials[%s], iterations[%zd]\n", name, name_list.size(), partials ? "YES" : "NO", count);
			for (auto &value : name_list)
			{
				printf("\t%s\n", value.c_str());
			}
		};

		TestFunc("beer",     false);
		TestFunc("Jason",    true);
		TestFunc("bacon",    false);
		TestFunc("banana",   false);
		TestFunc("hell",     true);
		TestFunc("Breaking", true);
		TestFunc("Bad",      true);
		TestFunc("Breaking", false);
		TestFunc("Bad",      false);
		TestFunc("America",  false);
		TestFunc("America",  true);
		//TestFunc("Internationalization",  false); // will assert for string being too long, 6ms
		//TestFunc("Internationalization",  true);  // will assert for string being too long, >15minutes
		TestFunc("abcdefgh", true);
		//TestFunc("abcdefghi", true);   // 2 seconds!
		//TestFunc("abcdefghij", true);  // 6 seconds!
	}
};

void MyChallenges_UnitTest()
{
	printf("\nTESTING MyChallenges - BEGIN\n");
	Solution_leet_code_242 _solution_leet_code_242;
	Solution_leet_code_27  _solution_leet_code_27;
	Solution_leet_code_283 _solution_leet_code_283;
	Solution_leet_code_258 _solution_leet_code_258;
	Solution_leet_code_65  _solution_leet_code_65;
	Solution_random_1      _solution_random_1;
	Solution_leet_code_229 _solution_leet_code_229;
	Solution_leet_code_151 _solution_leet_code_151;
	Solution_leet_code_75  _solution_leet_code_75;
	Solution_random_2      _Solution_random_2;
	Solution_leet_code_287 _Solution_leet_code_287;
	Solution_random_3      _Solution_random_3;
	Solution_turtle_simulator _Solution_turtle_simulator;
	Solution_BreakingBad_name_finder _Solution_BreakingBad_name_finder;
	printf("\nTESTING MyChallenges - END\n");
}