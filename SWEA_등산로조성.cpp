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
#define INF 9876543210
/*
 * 등산로 조성
 *  1. 등산로는 가장 높은 봉우리에서 시작
 *  2. 높은 지형에서 낮은 지형으로 가로 또는 세로 방향으로 연결
 *  3. 딱 한 곳을 정해서 최대 K 깊이만큼 지형을 깎는 공사를 할 수 있다.
 * N * N = 64
 * K = 5
 * 가장 높은 봉우리는 최대 5개
 * 지형을 깎아 높이를 1보다 작게 만드는 것도 가
 */

int T;
int n,k;
struct Point{
    int row, col;
};
queue<Point> starts;
int road[9][9];
bool visit[9][9];
int dr[] = {-1,1,0,0};
int dc[] = {0,0,-1,1};

bool isInBoudary(int row, int col){
    return row >= 0 and row < n and col >= 0 and col < n;
}

void init(){
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            visit[i][j] = 0;
        }
    }
}

void Display(int idx){
    cout << "======= "<< idx  <<" =======" << "\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << visit[i][j] << " ";
        }
        cout << endl;
    }
}

int dfs(int row, int col, bool canDig, int before){

    if(!isInBoudary(row,col)) // 범위 이탈
        return 0;

    int ret = 0;

    if(visit[row][col]) // 방문노드
        return 0;

    if(before <= road[row][col]) {
            return 0;
    }// 탐색 불가


    visit[row][col] = true;

    for (int i = 0; i < 4; ++i) { // 땅을 안 팠을 때
        int nr = row + dr[i];
        int nc = col + dc[i];
        ret = max(ret, dfs(nr,nc,canDig, road[row][col]) + 1);
    }

    if(canDig){

        for (int i = 0; i < 4; ++i) {
            int nr = row + dr[i];
            int nc = col + dc[i];

            if(!isInBoudary(nr,nc))
                continue;

            for (int j = 1; j <= k; ++j) {
                road[nr][nc] -= j;
                ret = max(ret, dfs(nr, nc, false, road[row][col]) + 1);
                road[nr][nc] += j;
            }
        }

    }


    visit[row][col] = false;
    ret = max(ret, 1);

    return ret;

}


int main(){
   cin >> T;

    for (int t = 1; t <= T; ++t) {
        cin >> n >> k;

        starts = queue<Point>();
        int start = 0;
        int ans = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> road[i][j];
                start = max(start,road[i][j]);
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if(road[i][j] == start)
                    starts.push({i,j});
            }
        }


        while(!starts.empty()){
            int row = starts.front().row;
            int col = starts.front().col;
            starts.pop();
            ans = max(ans, dfs(row,col, true, INF));
            ans = max(ans, dfs(row,col, false, INF));

        }

        cout << "#" <<t << " " <<ans << "\n";

    }

}

