#include <iostream>

using std::cout, std::cin, std::endl;

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

/*  1st attempt at solution: didn't account for range more than 4 digits
	int len = 0;
	int temp = number;

	int d1 = 0;
	int d2 = 0;
	int d3 = 0;
	int d4 = 0;
	
	while (temp != 0){
		temp /= 10;
		len += 1;
	}
	
	if (len == 2){
		d1 = number / 10;
		d2 = number % 10;
		
		if (d1 < d2){
			return 'M';
		}
		else if (d1 > d2){
			return 'V';
		}
	}
	
	else if (len == 3){
		d1 = number / 100;
		d2 = (number / 10) %  10;
		d2 = d2 % 10;
		d3 = number % 10;
		
		if (d1 < d2 && d2 > d3){
			return 'M';
		}
		else if (d1 > d2 && d2 < d3){
			return 'V';
		}
	}

	else if (len == 4){
		d1 = number / 1000;
		d2 = (number / 100) % 10;
		d3 = (number / 10) % 10;
		d4 = number % 10;
		
		if (d1 < d2 && d2 > d3 && d3 < d4){
			return 'M';
		}
		else if (d1 > d2 && d2 < d3 && d3 > d4){
			return 'V';
		}
	}	
*/

/*	2nd attempt at solution: more condensed and covers more cases, still largely fails most of the same cases as 1st solution
	int temp = number;
	int len = 0;
	int check_count = 1;
	
	int d1 = 0;
	int d2 = 0;
	int d3 = 0;
	
	bool is_m = false;
	bool is_v = false;
	
	while(temp != 0){
		d1 = temp % 10;
		temp /= 10;
		
		if(temp == 0){
			break;
		}
		
		d2 = temp % 10;
		
		if (len % 2 == 0){
			if(d1 > d2){
				check_count++;
				temp /= 10;
				d3 = temp % 10;
				is_m = true;
				if(d2 < d3 && len > 2){
					check_count++;
				}
			}
		
			else if(d1 < d2){
				check_count++;
				temp /= 10;
				d3 = temp % 10;
				is_v = true;
				if(d2 > d3 && len > 2) {
					check_count++;
				}
			}			
			
			
			
		}
		
		else if (len % 2 == 1){
			if(d1 > d2){
				check_count++;
				temp /= 10;
				d3 = temp % 10;
				is_v = true;
				if(d2 < d3 && len > 2){
					check_count++;
				}
			}
		
			else if(d1 < d2){
				check_count++;
				temp /= 10;
				d3 = temp % 10;
				is_m = true;
				if(d2 > d3 && len > 2) {
					check_count++;
				}
			}			
		}
	}
*/

}

int main() {
	cout << classify_mv_range_type(1503) << endl;
	cout << classify_mv_range_type(120548) << endl;
}