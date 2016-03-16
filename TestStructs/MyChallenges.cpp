#include "stdafx.h"
#include "MyChallenges.h"
#include <assert.h>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <list>

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
		
		for (int i = 0; i < s_length; i++)
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
			assert(first >= 0 && first < values.size());
			assert(last >= 0 && last < values.size());
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
			if (it->second > threshold)
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

		for (int c = 0; c < (nums.size() - 1); c++)
		{
			for (int d = 0; d < nums.size() - c - 1; d++)
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

void MyChallenges_UnitTest()
{
	printf("\nTESTING MyChallenges\n");
	Solution_leet_code_242 _solution_leet_code_242;
	Solution_leet_code_27  _solution_leet_code_27;
	Solution_leet_code_283 _solution_leet_code_283;
	Solution_leet_code_258 _solution_leet_code_258;
	Solution_leet_code_65  _solution_leet_code_65;
	Solution_random_1      _solution_random_1;
	Solution_leet_code_229 _solution_leet_code_229;
	Solution_leet_code_151 _solution_leet_code_151;
	Solution_leet_code_75  _solution_leet_code_75;
}