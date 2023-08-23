#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

int main(int argc, char *argv[]){

    string filename = argv[1];
    string targetWidthStr = argv[2];
    string targetHeightStr = argv[3];

    int width = 0;
    int height = 0;

    width = stoi(targetWidthStr);
    height = stoi(targetHeightStr);

    Pixel **image = nullptr;
    image = loadImage(filename, width, height);
    
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            cout << energy(image, i, j, width-1, height-1) << endl;
        }
    }

    int* seam = new int[height]{0};

    cout << getVerticalSeam(image, 4, width, height, seam) << endl << endl;

    for(int i = 0; i < height; i++){
        cout << seam[i] << endl;
    }
    
    cout << &getVerticalSeam << endl;

    delete[] seam;

    deleteImage(image, width);
}