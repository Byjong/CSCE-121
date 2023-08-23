#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "logic.h"

using std::cout, std::endl, std::istringstream, std::ifstream, std::string, std::stoi;

/**
 * TODO: Student implement this function
 * Load representation of the dungeon level from file into the 2D map.
 * Calls createMap to allocate the 2D array.
 * @param   fileName    File name of dungeon level.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference to set starting position.
 * @return  pointer to 2D dynamic array representation of dungeon map with player's location., or nullptr if loading fails for any reason
 * @updates  maxRow, maxCol, player
 */
char** loadLevel(const string& fileName, int& maxRow, int& maxCol, Player& player) {
    
    ifstream fin(fileName);
    if(!fin.is_open()){
        cout << "ERROR" << endl;
	    return nullptr;
	}

    //fin >> maxRow >> maxCol >> player.row >> player.col;
    fin >> maxRow;
     if (fin.fail()){
          return nullptr;
     }

     if (maxRow < 1){
          return nullptr;
     }


     fin >> maxCol;
     if (fin.fail()){
          return nullptr;
     }

     if (maxCol < 1){
          return nullptr;
     }

     if (maxRow > INT32_MAX / maxCol){
          return nullptr;
     }

     fin >> player.row;
     if (fin.fail()){
          return nullptr;
     }

     if (player.row < 0){
          return nullptr;
     }

     if (player.row >= maxRow){
          return nullptr;
     }

     fin >> player.col;
     if (fin.fail()){
          return nullptr;
     }

     if (player.col < 0){
          return nullptr;
     }

     if (player.col >= maxCol){
          return nullptr;
     }
    
    char** map = new char*[maxRow];
    for (int i = 0; i < maxRow; ++i) {
        map[i] = new char[maxCol];
    }

    for(int rIdx = 0; rIdx < maxRow; rIdx++){
        for(int cIdx = 0; cIdx < maxCol; cIdx++){
            char tile;
            fin >> tile;
            map[rIdx][cIdx] = tile;
            cout << tile;
        }
        cout << "\n";
    }

    return map;
}

/**
 * TODO: Student implement this function
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @updates  nextRow, nextCol
 */
void getDirection(char input, int& nextRow, int& nextCol) {
    if(input == MOVE_UP){
        nextRow -= 1;
    }
    else if(input == MOVE_DOWN){
        nextRow += 1;
    }
    else if(input == MOVE_LEFT){
        nextCol -= 1;
    }
    else if(input == MOVE_RIGHT){
        nextCol += 1;
    }
}

/**
 * TODO: [suggested] Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char** createMap(int maxRow, int maxCol) {
    char** map = new char*[maxRow];
    for (int i = 0; i < maxRow; ++i) {
        map[i] = new char[maxCol];
    }

    for (int rIdx = 0; rIdx < maxRow; ++rIdx) {
        for(int cIdx = 0; cIdx < maxCol; cIdx++){
            map[rIdx][cIdx] = '-';
        }
    }
    return map;
}

/**
 * TODO: Student implement this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @return None
 * @update map, maxRow
 */
void deleteMap(char**& map, int& maxRow) {
    if(map){
        for(int row = 0; row < maxRow; row++){
            delete[] map[row];
        }
        delete[] map;
    }

    maxRow = 0;
    map = nullptr;
}

/**
 * TODO: Student implement this function
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player, and remember to avoid memory leaks!
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
 * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
 * @return  pointer to a dynamically-allocated 2D array (map) that has twice as many columns and rows in size.
 * @update maxRow, maxCol
 */
char** resizeMap(char** map, int& maxRow, int& maxCol) {
    int extendRow = maxRow * 2;
    int extendCol = maxCol * 2;

    int row = maxRow, col = maxCol;
    char** extend_map = new char*[extendRow];
    for (int i = 0; i < extendRow; ++i) {
        map[i] = new char[extendCol];
    }

    for(int rIdx = 0; rIdx < row; ++rIdx){
        for(int cIdx = 0; cIdx < col; ++cIdx){
            extend_map[rIdx][cIdx] = map[rIdx][cIdx];

            if(map[rIdx][cIdx] == TILE_PLAYER){
                extend_map[rIdx + row][cIdx] = TILE_OPEN;
                extend_map[rIdx][cIdx + col] = TILE_OPEN;
                extend_map[rIdx + row][cIdx + col] = TILE_OPEN;
            }
            else{
                extend_map[rIdx + row][cIdx] = map[rIdx][cIdx];
                extend_map[rIdx][cIdx + col] = map[rIdx][cIdx];
                extend_map[rIdx + row][cIdx + col] = map[rIdx][cIdx];
            }
        }
    }

    int initRow = maxRow;
    deleteMap(map, initRow);

    maxRow = extendRow;
    maxCol = extendCol;

    for (int i = 0; i < extendRow; ++i) {
        for(int j = 0; j < extendCol; ++j){
            cout << extend_map[i][j];
        }
        cout << endl;
    }

    return extend_map;
}

/**
 * TODO: Student implement this function
 * Checks if the player can move in the specified direction and performs the move if so.
 * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
 * Cannot move onto TILE_EXIT without at least one treasure. 
 * If TILE_TREASURE, increment treasure by 1.
 * Remember to update the map tile that the player moves onto and return the appropriate status.
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object to by reference to see current location.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @return  Player's movement status after updating player's position.
 * @update map contents, player
 */
int doPlayerMove(char** map, int maxRow, int maxCol, Player& player, int nextRow, int nextCol) {
    INFO(map);
    INFO(maxRow);
    INFO(maxCol);
    INFO_STRUCT(player);
    INFO(nextRow);
    INFO(nextCol);

    return 0;
}

/**
 * TODO: Student implement this function
 * Update monster locations:
 * We check up, down, left, right from the current player position.
 * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
 * If we see a monster before an obstacle, the monster moves one tile toward the player.
 * We should update the map as the monster moves.
 * At the end, we check if a monster has moved onto the player's tile.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference for current location.
 * @return  Boolean value indicating player status: true if monster reaches the player, false if not.
 * @update map contents
 */
bool doMonsterAttack(char** map, int maxRow, int maxCol, const Player& player) {
    INFO(map);
    INFO(maxRow);
    INFO(maxCol);
    INFO_STRUCT(player);
    return false;
}