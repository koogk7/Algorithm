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
 * 도로 복구 작업을 빠른 시간 내에 수행, 도로가 파여진 깊이에 비례해서 복구시간 증가
 * 출발지에서 도착지까지 가는 경로중에 복구시간이 가장 짧은 경로에 대한 총 복구시간을 구하시오
 * 깊이가 1이라면 복구시간은 1
 * ---> 출발지에서 도착지까지 가장 짧은 비용으로 이동해라
 * 그리디하게? 보다 dp 같은데?
 * 점화식 : dp[i][j] = max(dp[i+1][j], dp[i][j+1])
 * 거꾸로 dp를 채워나가자!
 *
 * #1 2
#2 2
#3 8
#4 57
#5 151
#6 257
#7 18
#8 160
#9 414
#10 395

 */

struct point{
    int row, col;
};
int t, n;
int box[102][102];
int visit[102][102];
int dp[102][102]; // i,j 좌표에서 도착지까지 가장 짧은 비용을 저장
int ans;
int head = 1;
queue<point> que;

int dr[] = {-1,1,0,0};
int dc[] = {0,0,-1,1};

bool isBoundary(int row , int col)
{
    return row>=0 && row<n && col>=0 && col<n;
}

void BFS()
{
   int row, col;

    while(!que.empty())
    {
        row = que.front().row;
        col = que.front().col;
        que.pop();

        for (int i = 0; i < 4; ++i) {
            int nr = row + dr[i];
            int nc = col + dc[i];
            if(!isBoundary(nr,nc)) continue;
            if(dp[nr][nc] > dp[row][col] + box[nr][nc]){
                dp[nr][nc] = dp[row][col] + box[nr][nc];
                que.push({nr,nc});
            }
        }
    }
}

int main() {

   cin >> t;

   while(t--){
       ans = 0;
       cin >> n;
       for (int i = 0; i < n; ++i) {
           for (int j = 0; j < n; ++j) {
                scanf("%1d", &box[i][j]);
                dp[i][j] = 10000;
           }
       }
       dp[0][0] = 0;
       que.push({0,0});
       BFS();
       ans = dp[n-1][n-1];
       cout << "#" << head << " " << ans << endl;
       head++;
       for (int i = 0; i <n; ++i) {
           for (int j = 0; j < n; ++j) {
               dp[i][j] = 10000;
           }
       }
   }

}

