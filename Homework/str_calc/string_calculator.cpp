#include <iostream>
#include <string>
#include "./string_calculator.h"

using std::cout, std::endl;
using std::string;

unsigned int digit_to_decimal(char digit) {
	int num = digit;
	if(num < 48 || num > 57){
		throw std::invalid_argument("Invalid argument.");
	}
	num -= '0'; 
    return num;
}

char decimal_to_digit(unsigned int decimal) {
	if((decimal / 10) != 0){
		throw std::invalid_argument("Invalid argument.");
	}
	else{
		decimal += '0';
	}
    return static_cast<char>(decimal);
}

string trim_leading_zeros(string num) {
	
	bool is_neg = false;
	
	if(num.find('-') != std::string::npos){
		num.erase(0, 1);
		is_neg = true;
	}
	
	if(num.find_first_not_of('0') == std::string::npos){
		return "0";
	}
	
	num.erase(0, num.find_first_not_of('0'));
	
	if(is_neg == true){
		num.insert(0, "-");
	}
	
    return num;
}

string add(string lhs, string rhs)
{
     // Epic Debugging Lines
     // cout << flush;
     // cout << "LHS: " << lhs << endl;
     // cout << "RHS: " << rhs << endl;
     // cout << endl;

     // Remove Leading zeros
     lhs = trim_leading_zeros(lhs);
     rhs = trim_leading_zeros(rhs);

     // Determine if both numbers are negative.
     bool is_l_neg = lhs.at(0) == '-';
     bool is_r_neg = rhs.at(0) == '-';

     if (is_l_neg && is_r_neg)
     {
          lhs.erase(0, 1);
          rhs.erase(0, 1);
     } else if (!is_l_neg && is_r_neg) {
          return subtract(lhs, rhs.substr(1));
     } else if (is_l_neg && !is_r_neg) {
          return subtract(rhs, lhs.substr(1));
     }

     // Swap if lhs is shorter than rhs
     // allow for any nessesary increase of length
     if (lhs.size() < rhs.size())
          swap(lhs, rhs);

     // loop over string and add
     int j = lhs.size() - 1;
     for (int i = rhs.size() - 1; i >= 0; i--, j--)
     {
          lhs[j] += digit_to_decimal(rhs[i]);
          // cout << "Added Digit: " << lhs[j] << endl;
     }

     // cout << "All Digits: " << lhs << endl;
     // cout << endl;

     // perform any carries
     for (int i = lhs.size() - 1; i > 0; i--)
     {
          if (lhs[i] > '9')
          {
               int d = lhs[i] - '0';
               lhs[i - 1] = (lhs[i - 1] - '0') + d / 10 + '0';
               lhs[i] = decimal_to_digit(d % 10);
          }
     }

     // cout << "Intermediate: " << lhs << endl;
     // cout << endl;

     // perform carry on left-most digit
     if (lhs[0] > '9')
     {
          string k;
          k += lhs[0];
          lhs[0] = decimal_to_digit((lhs[0] - '0') % 10);
          k[0] = decimal_to_digit((k[0] - '0') / 10);
          lhs = k + lhs;
     }

     // cout << "Result: " << (neg ? "-" + lhs : lhs) << endl;
     // cout << "-------------------------" << endl;
     return (is_l_neg && is_r_neg) ? "-" + lhs : lhs;
}

string multiply(string lhs, string rhs) {
	
	bool is_neg = false;
	
	lhs = trim_leading_zeros(lhs);
	rhs = trim_leading_zeros(rhs);
	
	if(lhs.find('-') != std::string::npos){
		if(rhs.find('-') != std::string::npos){
			lhs.erase(0, 1);
			rhs.erase(0, 1);
		}
		else{
			lhs.erase(0, 1);
			is_neg = true;
		}
	}
	else if(rhs.find('-') != std::string::npos){
		rhs.erase(0, 1);
		is_neg = true;
	}

	char carry = '\0';
	char digit = '\0';
	string final_result = "0";
	int num_pos = 0;
	
	for(int i = lhs.length() - 1; i >= 0; i--){
		char a = lhs.at(i) - '0';
		string curr_result = "";
		
		for(int j = rhs.length() - 1; j >= 0; j--){
			char b = rhs.at(j) - '0';
			
			if(((a * b) + carry) > 9){
				digit = ((a * b) + carry) % 10;
				carry = ((a * b) + carry) / 10;
			}
			else{
				digit = ((a * b) + carry) % 10;
				carry = 0; 
			}
			
			digit += '0';
			
			curr_result.insert(0, 1, digit);
		}
		
		num_pos++;

		for(int k = 0; k < (num_pos - 1); k++){
			curr_result.append("0");
		}
		
		if(carry != 0){
			carry += '0';
			curr_result.insert(0, 1, carry);
			carry = 0;
		}
		
		final_result = add(final_result, curr_result);
		
	}
	
	
	if(carry != 0){
		carry += '0';
		final_result.insert(0, 1, carry);
	}
	
	if(is_neg == true){
		final_result.insert(0, "-");
	}
	
    return final_result;
}

///////[EXTRA CREDIT]/////////

string subtract(string lhs, string rhs)
{
     // Epic Debugging Lines
     cout << std::flush;
     cout << "LHS: " << lhs << "\n";
     cout << "RHS: " << rhs << "\n";
     cout << endl;

     // Trim leading zeros
     lhs = trim_leading_zeros(lhs);
     rhs = trim_leading_zeros(rhs);

	if (lhs == "0" && rhs == "0")
		return "0";
     if (lhs == "0")
          return (rhs.at(0) == '-') ? rhs.substr(1) : "-" + rhs;
     if (rhs == "0")
          return lhs;

     bool is_l_neg = lhs.at(0) == '-', is_r_neg = rhs.at(0) == '-';
     if (is_l_neg && is_r_neg) {
          return add(rhs.substr(1), lhs);
     } else if (is_l_neg && !is_r_neg) {
          return "-" + add(lhs.substr(1), rhs);
     } else if (!is_l_neg && is_r_neg) {
          return add(lhs, rhs.substr(1));
     }

     int n = lhs.size(), m = rhs.size();

     // Determine if lhs is smaller than rhs
     bool swapped = false;

     if (n < m) {
          swap(lhs, rhs);
          swapped = true;
     } else if (n == m) {          
          for (int i = 0; i < n; ++i) {
               if (lhs.at(i) < rhs.at(i)) {
                    swap(lhs, rhs);
                    swapped = true;
                    break;
               } else if (lhs.at(i) > rhs.at(i)) {
                    break;
               }
          }
     }

     n = lhs.size();
     m = rhs.size();

     // cout << "LHS: " << lhs << endl;
     // cout << "RHS: " << rhs << endl;
     // cout << endl;

     string result = "";

     // Loop over rhs backwards and subtract
     int carry = 0;
     for (int i = m - 1, j = n - 1; i > -1; --i, --j)
     {
          // compute difference of current digits
          int sub = lhs.at(j) - rhs.at(i) - carry;
          // cout << "Raw Calc:\t" << sub << "\n";

          // If subtraction is less then zero
          // we add then we add 10 into sub and
          // take carry as 1 for calculating next step
          if (sub < 0)
          {
               sub += 10;
               carry = 1;
          }
          else
               carry = 0;

          // cout << "Sub:\t" << sub << "\n";
          // cout << "Carry:\t" << carry << "\n";
          result.insert(0, 1, sub + '0');
     }

     //Subtract any remaining digits of the larger number.
     for (int i = n - m - 1; i > -1; --i) {
        int sub = digit_to_decimal(lhs.at(i)) - carry;
 
        // if the sub value is -ve, then make it positive
        if (sub < 0) {
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;
 
        result.insert(0, 1, decimal_to_digit(sub));
    }

     result = trim_leading_zeros(result);
     result = swapped ? "-" + result : result;
     // cout << "All Digits: " << result << endl;
     // cout << endl;

     return result;
}