#include <iostream>
#include <string>
#include <limits>
#include "./string_calculator.h"

#include <sstream>

using std::cout, std::endl, std::cin;
using std::string, std::istringstream; 

int main() {

	string input = "";
	
	cout << "String Calculator" << endl;
    cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl;
	
	while(true){
		string result = "Invalid input.";
		cout << ">> ";
		getline(cin, input);
		
		if(input == "q" || input == "quit"){
			break;
		}
		
		if(input.find("+") != std::string::npos){
			
			string num1 = input.substr(0, input.find("+"));
			num1 = num1.substr(0, num1.find(" "));
			
			string num2 = input.substr((input.find("+") + 1), input.length());
			num2 = num2.substr(num2.find_first_not_of(" "), num2.length());
			
			result = add(num1, num2);
		}
		
		else if(input.find("*") != std::string::npos){
			
			string num1 = input.substr(0, input.find("*"));
			num1 = num1.substr(0, num1.find(" "));
			
			string num2 = input.substr((input.find("*") + 1), input.length());
			num2 = num2.substr(num2.find_first_not_of(" "), num2.length());
		
			result = multiply(num1, num2);
		}
		
		cout << endl;
		cout << "ans =" << endl << endl;
		cout << "    " << result << endl << endl;

	}
	
	cout << endl << "farvel!" << endl;
	
	return 0;
}

