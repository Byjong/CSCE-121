#include <iostream>
#include "functions.h"

using std::cout, std::endl;

bool is_valid_range(int a, int b) {
	if (a >= 10 && b < 10000 && a <= b){
		return true;
	}
	return false;
}

char classify_mv_range_type(int number) {
	
	int temp = number;
	int len = 0;
	int check_count = 1;
	
	int d1 = 0;
	int d2 = 0;
	
	bool was_inc = true;
	bool was_dec = true;
	
	bool is_m = false;
	bool is_v = false;
	
	while(temp != 0){
		temp /= 10;
		len++;
	}
	
	temp = number;
	while(temp != 0){
		
		if(check_count == len){
			break;
		}
		
		d1 = temp % 10;
		temp /= 10;
		d2 = temp % 10;
		
		if(d1 > d2 && was_inc == true){
			was_inc = false;
			was_dec = true;
			check_count++;
			
		}
		else if(d1 < d2 && was_dec == true){
			was_dec = false;
			was_inc = true;
			check_count++;
		}
		else{
			break;
		}
	}

	if(was_inc == false && was_dec == true){
		is_m = true;
	}
	else if(was_inc == true && was_dec == false){
		is_v = true;
	}
	
	if(check_count == len && is_m == true){
		return 'M';
	}
	else if(check_count == len && is_v == true){
		return 'V';
	}
	return 'N';
}

void count_valid_mv_numbers(int a, int b) {
	
	int num_m = 0;
	int num_v = 0;
	char val = ' ';
	
	for (int i = a; i <= b; i++){
		val = classify_mv_range_type(i);
		if(val == 'M'){
			num_m++;
		}
		else if(val == 'V'){
			num_v++;
		}
	}
	
	cout << "There are " << num_m << " mountain ranges and " << num_v << " valley ranges between " << a << " and " << b << "." << endl;
}