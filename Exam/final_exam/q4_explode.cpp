#include <iostream>
#include <stdexcept>

void explode(unsigned int*& array, size_t& size) {

    if (array == nullptr) {
        throw std::invalid_argument("Array does not exist.");
    }

    int new_size = 0;

    for (size_t i = 0; i < size; ++i) {
        if (array[i] == 0) {
            --new_size;
        }
        new_size += array[i];
    }

    size_t arr_size = new_size;

    unsigned int* new_arr = new unsigned int[arr_size];

    size_t idx = 0;

    while (idx < arr_size) {

        for (size_t i = 0; i < size; ++i) {

            if (array[i] != 0) {

                for (size_t j = 0; j < array[i]; ++j) {
                    new_arr[idx] = array[i];
                    ++idx;
                }

            }
        }
    }

    delete array;
    array = new_arr;
    size = arr_size;
}