#include <iostream>
#include <string>
using std::cin, std::cout, std::endl, std::string;

int main() {

	string sentence = "";
	string len_deobf = "";
	string deobf_sentence = "";
	int index = 0;
	
	cout << "Please enter obfuscated sentence: ";
	cin >> sentence;
	cout << "Please enter deobfuscation details: ";
	cin >> len_deobf;
	
	for(unsigned int i = 0; i < len_deobf.size(); i++){
		
		int num = static_cast<char>(len_deobf.at(i)) - '0';
		string part = sentence.substr(index, num);
		part += " ";
		deobf_sentence += part;
		index += num;
	
	}
	
	deobf_sentence.erase(deobf_sentence.size() - 1);
	
	cout << "Deobfuscated sentence: " << deobf_sentence << endl;
	
	return 0;
}
