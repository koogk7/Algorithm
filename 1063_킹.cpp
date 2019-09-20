// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <iostream>
#include <queue>
#include <vector>
#include <string.h>
#include <algorithm>
#include <map>
#include <math.h>
#include <stack>
#include <set>
#include <sstream>
#include <string.h>
using namespace std;

/*
 * 1063 킹
 *  - 문제를 잘못 이해함....
 *  - 생각대로 구현했는데 틀릴 경우 문제를 다시 한번 꼼꼼히 읽어보자!
 */

struct point {
    int row, col;
};
point king;
point stone;


map<string, point> move_dir;



void initMove(){
    move_dir.insert(pair<string,point>("R",{0,1}));
    move_dir.insert(pair<string,point>("L",{0,-1}));
    move_dir.insert(pair<string,point>("B",{1,0}));
    move_dir.insert(pair<string,point>("T",{-1,0}));
    move_dir.insert(pair<string,point>("RT",{-1,1}));
    move_dir.insert(pair<string,point>("LT",{-1,-1}));
    move_dir.insert(pair<string,point>("RB",{1,1}));
    move_dir.insert(pair<string,point>("LB",{1,-1}));
}

bool isBoudary(int row, int col){
    return row >=0 and row < 8 and col >=0 and col < 8;
}

void move(int row, int col, string dir){
    int nr = row + move_dir[dir].row;
    int nc = col + move_dir[dir].col;

    if(!isBoudary(nr,nc)) return;

    if(nr == stone.row and nc == stone.col) {
        int nr_stone = stone.row + move_dir[dir].row;
        int nc_stone = stone.col + move_dir[dir].col;
        if (!isBoudary(nr_stone, nc_stone)) return;
        stone = {nr_stone, nc_stone};
    }

    king = {nr,nc};
}


int main(){

    initMove();
    int n;
    string king_input, stone_input;
    string dir_input;

    cin >> king_input >> stone_input >> n;

    king = {'8' - king_input[1], king_input[0] - 'A'};
    stone = {'8' - stone_input[1], stone_input[0] - 'A'};


    for (int i = 0; i < n; ++i) {
        cin >> dir_input;
        move(king.row, king.col, dir_input);
    }


    cout << char(king.col + 'A') << char( 8 - king.row + '0') << "\n";
    cout << char(stone.col + 'A') << char( 8 - stone.row + '0');
}

