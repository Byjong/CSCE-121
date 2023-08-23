#include <iostream>
#include <string>
#include "./string_calculator.h"
#include "tests.h"

using std::cin, std::cout, std::endl, std::string, std::to_string;

namespace {
	bool test_passed = true;
}
/*
void test_deci_digit(unsigned int num, char predict){
	char actual = decimal_to_digit(num);
	cout << "Input: " << num << endl;
	cout << "Predict: " << predict << endl;
	cout << "Actual: " << actual << endl;
	assert(predict == actual);
	cout << endl;
}

/*	
void test_digit_deci(char num, int predict){
	int actual = digit_to_decimal(num);
	cout << "Input: " << num << endl;
	cout << "Predict: " << predict << endl;
	cout << "Actual: " << actual << endl;
	assert(predict == actual);
	cout << endl;
}

/*
void test_trim(string num, string predict){
	string actual = trim_leading_zeros(num);
	cout << "Input: " << num << endl;
	cout << "Predict: " << predict << endl;
	cout << "Actual: " << actual << endl;
	assert(predict == actual);
	cout << endl;
}

/*
void test_add(string num1, string num2, string predict){
	string actual = add(num1, num2);
	cout << "Input: " << num1 << " + " << num2 << endl;
	cout << "Predict: " << predict << endl;
	cout << "Actual: " << actual << endl;
	assert(predict == actual);
	cout << endl;
}

/*
void test_mult(stirng num1, string num2, string predict){
	string actual = multiply(num1, num2);
	cout << "Input: " << num1 << " * " << num2 << endl;
	cout << "Predict: " << predict << endl;
	cout << "Actual: " << actual << endl;
	assert(predict == actual);
	cout << endl;
}
*/

bool test_sub(){
	string actual = string();
	string expected = string();
	for (int i = -15; i < 25; ++i) {
		for (int j = -15; j < 25; ++j) {
			actual = subtract(to_string(i), to_string(j));
			expected = to_string(i - j);

			cout << "Expected:\t" << expected << "\n";
			cout << "Actual:\t" << actual << "\n";
			expect(actual == expected);
			cout << "\n";
		}
	}

	END_TEST
}



int main() {
	unsigned pass_cnt = 0, fail_cnt = 0, skip_cnt = 0;
	//test_deci_digit(10, '1');
	
	//test_digit_deci('1', 1);
	
	//test_trim("2", "2");
	
	//test_add("2", "9", "11");
	
	//test_mult();
	test(sub);
	
	return 0;
}