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
typedef long long ll;

/*
 * 3085 사탕게임
 * 사탕의 색은 모두 같지 않을 수도 있다.
 * 사탕의 색이 다른 인접한 두칸을 고르고, 교환한다.
 * 모두 같은 색으로 이루어져 있는 가장 긴 수열(행 또는 열)을 고른 후 먹는다.
 * N = 250
 *
 * 회고
 *  - 생각보다 더 간단한 문제다. 상하좌우 swap 해주고 swap때마다 col, row를 검사하면된다. 쉬운 문제는 쉽게 가자
 *  - 하우, 두방향에 대해서만 검사를 진행해서 계속 오답이 났다.
 *  
 */

char box[51][51];
bool visit[51][51];
int n;
int dr[] = {1,0,-1,0};
int dc[] = {0,1,0,-1};

bool isBoundary(int r, int c){
    return r >= 0 and r < n and c >= 0 and c < n;
}

int dfs(int row, int col, int dir, char value, bool canChange, int depth){
    if(!isBoundary(row,col))
        return depth;

    int rst = depth;
    int nr = row + dr[dir];
    int nc = col + dc[dir];

    visit[row][col] = true;

    if(box[row][col] != value and canChange){
        for (int i = 0; i < 4; ++i) {
            int swap_row = row + dr[i];
            int swap_col = col + dc[i];
            if(!isBoundary(swap_row,swap_col)) continue;
            if(visit[swap_row][swap_col]) continue;
            if(box[swap_row][swap_col] != value) continue;
            char temp = box[swap_row][swap_col];
            box[swap_row][swap_col] = box[row][col];
            rst = max(rst, dfs(nr,nc,dir,value,false,depth+1));
            box[swap_row][swap_col] = temp;
        }
    } else if(box[row][col] == value) {
        rst = dfs(nr,nc,dir,value,canChange,depth+1);
    }

    visit[row][col] = false;
    return rst;
}

int main(){
    cin >> n;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> box[i][j];
        }
    }

    int ans = 1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < 4; ++k) {
                ans = max(ans, dfs(i,j,k,box[i][j], true, 0));
            }
        }
    }


    cout << ans;
    // 교환 dfs
    // 수열찾기 -- > O(2n)
}

