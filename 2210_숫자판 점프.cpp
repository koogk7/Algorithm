#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <stack>
#include <map>
#include <set>

typedef long long ll;


#define MAX_N 68
#define INF 987654321



using namespace std;

/* 2210 숫자판 점프
 *
 * 회고
 *  - 난이도 하
 *  - 시간 복잡도 5 * 5 * 4^5
 *
 */

int field[5][5];
int dr[4] = {0,0,-1,1};
int dc[4] = {1,-1,0,0};
set<int> nums;

bool isBoundary(int r, int c){
    return r >= 0 && r < 5 &&  c >= 0 && c < 5;
}

int getDigit(int depth){
    int ret = 1;
    while(depth--){
        ret *= 10;
    }
    return ret;
}

void BackTracking(int row, int col, int depth, int num) {
    if(depth == 6){
        nums.insert(num);
        return;
    }

    int digit = getDigit(depth);

    for (int i = 0; i < 4; ++i) {
        int nr = dr[i] + row;
        int nc = dc[i] + col;
        if(!isBoundary(nr,nc)) continue;
        BackTracking(nr,nc,depth+1,num + digit*field[row][col]);
    }

    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            cin >> field[i][j];
        }
    }

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            BackTracking(i,j,0,0);
        }
    }

    cout << nums.size();

}










