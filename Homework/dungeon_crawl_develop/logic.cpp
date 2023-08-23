#include <iostream>
#include <fstream>
#include <string>
#include "logic.h"

using std::cout, std::endl, std::ifstream, std::string;

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
char **loadLevel(const string &fileName, int &maxRow, int &maxCol, Player &player)
{
     ifstream fin(fileName);

     if (!fin.is_open()){
          return nullptr;
     }

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

     char tile;
     bool has_exit = false;
     int num_tiles = 0, max_tiles = maxRow * maxCol;
     while (true){
          fin >> tile;

          if (fin.eof()) {
               break;
          }

          if (++num_tiles > max_tiles){
               return nullptr;
          }

          if(tile == TILE_EXIT || tile == TILE_DOOR) {
               has_exit = true;
          }
          else if(
               tile != TILE_OPEN && 
               tile != TILE_PLAYER && 
               tile != TILE_TREASURE && 
               tile != TILE_AMULET && 
               tile != TILE_MONSTER && 
               tile != TILE_PILLAR
               )
          {
               return nullptr;
          }
     }

     if (num_tiles < max_tiles){
          return nullptr;
     }

     fin.close();
     fin.clear();
     fin.open(fileName);
     fin.ignore(std::numeric_limits<int>::max(), '\n');
     fin.ignore(std::numeric_limits<int>::max(), '\n');

     char **map = new char*[maxRow];

     for (int i = 0; i < maxRow; ++i){
          map[i] = new char[maxCol];
          for (int j = 0; j < maxCol; ++j){
               fin >> map[i][j];
          }
     }

     if (!has_exit)
     {
          deleteMap(map, maxRow);
          return nullptr;
     }

     map[player.row][player.col] = TILE_PLAYER;

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
void getDirection(char input, int &nextRow, int &nextCol)
{
     input = tolower(input);
     if(input == MOVE_UP){
          --nextRow;
     }
     else if(input == MOVE_DOWN){
          ++nextRow;
     }
     else if(input == MOVE_LEFT){
          --nextCol;
     }
     else if(input == MOVE_RIGHT){
          ++nextCol;
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
char **createMap(int maxRow, int maxCol)
{
     if (maxRow < 0)
          return nullptr;
     
     if (maxCol < 0)
          return nullptr;

     char** map = new char*[maxRow];
     for (int i = 0; i < maxRow; ++i)
     {
          map[i] = new char[maxCol];
          for (int j = 0; j < maxCol; ++j)
               map[i][j] = TILE_OPEN;
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
void deleteMap(char **&map, int &maxRow)
{
     if (map) {
          for (int i = 0; i < maxRow; ++i)
               delete[] map[i];
          delete[] map;
     }
     maxRow = 0;
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
char **resizeMap(char **map, int &maxRow, int &maxCol)
{
     if (map == nullptr){
          return nullptr;
     }

     if (maxRow < 1){
          return nullptr;
     }

     if (maxRow > INT32_MAX / 2){
          return nullptr;
     }

     if (maxCol < 1){
          return nullptr;
     }

     if (maxCol > INT32_MAX / 2){
          return nullptr;
     }

     char **extend_map = new char*[maxRow * 2];
     for (int i = 0; i < maxRow * 2; ++i){
          extend_map[i] = new char[maxCol * 2];
     }
     for (int rIdx = 0; rIdx < maxRow; ++rIdx){
          for (int  cIdx = 0;  cIdx < maxCol; ++cIdx){
               extend_map[rIdx][cIdx] = map[rIdx][cIdx];
               
               if(map[rIdx][cIdx] == TILE_PLAYER){
                     extend_map[rIdx][cIdx + maxCol] = TILE_OPEN;
                     extend_map[rIdx + maxRow][cIdx + maxCol] = TILE_OPEN;
                     extend_map[rIdx + maxRow][cIdx] = TILE_OPEN;
               }
               else{
                     extend_map[rIdx][cIdx + maxCol] = map[rIdx][cIdx];
                     extend_map[rIdx + maxRow][cIdx + maxCol] = map[rIdx][cIdx];
                     extend_map[rIdx + maxRow][cIdx] = map[rIdx][cIdx];
               }
          }
     }

     int initRow = maxRow;
     deleteMap(map, initRow);

     maxRow *= 2;
     maxCol *= 2;

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
int doPlayerMove(char **map, int maxRow, int maxCol, Player &player, int nextRow, int nextCol)
{
     if (nextRow < 0){
          return STATUS_STAY;
     }

     if (nextRow >= maxRow){
          return STATUS_STAY;
     }

     if (nextCol < 0){
          return STATUS_STAY;
     }

     if (nextCol >= maxCol){
          return STATUS_STAY;
     }

     if(map[nextRow][nextCol] == TILE_MONSTER || map[nextRow][nextCol] == TILE_PILLAR){
          return STATUS_STAY;
     }
     else if(map[nextRow][nextCol] == TILE_EXIT){
          if(player.treasure){
               map[player.row][player.col] = TILE_OPEN;
               player.row = nextRow;
               player.col = nextCol;
               map[player.row][player.col] = TILE_PLAYER;
               return STATUS_ESCAPE;
          }
          else{
               return STATUS_STAY;
          }
     }
     else if(map[nextRow][nextCol] == TILE_AMULET){
               map[player.row][player.col] = TILE_OPEN;
               player.row = nextRow;
               player.col = nextCol;
               map[player.row][player.col] = TILE_PLAYER;
               return STATUS_AMULET;
     }
     else if(map[nextRow][nextCol] == TILE_DOOR){
          map[player.row][player.col] = TILE_OPEN;
          player.row = nextRow;
          player.col = nextCol;
          map[player.row][player.col] = TILE_PLAYER;
          return STATUS_LEAVE;
     }
     else if(map[nextRow][nextCol] == TILE_OPEN){
          map[player.row][player.col] = TILE_OPEN;
          player.row = nextRow;
          player.col = nextCol;
          map[player.row][player.col] = TILE_PLAYER;
          return STATUS_MOVE;
     }
     else if(map[nextRow][nextCol] == TILE_TREASURE){
          map[player.row][player.col] = TILE_OPEN;
          player.row = nextRow;
          player.col = nextCol;
          map[player.row][player.col] = TILE_PLAYER;
          ++player.treasure;
          return STATUS_TREASURE;
     }
     return STATUS_STAY;
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
bool doMonsterAttack(char **map, int maxRow, int maxCol, const Player &player)
{
     char tile;
     bool eaten = false;
     for (int i = player.row - 1; i >= 0; --i) {
          tile = map[i][player.col];
          if (tile == TILE_PILLAR) {
               break;
          }
          else if (tile == TILE_MONSTER) {
               map[i][player.col] = TILE_OPEN;
               map[i + 1][player.col] = TILE_MONSTER;
               if (i + 1 == player.row) {
                    eaten = true;
               }
          }
     }

     for (int i = player.row + 1; i < maxRow; ++i) {
          tile = map[i][player.col];
          if (tile == TILE_PILLAR) {
               break;
          }
          else if (tile == TILE_MONSTER) {
               map[i][player.col] = TILE_OPEN;
               map[i - 1][player.col] = TILE_MONSTER;
               if (i - 1 == player.row) {
                    eaten = true;
               }
          }
     }

     for (int j = player.col - 1; j > -1; --j) {
          tile = map[player.row][j];
          if (tile == TILE_PILLAR) {
               break;
          }
          else if (tile == TILE_MONSTER) {
               map[player.row][j] = TILE_OPEN;
               map[player.row][j + 1] = TILE_MONSTER;
               if (j + 1 == player.col) {
                    eaten = true;
               }
          }
     }

     for (int j = player.col + 1; j < maxCol; ++j) {
          tile = map[player.row][j];
          if (tile == TILE_PILLAR) {
               break;
          }
          else if (tile == TILE_MONSTER) {
               map[player.row][j] = TILE_OPEN;
               map[player.row][j - 1] = TILE_MONSTER;
               if (j - 1 == player.col) {
                    eaten = true;
               }
          }
     }

     return eaten;
}
