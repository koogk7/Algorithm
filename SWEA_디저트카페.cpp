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
 * 디저트카페
 *  카페들 사이에는 대각선 방향으로 움직일 수 있는 길이 있다
 *  디저트 카페투어는 어느 한 카페에서 출발하여 대각선 방향으로 움직이고
 *  사각형 모양을 그리며 출발한 카페로 돌아와야한다. 또한 같은 종류의 디저트는 방문하지 않는다.
 *  하나의 카페에서 디저트를 먹는 것도 안 된다.
 *  왔던 길 을 다시 돌아가는 것도 안된다.
 *  디저트를 가장 많이 먹을 수 있는 경로를 찾고 디저트 수를 출력, 먹을 수 없는 경우 -1 출력
 *
 *  N * N = 400
 *
 *
 */

int T;
int n;
int road[21][21];
int dr[4] = {1,  1, -1, -1};
int dc[4] = {1, -1, -1,  1};
bool visit[101];
int start_row, start_col;

bool isInBoudary(int row, int col){
    return row >= 0 and row < n and col >= 0 and col < n;
}

int dfs(int row, int col, int cnt, int d){
    if(!isInBoudary(row,col))
        return 0;
    if(d > 3)
        return 0;
    if(row == start_row and col == start_col)
        return cnt;


    int ret = 0;
    int desert = road[row][col];

    if(visit[desert])
        return 0;

    // 방향을 꺽는 경우, 안 꺽는 경우
    visit[desert] = true;
    ret = dfs(row + dr[d], col + dc[d], cnt+1, d);

    if(d < 3)
        ret = max(ret, dfs(row + dr[d+1], col + dc[d+1], cnt+1, d+1));

    visit[desert] = false;
    return ret;
}

int main(){
    cin >> T;

    for (int t = 1; t <= T; ++t) {
        cin >> n;
        int ans = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> road[i][j];
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                // 각점에서 투어, 디저트 종류 리
                start_row = i;
                start_col = j;
                int desert = road[i][j];

                visit[desert] = true;
                ans = max(ans, dfs(i+dr[0],j+dc[0],1,0));
                visit[desert] = false;
            }
        }

        if(ans < 4)
            ans = -1;

        cout << "#" << t << " " << ans << "\n";

    }

}

