// ConsoleApplication2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <stack>
#include <map>
#include <set>

using namespace std;

typedef long long ll;

/* 14442 벽 부수고 이동하기 2
 * - 다익스트라로 접근해보자 -- > x
 * - 다익스트라로 풀면 시간 초과 남
 * - 노드사이의 거리가 1일 때는 BFS 사용 가능
 * - BFS에서는 que가 자동으로 거리에 따라 정렬 된 상태이다.
 */

#define MAX_N 68
#define INF 987654321

int n,m,k;
int field[1001][1001];
int dp[11][1001][1001];
struct point{
    int row, col, canBreakCnt;
};
int dr[] = {-1,1,0,0};
int dc[] = {0,0,-1,1};
int ans = INF;

bool isInBoundary(int r, int c){
    return r>=0 and r<n and c>=0 and c<m;
}

void dijkstra(){
    queue<point> que;
    que.push({0, 0, k});
    
    while(!que.empty()){
        int row = que.front().row;
        int col = que.front().col;
        int canBreakCnt = que.front().canBreakCnt;
        int dist = dp[canBreakCnt][row][col];
        que.pop();
        
        if(row == n-1 and col == m-1){
            ans = min(ans, dist);
            continue;
        }

        for (int i = 0; i < 4; ++i) {
            int nr = row + dr[i];
            int nc = col + dc[i];

            if(!isInBoundary(nr,nc))
                continue;

            int nextDist = dist + 1;
            int nextBreakCnt = field[nr][nc] == 0 ? canBreakCnt : canBreakCnt-1;

            if(nextBreakCnt < 0)
                continue;
            if(dp[nextBreakCnt][nr][nc] != INF)
                continue;
            if(nextDist > ans)
                continue;

            que.push({nr, nc, nextBreakCnt});
            dp[nextBreakCnt][nr][nc] = nextDist;
        }
        
    }
    
}


int main() {
    cin >> n >> m >> k;
    char input;

    for (int i = 0; i <= k; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int l = 0; l < m; ++l) {
                dp[i][j][l] = INF;
            }
        }
    }
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> input;
            field[i][j] = input - '0';
        }
    }

    for (int i = 0; i <= k; ++i) {
        dp[i][0][0] = 1;
    }

    dijkstra();
    if(ans == INF)
        ans = -1;

    cout << ans << "\n";
}


