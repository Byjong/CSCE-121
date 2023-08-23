#include <iostream>
#include "logic.h"

using std::cout, std::endl;
//                You should end up with at least 500 lines of test code

char monster_move[5][5] = {
    {'-', '-', 'M', '-', '-'},
    {'-', '-', '-', '-', '-'},
    {'M', '-', 'o', '-', 'M'},
    {'-', '-', '-', '-', '-'},
    {'-', '-', 'M', '-', '-'}
};

char monster_no_move[5][5] = {
    {'-', '-', 'M', '-', '-'},
    {'-', '-', '+', '-', '-'},
    {'M', '+', 'o', '+', 'M'},
    {'-', '-', '+', '-', '-'},
    {'-', '-', 'M', '-', '-'}
};

template<int r, int c>
char ** static_to_dynamic(char map[r][c]) {
    char ** t = new char*[r];
    for (int i = 0; i < r; ++i) {
        t[i] = new char[c];
        for (int j = 0; j < c; ++j) {
            t[i][j] = map[i][j];
        }
    }

    return t;
}
void dltMap(char ** level, int& maxRow){
if (level) {
        for (int row = 0; row < maxRow; row++) {
            delete[] level[row];
        }
        delete[] level;
    }
}

void test_getDirection() {
    cout << "Test getDirection\n";

    int maxRow = 5;
    int maxCol = 3;

    Player player;
    player.row = 3;
    player.col = 1;
    int nextRow = player.row;
    int nextCol = player.col;

    char ** level = loadLevel("player_move.txt", maxRow, maxCol, player);

    getDirection('w', nextRow, nextCol);
    doPlayerMove(level, maxRow, maxCol, player, nextRow, nextCol);
    getDirection('a', nextRow, nextCol);
    doPlayerMove(level, maxRow, maxCol, player, nextRow, nextCol);
    getDirection('s', nextRow, nextCol);
    doPlayerMove(level, maxRow, maxCol, player, nextRow, nextCol);
    getDirection('s', nextRow, nextCol);
    doPlayerMove(level, maxRow, maxCol, player, nextRow, nextCol);
    getDirection('s', nextRow, nextCol);
    doPlayerMove(level, maxRow, maxCol, player, nextRow, nextCol);
    getDirection('a', nextRow, nextCol);
    doPlayerMove(level, maxRow, maxCol, player, nextRow, nextCol);
    deleteMap(level, maxRow);


    getDirection('e', nextRow, nextCol);
    getDirection('W', nextRow, nextCol);
    getDirection('5', nextRow, nextCol);

    player.treasure = 0;
    level = loadLevel("player_move.txt", maxRow, maxCol, player);
    getDirection('d', nextRow, nextCol);
    doPlayerMove(level, maxRow, maxCol, player, nextRow, nextCol);
    getDirection('s', nextRow, nextCol);
    doPlayerMove(level, maxRow, maxCol, player, nextRow, nextCol);
    deleteMap(level, maxRow);

    level = loadLevel("player_move.txt", maxRow, maxCol, player);
    getDirection('a', nextRow, nextCol);
    doPlayerMove(level, maxRow, maxCol, player, nextRow, nextCol);
    deleteMap(level, maxRow);
}

void test_doMonsterAttack() {
    int maxRow = 5;
    int maxCol = 5;

    Player player;
    player.row = 2;
    player.col = 2;

    char* *level = static_to_dynamic<5, 5>(monster_move);
    doMonsterAttack(level, maxRow, maxCol, player);
    doMonsterAttack(level, maxRow, maxCol, player);
    dltMap(level, maxRow);
    
    char* *map = static_to_dynamic<5, 5>(monster_no_move);
    doMonsterAttack(map, maxRow, maxCol, player);
    dltMap(map, maxRow);
}

int main() {
    int maxRow;
    int maxCol;
    Player player;
    char** level = loadLevel("example.txt", maxRow, maxCol, player);

    level = resizeMap(level, maxRow, maxCol);
    deleteMap(level, maxRow);

    //Test for map text file errors
    level = loadLevel("not_exist.txt", maxRow, maxCol, player);
    level = resizeMap(level, maxRow, maxCol);
    deleteMap(level, maxRow);

    level = loadLevel("empty.txt", maxRow, maxCol, player);
    level = resizeMap(level, maxRow, maxCol);
    deleteMap(level, maxRow);

    level = loadLevel("no_map.txt", maxRow, maxCol, player);
    deleteMap(level, maxRow);
    
    level = loadLevel("invalid_tile.txt", maxRow, maxCol, player);
    deleteMap(level, maxRow);
    
    level = loadLevel("no_exit.txt", maxRow, maxCol, player);
    deleteMap(level, maxRow);
    
    level = loadLevel("few_tiles.txt", maxRow, maxCol, player);
    deleteMap(level, maxRow);
    
    level = loadLevel("many_tiles.txt", maxRow, maxCol, player);
    deleteMap(level, maxRow);
    
    //Test for player and map bound errors
    level = loadLevel("no_r.txt", maxRow, maxCol, player);
    deleteMap(level, maxRow);
    
    level = loadLevel("no_c.txt", maxRow, maxCol, player);
    deleteMap(level, maxRow);
    
    level = loadLevel("player_neg_r.txt", maxRow, maxCol, player);
    deleteMap(level, maxRow);
    
    level = loadLevel("player_neg_c.txt", maxRow, maxCol, player);
    deleteMap(level, maxRow);
    
    level = loadLevel("player_pos_r.txt", maxRow, maxCol, player);
    deleteMap(level, maxRow);
    
    level = loadLevel("player_pos_c.txt", maxRow, maxCol, player);
    deleteMap(level, maxRow);

    level = loadLevel("player_alph_r.txt", maxRow, maxCol, player);
    deleteMap(level, maxRow);
    
    level = loadLevel("player_alph_c.txt", maxRow, maxCol, player);
    deleteMap(level, maxRow);
    
    level = loadLevel("map_neg_r.txt", maxRow, maxCol, player);
    deleteMap(level, maxRow);

    level = loadLevel("example.txt", maxRow, maxCol, player);
    maxRow *= -1;
    char** resized = resizeMap(level, maxRow, maxCol);
    maxRow *= -1;
    dltMap(level, maxRow);
    dltMap(resized, maxRow);

    level = loadLevel("example.txt", maxRow, maxCol, player);
    maxCol *= -1;
    resized = resizeMap(level, maxRow, maxCol);
    maxCol *= -1;
    dltMap(level, maxRow);
    dltMap(resized, maxRow);

    level = loadLevel("map_neg_c.txt", maxRow, maxCol, player);
    deleteMap(level, maxRow);
    
    level = loadLevel("map_pos_r.txt", maxRow, maxCol, player);
    level = resizeMap(level, maxRow, maxCol);
    deleteMap(level, maxRow);
    
    level = loadLevel("map_pos_c.txt", maxRow, maxCol, player);
    level = resizeMap(level, maxRow, maxCol);
    deleteMap(level, maxRow);
    
    level = loadLevel("map_alph_r.txt", maxRow, maxCol, player);
    deleteMap(level, maxRow);
    
    level = loadLevel("map_alph_c.txt", maxRow, maxCol, player);
    deleteMap(level, maxRow);

    test_getDirection();
    test_doMonsterAttack();
    
    return 0;
}
