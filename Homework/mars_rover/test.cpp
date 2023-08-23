#include <iostream>
#include <string>
#include "MyString.h"

using std::string, std::cout;

int main() {
    string data = "Hello, world!", find = "world?";
    MyString DATA = MyString(data.data()), FIND = MyString(find.data());

    cout << DATA.find(FIND) << "\n";
    cout << data.find(find) << "\n";
    return 0;
}