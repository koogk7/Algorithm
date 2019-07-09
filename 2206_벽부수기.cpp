// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <queue>
#include <vector>
#include <string.h>
#include <algorithm>
#include <map>
#include <math.h>
using namespace std;


/**
 * 2206번 벽부수기
 *
 * 1:40분 걸림
 *
 *  회고
 * 1. 처음에 DFS로 접근, 최단거리를 구하고 N이 충분히 크다면 BFS로 접근하자.
 * 2. 처음에 설계한 알고리즘이 맞았으나 DFS로 코드를 짜니 시간초과가 뜸
 * 3. 마지막 정답값을 제대로 갱신하지 않아서 틀렸음
 */
 
#define MAX_N 1001
#define MAX_V 123456789
int n,m;
int box[MAX_N][MAX_N];
int dp[MAX_N][MAX_N][2]; // 0 : 없음, 1 : 부술 벽이 있음
int visit[MAX_N][MAX_N][2];
struct point{
    int row, col, remain;
};
int dr[4] = {0, 0, 1, -1};
int dc[4] = {-1, 1, 0, 0};
int ans = MAX_V;
queue<point> que;

bool isBoundary(int row, int col){
    return row<n && row >=0 && col < m && col >= 0;
}

bool isNotWall(int row, int col){
    return box[row][col] == 0;
}

bool canBreakeWall(int row, int col, int remain){
    return box[row][col] == 1 && remain == 1;
}

void Display(int row, int col ,int remain){
    cout << "======================" << endl;
    cout << "row: " << row << " col:" << col << " remain: " << remain << endl;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << "( " << visit[n][m][0] << " , " << visit[n][m][1] << " ) ";
        }
        cout << endl;
    }

}

void BFS(){
    int row, col, remain, dist;
    while(!que.empty()){
        row = que.front().row;
        col = que.front().col;
        remain = que.front().remain;
        que.pop();

//        Display(row,col,remain);

        dist = visit[row][col][remain] + 1;

        for (int i = 0; i < 4; ++i) {
            int nr = row + dr[i];
            int nc = col + dc[i];
            if(!isBoundary(nr, nc)) continue;
            if(visit[nr][nc][remain]) continue;
            if(isNotWall(nr,nc)) {
                visit[nr][nc][remain] = dist;
                que.push({nr,nc,remain});
            }
            if(canBreakeWall(nr, nc, remain)){ ;
                visit[nr][nc][0] = dist;
                que.push({nr,nc,0});
            }
        }
    }
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    char buffer;


    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> buffer;
            box[i][j] = buffer - '0';
            dp[i][j][0] = MAX_V;
            dp[i][j][1] = MAX_V;
        }
    }

    que.push({0,0,1});
    visit[0][0][1] = 1;
    BFS();

    if(visit[n-1][m-1][0] != 0)
        ans = visit[n-1][m-1][0];
    if(visit[n-1][m-1][1] != 0)
        ans = min(ans,visit[n-1][m-1][1]);

    if(ans == MAX_V)
        ans = -1;

    cout << ans;

}

