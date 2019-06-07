#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <set>
#include <stack>
using namespace std;

/*
 * 각 숫자는 지형의 높이
 * 1. 가장 높은 봉우리에서 시작
 * 2. 높은지형에서 낮은 지형으로 가로 또는 세로로 연결
 * 3. 딱 한 곳을 정해서 최대 k 깊이만큼 지형을 깍는 공사를 할 수 있다.
 * 만들 수 있는 가장 긴 등산로를 찾아서 이 길이를 출력
 *
 * 탐색은 dfs로! 핵심은 깍을 지형을 정하는 것!
 *
 * 알고리즘
 *  1. 가장 높은 봉우리의 위치를 큐에 저장한다.
 *  2. 큐에서 하나씩 꺼내서 dfs로 탐색, 탐색이 막히면?
 *  방문하지 않은 상하좌우 중 하나를 깎은 다음 탐색 계속
 *  3. 2에서 탐색 길이를 max와 비교
 *  4. dp 배열에 해당 좌표에서 탐색 할 수 있는 길이를 저장!
 *  ---> 이러면 문제가 k를 깍는게 두번 중복 되서 발생할 수 있어....
 *
 * 회고
 *  깍은 후 다시 되돌려 놓는데서 실수가 있었음, 깍은 뒤에 다른 방향을 탐샏하고 있었어...
 *
 *
 */

int t,n,k;
int box[10][10];
int origin[10][10];
int dp[10][10];
int visit[10][10];
struct point{
    int row,col;
};
int dr[] = {-1,1,0,0};
int dc[] = {0,0,-1,1};
queue<point> que;
int ans;

bool isBoundary(int row, int col)
{
    return row>=0 && row < n && col>=0 && col < n;
}

void BeOrigin()
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            box[i][j] = origin[i][j];
        }
    }

}

void DFS(point a, int depth, int kflag){
    visit[a.row][a.col] = 1; // 방문 표시
    for (int i = 0; i < 4; ++i) {
        int nr = a.row + dr[i];
        int nc = a.col + dc[i];
        if(!isBoundary(nr,nc)) continue; // 범위체크
        if(visit[nr][nc]) continue; // 방문체크
        if(box[a.row][a.col] <= box[nr][nc]){ // 등산할 수 없다면
            if(kflag == 1) continue; // 이미 등산로를 놓은 경우 pass
            int iter = k;
            while(iter-- ){ // k~0까지 깍아가면서 재탐색
                box[nr][nc]--;
                if(box[a.row][a.col] > box[nr][nc]){
                    if(box[nr][nc] < 0)
                        box[nr][nc] = 0;
                    else {
                        DFS({nr, nc}, depth + 1, 1);
                    }
                }
            }
            BeOrigin();
            continue;
        }
        DFS({nr,nc}, depth+1,kflag);
    }
    dp[que.front().row][que.front().col] =
            max (dp[que.front().row][que.front().col] , depth);
    ans = max(ans , dp[que.front().row][que.front().col]);
    visit[a.row][a.col] = 0;
//    BeOrigin();
    return;

}

void Print()
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
}

void Init()
{
    ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dp[i][j] = 0;
            visit[i][j] = 0;
        }
    }
}

int main() {

    cin >> t;
    int num = 1;

    while(t--){
        int start = 0;
        cin >> n >> k;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> box[i][j];
                origin[i][j] = box[i][j];
                start = max(start, box[i][j]);
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if(box[i][j] == start)
                    que.push({i,j});
            }
        } // 가장 높은 봉우리 좌표 큐에 저장

        while(!que.empty()){
            DFS(que.front(),1,0);
            que.pop();
        }
//        Print();
        cout <<"#" << num << " " << ans << endl;
        Init();
        num++;
    }
}

