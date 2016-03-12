#include "stdafx.h"

#include "MyMathExpressionParser.h"
#include <assert.h>
#include <stdint.h>
#include <assert.h>
#include <string>

// inspired by https://www.strchr.com/expression_evaluator

class MyExpressionParser
{
public:
	enum ParseResultCode
	{
		SUCCESS = 0,
		NO_OPEN_PARENTHESES,
		NO_CLOSE_PARENTHESES,
		DIV_ZERO,
	};

#define RETURN_FAILURE(code, error_string)    { m_code = code; m_error_start = error_string; return NAN; }
#define FAIL_CHECK	                          if (SUCCESS != m_code) { return NAN; }

	double m_result;
	ParseResultCode m_code;
	size_t m_parenthesis;
	std::string m_original;
	std::string m_error_start;

	MyExpressionParser()
	{
		init();
	}

protected:

	void init()
	{
		m_result = 0.0;
		m_code = SUCCESS;
		m_parenthesis = 0;
		m_original.clear();
		m_error_start.clear();
	}

	void skip_spaces(char *& expression)
	{
		while (*expression == ' ')
		{
			expression++;
		}
	}

	double parse_atom(char *& expression)
	{
		FAIL_CHECK;

		skip_spaces(expression);

		bool negative = false;
		if (*expression == '-')
		{
			negative = true;
			expression++;
		}
		if (*expression == '+')
		{
			expression++;
		}

		// PAR-EN-THESIS
		if (*expression == ')' && !m_parenthesis)
		{
			RETURN_FAILURE(NO_OPEN_PARENTHESES, expression);
		}
		if (*expression == '(')
		{
			expression++;
			m_parenthesis++;
			double result = parse_commands(expression);
			if (*expression != ')')
			{
				RETURN_FAILURE(NO_CLOSE_PARENTHESES, expression);
			}
			expression++;
			m_parenthesis--;
			return negative ? -result : result;
		}

		// convert the string to a double, gives point in the string where the number ends
		char *end_ptr = nullptr;
		double res = strtod(expression, &end_ptr);
		expression = end_ptr;
		return negative ? -res : res;
	}

	double parse_factors(char *& expression)
	{
		FAIL_CHECK;
		double num1 = parse_atom(expression);
		FAIL_CHECK;
		for (;;)
		{
			skip_spaces(expression);
			char op = *expression;
			char *position = expression;
			if (op != '/' && op != '*')
			{
				// nothing for us, pass it back
				return num1;
			}
			expression++;
			double num2 = parse_atom(expression);
			FAIL_CHECK;
			if (op == '/')
			{
				if (num2 == 0)
				{
					RETURN_FAILURE(DIV_ZERO, expression);
				}
				num1 /= num2;
			}
			else
			{
				num1 *= num2;
			}
		}
	}

	double parse_commands(char *&expression)
	{
		FAIL_CHECK;
		double num1 = parse_factors(expression);
		FAIL_CHECK;
		for (;;)
		{
			skip_spaces(expression);
			char op = *expression;
			if (op != '-' && op != '+')
			{
				return num1;
			}
			expression++;
			double num2 = parse_factors(expression);
			FAIL_CHECK;
			if (op == '-')
			{
				num1 -= num2;
			}
			else
			{
				num1 += num2;
			}
		}
	}

public:
	double evaluate(std::string expression)
	{
		init();

		m_original = expression;
		char *source = (char*)m_original.c_str();
		return parse_commands(source);
	}
};

double MyMathExpressionEvaluator(std::string expression)
{
	MyExpressionParser parser;
	return parser.evaluate(expression);
}

// Floats are annoying to compare against, so turn them into int's 
// 1.200000000000001 can become 120 if all you care about is 2 digits of precision
int64_t float_to_big_int(double f, size_t precision)
{
	if (precision == 0)
	{
		assert(!"That wasn't a good param, needs to be 1 or greater");
		return 0;
	}
	size_t factor = 1;
	for (size_t i = 0; i < precision; i++)
	{
		factor *= 10;
	}

	return int64_t(f * factor);
}

void MyMathExpressionEvaluator_UnitTest()
{
	printf("\nTESTING MyMathExpressionEvaluator\n");

	double m1 = MyMathExpressionEvaluator("1+2");
	double m2 = MyMathExpressionEvaluator("1-2");
	double m3 = MyMathExpressionEvaluator("2*3");
	double m4 = MyMathExpressionEvaluator("2/3");
	double m5 = MyMathExpressionEvaluator("1+2*3-4/6");
	double m6 = MyMathExpressionEvaluator("1.5+2+3.4*(25-4)/2-8");

	struct data_point {
		const char * expression;
		double expected_value;
		size_t precision;
		MyExpressionParser::ParseResultCode expected_result;
	};

	data_point test_data[] = {
		{ ")",                                   0.0f,        1, MyExpressionParser::ParseResultCode::NO_OPEN_PARENTHESES },
		{ "((1+2)/2",                            0.0f,        1, MyExpressionParser::ParseResultCode::NO_CLOSE_PARENTHESES },
		{ "1/0",                                 0.0f,        1, MyExpressionParser::ParseResultCode::DIV_ZERO },

		{ "-((6+4))* -(2+2) - -1",               41.0f,       1, MyExpressionParser::ParseResultCode::SUCCESS },
		{ "6/5-4-45+3.08",                      -44.72f,      2, MyExpressionParser::ParseResultCode::SUCCESS },
		{ "0.34+ -34/45-2",                     -2.41556f,    4, MyExpressionParser::ParseResultCode::SUCCESS },
		{ "(0.03)*73-2",                         0.19f,       2, MyExpressionParser::ParseResultCode::SUCCESS },
		{ "(20-23 + -5 * (12 / (34 + 3) - 3))",  10.3784f,    4, MyExpressionParser::ParseResultCode::SUCCESS },
		{ "-25 + 4 * -(32 - 45 / 5 - -6)",      -141.0f,      1, MyExpressionParser::ParseResultCode::SUCCESS },
		{ "0.0003101 - 34 * (4 + 5) / 23",      -13.3040f,    2, MyExpressionParser::ParseResultCode::SUCCESS },
		{ "1 + ((1 + 1) + 3) + 4 * 5 / 6 - 7",   2.33333f,    2, MyExpressionParser::ParseResultCode::SUCCESS },
		{ "9 / 8/7 /6/5/4  /  3 /  2/1",         0.00022321f, 7, MyExpressionParser::ParseResultCode::SUCCESS },
		{ "-( -(-( -(2+3*4)+2 )-1)+ 0)",         11.0f,       1, MyExpressionParser::ParseResultCode::SUCCESS },		
	};

	MyExpressionParser parser;
	for (auto data : test_data)
	{
		double result = parser.evaluate(data.expression);
		
		assert(data.expected_result == parser.m_code);

		switch (data.expected_result)
		{
		case MyExpressionParser::ParseResultCode::SUCCESS:
			{
				int64_t l = float_to_big_int(result, data.precision);
				int64_t r = float_to_big_int(data.expected_value, data.precision);
				assert(l == r);
			}
			break;

		case MyExpressionParser::ParseResultCode::NO_CLOSE_PARENTHESES:
			break;

		case MyExpressionParser::ParseResultCode::NO_OPEN_PARENTHESES:
			break;

		case MyExpressionParser::ParseResultCode::DIV_ZERO:
			break;

		default:
			assert(!"missed a case");
		}
		
	}
}

