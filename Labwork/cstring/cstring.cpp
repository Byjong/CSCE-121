#include <iostream>
#include "cstring.h"

unsigned int length(char str[]) {
  
	int count = 0;
	int idx = 0;
	
	while(str[idx] != '\0'){
		count++;
		idx++;
	}

	return count;
}

unsigned int find(char str[], char character) {
  
	int idx = 0;
	while(str[idx] != '\0'){
		if(character == str[idx]){
			return idx;
		}
		idx++;
	}
 
	return length(str);
}

bool equalStr(char str1[], char str2[]) {

	if(length(str1) != length(str2)){
		return false;
	}
	else{
		int idx = 0;
		while(str1[idx] != '\0'){
			if(str1[idx] != str2[idx]){
				return false;
			}
			idx++;
		}
	}
	return true;
}