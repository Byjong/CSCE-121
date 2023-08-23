#include <iostream>
#include "exam_1_practice.h"
#include <stdexcept>

using std::cin, std::cout, std:: endl;

int main() {

	int option = 0;

	cout << "Pick an operation you would like to perform by typing in the corresponding number in partheses." << endl;
	cout << "Multiples (1)" << endl;
	cout << "Triproduct (2)"<< endl;
	cout << "Array segments (3)" << endl;
	cout << "Find the sum (4)" << endl;
	cout << "Numeric Palindrome (5)" << endl;
	cout << "Happy number (6)" << endl;
	cout << endl;
	
	cout << "Enter option: ";
	cin >> option;
	cout << endl;
	
	if(option == 1){
		int n = 0;
		int k = 0;
		int l = 0;
	  
		cout << "Enter positive number (n): ";
		cin >> n;
		cout << "Enter positive number (k): ";
		cin >> k;
		cout << "Enter positive number (l): ";
		cin >> l;

		multiples(n, k, l);	
	}
	else if(option == 2){
		
		int n = 0;
		
		cout << "Enter a positive number to check if it is a triproduct: ";
		cin  >> n;
		
		if(triproduct(n)){
			cout << n << " is a triproduct." << endl;
		}
		else{
			cout << n << " is not a triproduct." << endl;
		}
	}
	else if(option == 3){
		
		const int SIZE = 10;
		int arr[SIZE] = {};
		
		int len = 0;
		cout << "Number of elements: "; 
		cin >> len;
		
		for(int i = 0; i < len; i++){
			cout << "Enter number: " << endl;
			cin >> arr[i];
			cout << endl;
		}
		
		cout << "Number of segments: " << segments(len, arr) << endl;
	}
	
	else if(option == 4){
		
		int temp = 0;
		cout << "Enter length of an array: "<< endl;
		cin >> temp;
		
		const unsigned int len = temp;
		
		int arr[] = {0};
		
		for(unsigned int i = 0; i < len; i++){
			cout << "Enter number: " << endl;
			cin >> arr[i];
			cout << endl;
		}
		
		int target = 0;
		cout << "Enter target number: ";
		cin >> target;
		cout << endl;
		find_sum(len, arr, target);
	}
	else if(option == 5){
		
		int num = 0;
		cout << "Enter number: ";
		cin >> num;
		
		if(isNumericPalindrome(num)){
			cout << num << " is a numeric palindrome.";
		}
		else{
			cout << num << " is not a numeric palindrome";
		}
		cout << endl;
	}
	
	else if(option == 6){
		
		int num = 0;
		cout << "Enter number: ";
		cin >> num;
		
		if(isHappy(num)){
			cout << num << " is a happy number.";
		}
		else{
			cout << num << " is not a happy number.";
		}
		cout << endl;
	}
	return 0;
}