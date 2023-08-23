#include <stdexcept>

int Largest(int a, int b, int c) {
  int d = c;
  if (a > d) {
    d = a;
  } 
  if (b > d) {
    d = b;
  } 
  if (c > d) {
    d = c;
  }
  return d;
}

bool SumIsEven(int a, int b) {
  if(((a + b) % 2) == 1 || ((a + b) % 2) == -1){
    return false;
  }
  else{
    return true;
  }
}

int BoxesNeeded(int apples) {
	
	if(apples < 0){
		return 0;
	}
	else if ((apples % 20) == 0){
		return apples / 20;
	}
	else{
		return 1 + (apples / 20);
	}
}

bool SmarterSection(int A_correct, int A_total, int B_correct, int B_total) {
	
	if(A_correct < 0 || A_total < 0 || B_correct < 0 || B_total < 0){
		throw std::invalid_argument("Invalid Argument.");
	}
	
	if(A_correct > A_total || B_correct > B_total){
		throw std::invalid_argument("Error");
	}
	
	return (static_cast<double>(A_correct)/A_total) > (static_cast<double>(B_correct)/B_total);
}

bool GoodDinner(int pizzas, bool is_weekend) {
  
  if(is_weekend == false){
	  if (pizzas >= 10 && pizzas <= 20) {
		return true;
	  }
	  else{
		return false;
	  }
  }
  else{
	  if(pizzas >= 10){
		  return true;
	  }
	  else{
		  return false;
	  }
  }
}

int SumBetween(int low, int high) {
	int value = 0;
	
	if(low > high){
		throw std::invalid_argument("Arguments out of order.");
	}
	
	else if(-(low + 1) == high){
		return low;
	}
	
	else if(-(low - 1) == high){
		return high;
	}
	
	else if (low == high){
		return high;
	}

	else if(-low == high){
		return 0;
	}
	
	else if (low >= 0 && high > 0){
		for (int n = low; n <= high; n++) {
			value += n;
		
			if(value < 0){
				throw std::overflow_error("Overflow.");
			}	  
		}
	}
	
	else if(low < 0 && high <= 0){
		for (int n = low; n <= high; n++) {
			value += n;
		
			if(value > 0){
				throw std::overflow_error("Overflow.");
			}  
		}
	}
	
	else{
		
		int temp = INT32_MIN;
		
		value += INT32_MAX;
		
		int sign_change_low = 0;
		int sign_change_high = 0;
		
		bool is_pos = true;
		bool is_neg = false;
		
		for(int n = low; n <= 0; n++){
			value += n;
			
			if(value < 0 && is_pos == true){
				sign_change_low++;
				is_pos = false;
				is_neg = true;
			}
			
			else if(value > 0 && is_neg == true){
				sign_change_low++;
				is_pos = true;
				is_neg = false;
			}
			
		}
		
		is_pos = false;
		is_neg = true;
		
		for (int n = 0; n <= high; n++){
			temp += n;
			
			if(temp > 0 && is_neg == true){
				sign_change_high++;
				is_pos = true;
				is_neg = false;
			}
			
			else if(temp < 0 && is_pos == true){
				sign_change_high++;
				is_pos = false;
				is_neg = true;
			}
		}
		
		value = value + temp + 1;
		
		if(-low > high){
			if(value > 0){
				throw std::overflow_error("Overflow.");
			}
		}
		else if(-low < high){
			if(value < 0){
					throw std::overflow_error("Oberflow.");
			}
		}
	
		if((sign_change_high - sign_change_low) > 1){
			throw std::overflow_error("Overflow.");
		}
	}
	return value;
}


int Product(int a, int b) {
	
	int max = 0;
	
	if(a == 0 || b == 0){
		return 0;
	}
	
	if(a > 0 && b > 0){
		max = INT32_MAX / a;
	
		if(b > max){
			throw std::overflow_error("Overflow.");
		}
	}
	else if(a > 0 && b < 0){
		max = INT32_MIN / a;
		
		if(b < max){
			throw std::overflow_error("Overflow.");
		}
	}
	else if(a < 0 && b > 0){
		max = INT32_MIN / a;
		
		if(b > max){
			throw std::overflow_error("Overflow.");
		}
	}
	else if(a < 0 && b < 0){
		max = INT32_MAX / a;
		
		if(b < max){
			throw std::overflow_error("Overflow.");
		}
	}
	
	return a * b;
}