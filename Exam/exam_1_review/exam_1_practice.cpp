#include <iostream>
#include "exam_1_practice.h"
#include <stdexcept>
#include <string>
#include <sstream>
#include <cmath>

using std::cin, std::cout, std:: endl, std::istringstream;

void multiples(unsigned int n, unsigned int k, unsigned int l){
	unsigned int num = 1;	//Number to check if a it's multiple of k or l

	while(n > 0){
		if(num % k == 0 || num % l == 0){
			cout << num << " ";
			n--;
		}
		num++;	//Iternate in order to check all positive integers
	}
	cout << endl;
}

bool triproduct(unsigned int n){
	
	unsigned int num = 1;
	
	while((num + 2) < n){
		unsigned int triproduct = num * (num + 1) * (num + 2);		//For extensive solution: ERROR CHEKC NEEDED
		
		if(n == triproduct){
			return true;
		}
		num++;
	}
	return false;
}

int segments(int n, int nums[]){
	
	int num = nums[0];
	int count = 1;
	
	for(int i = 0; i < n; i++){
		if(nums[i] != num){
			count++;
			num = nums[i];
		}
	}
	return count;
}

void find_sum(unsigned int n, int nums[], int k){

	int left = 0;
	int right = 0;
	bool has_Sum = false;
	
	for(unsigned int i = 0; i < n; i++){
		left = nums[i];
		
		for(unsigned int j = i + 1; j < n; j++){
			right = nums[j];
			
			if((left + right) == k){
				cout << left << " " << right << endl;
				has_Sum = true;
			}
		}
	}
	
	if(!has_Sum){
		cout << "none" <<endl;
	}
}

bool isNumericPalindrome(int n){
	
	int temp = n;
	int len = 0;
	
	while(temp != 0){
		temp /= 10;
		len++;
	}
	/*	Whether length of n is odd or even, integer division by 2 will give right number of loop iterations as, 
	in the case of an odd length number, the very middle can be any number.	*/ 
	
	int loop_count = len / 2;		
	
	
	for(int idx = 0; idx < loop_count; idx++){
		
		int mod_fact = pow(10, (len - 1));
		temp = n / mod_fact;
		
		if(temp != (n % 10)){  
			return false;
		}
		
		len -= 2;	//Decrement len so that your modulus factor is correct.
		n -= (temp * mod_fact);
		n /= 10;
	}
	return true;
}

bool isHappy(int n){

	int total = 0;
	int temp = n;
	
	do{
		total = 0;
		while(temp != 0){
			int digit = temp % 10;
			temp /= 10;
			total += (digit * digit);
		}
		temp = total;
		
		if(total == 1){
			return true;
		}
	}
	while(total != 4);
	return false;
}
