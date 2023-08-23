#include "MyString.h"
#include <iostream>

using std::iostream;

MyString::MyString() : s_size{0}, s_cap{15}, c_str{new char[15]} {}

MyString::MyString(const MyString& str) : s_size{str.s_size}, s_cap{str.s_cap}, c_str{new char[s_cap]} {
    for (size_t i = 0; i < s_size; ++i) {
        this->c_str[i] = str.c_str[i];
    }

    for (size_t j = s_size; j < s_cap; ++j) {
        this->c_str[j] = 0;
    }
}

MyString::MyString(const char* s) : s_size{0}, s_cap{15}, c_str{nullptr} {
    size_t idx = 0;
    while (s[idx] != '\0') {
        ++idx;
    }

    this->s_size = idx;
    while (this->s_size > this->s_cap) {
        this->s_cap *= 2;
    }

    this->c_str = new char[this->s_cap];

    for (size_t i = 0; i < s_size; ++i) {
        this->c_str[i] = s[i];
    }

    for (size_t j = s_size; j < s_cap; ++j) {
        this->c_str[j] = 0;
    }
}

MyString::~MyString() {
    delete[] this->c_str;
}

void MyString::resize(size_t n) {
    this->s_size = n;

    while (n > this->s_cap) {
        this->s_cap *= 2;
    }

    for (size_t i = n; i < this->s_cap; ++i) {
        this->c_str[i] = 0;
    }
}

size_t MyString::capacity() const noexcept {
    return this->s_cap;
}

size_t MyString::size() const noexcept {
    return this->s_size;
}

size_t MyString::length() const noexcept {
    return this->s_size;
}

char* MyString::data() const noexcept {
    return this->c_str;
}

bool MyString::empty() const noexcept {
    return !this->s_size;
}

const char& MyString::front() const {
    return this->c_str[0];
}

const char& MyString::at(size_t pos) const {
    if (pos >= this->s_size) {
        throw std::out_of_range("Index out of bounds.");
    }

    return this->c_str[pos];
}

void MyString::clear() noexcept {
    for (size_t i = 0; i < this->s_cap; ++i) {
        this->c_str[i] = 0;
    }

    this->s_size = 0;
    this->s_cap = 15;
}

ostream& operator<< (ostream& os, const MyString& str) {
    for (size_t i = 0; i < str.size(); ++i) {
        os << str.at(i);
    }
    return os;
}

MyString& MyString::operator=(const MyString& str) {
    this->s_size = str.size();
    this->s_cap = str.capacity();

    delete[] this->c_str;
    this->c_str = new char[this->s_cap];

    for (size_t i = 0; i < s_size; ++i) {
        this->c_str[i] = str.at(i);
    }

    for (size_t j = s_size; j < s_cap; ++j) {
        this->c_str[j] = 0;
    }

    return *this;
}

MyString& MyString::operator+=(const MyString& str) {
    size_t new_size = this->s_size + str.size();
    size_t new_cap = this->s_cap + str.capacity();

    char* new_str = new char[new_cap];

    for (size_t i = 0; i < s_size; ++i) {
        new_str[i] = this->c_str[i];
    }

    for (size_t j = s_size; j < new_size; ++j) {
        new_str[j] = str.at(j - s_size);
    }

    for (size_t k = new_size; k < new_cap; ++k) {
        new_str[k] = static_cast<char>(0);
    }

    delete[] this->c_str;

    this->c_str = new_str;
    this->s_size += str.size();

    while (this->s_size > this->s_cap) {
        this->s_cap *= 2;
    }

    return *this;
}

size_t MyString::find(const MyString& str, size_t pos) const noexcept {

    size_t idx = static_cast<size_t>(-1);

    for (size_t i = pos; i < this->s_size - str.size() + 1; ++i) {
        bool is_equal = true;

        for (size_t j = 0; j < str.size(); ++j) {
            if (this->c_str[i + j] != str.at(j)) {
                is_equal = false;
                break;
            }
        }

        if (is_equal) {
            idx = i;
        }
    }

    return idx;
}

bool operator==(const MyString& lhs, const MyString& rhs) noexcept{
    if(lhs.size() != rhs.size()){
        return false;
    }

    for(size_t i = 0; i < lhs.size(); ++i){
        if(lhs.at(i) != rhs.at(i)){
            return false;
        }
    }
    return true;
}

MyString operator+(const MyString& lhs, const MyString& rhs){
    size_t new_size = lhs.size() + rhs.size();
    size_t new_cap = lhs.capacity() + rhs.capacity();

    char* new_str = new char[new_cap];

    for (size_t i = 0; i < lhs.size(); ++i) {
        new_str[i] = lhs.at(i);
    }

    for (size_t j = lhs.size(); j < new_size; ++j) {
        new_str[j] = rhs.at(j - lhs.size());
    }

    for (size_t k = new_size; k < new_cap; ++k) {
        new_str[k] = static_cast<char>(0);
    }

    return MyString(new_str);
}