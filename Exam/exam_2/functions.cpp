#include <iostream>
#include <string>
#include <stdexcept>

using std::string;

int main(){
    struct BoundingBox{
        int min_row_idx;
        int min_col_idx;
        int max_row_idx;
        int max_col_idx;
    };

    void crop(int**& array, size_t& row_capacity, size_t&column_capacity, size_t& rows, size_t& columns, BoundingBox selected_area){

        if(selected_area.min_row_idx >= row_capacity || selected_area.min_col_idx >= column_capacity){
            throw std::out_of_range("Invalid bounding box dimensions.");
        }

        int targetRows = selected_area.max_row_idx - selected_area.min_row_idx + 1;
        int targetCols = selected_area.max_col_idx - selected_area.min_col_idx + 1;

        int** rebound = new int*[targetRows];
        for(int i = 0; i <= targetRows; ++i){
            rebound[i] = new int[targetCols];
        }

        for (int elem = 0; elem < (targetRows * targetCols); elem++){
            rebound[elem / targetCols][elem % targetCols] = array[elemIdx / columns][elemIdx % columns];
        }

        for(int rIdx = selected_area.min_row_idx, rIdx <= selected_area.max_row_idx; rIdx++){
            for(int cIdx = selected_area.min_col_idx, cIdx <= selected_area.col_row_idx; cIdx++){
                
                rebound[rIdx - selected_area.min_row_idx][cIdx - selected_area.min_col_idx] = array[rIdx][cIdx];
            
            }
        }

        delete[] array;

        array = rebound;
    }



    return 0;
}