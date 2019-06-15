// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <queue>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;


/**
 * 1937번 욕심쟁이 판다
 *
 *  회고
 *  1. 처음에 BFS로 짤려고 했으나, 터미널 노드의 값을 연달아 받아야함으로 DFS로 바꿈
 *  2. DP의미를 초반에 잘못 설정함, DP[K]는 K로부터 "시작"하는 최대생존일임!
 *  3. DP갱신을 매 return때마다 day만큼 해줘서 고생했음, DP[K]는 K로부터 "시작"하는 최대생존일
 *  이기때문에 지금까지 더해져왔던 day를 빼주고 값을 넣어줘야함! 반면 리턴값은 day를 더한채로 넣어줘야함!
 *  4. for문 돌때 시작하는 날짜 dp를 미리 저장해놓고 0으로 세팅해준 다음 시작해야 조건에 걸리지 않음!
 */


int n;
int map[501][501];
int dp[501][501];
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,-1,1};
int ans;
struct point {
    int row, col;
};

bool isBoundary(int r, int c){
    return r < n && r >= 0 && c < n && c >= 0;
}

int DFS(point cur, int day, int before){
    if(!isBoundary(cur.row, cur.col)) return day;
    if(map[cur.row][cur.col] <= before)
        return day;
    int &rst = dp[cur.row][cur.col];

    if(rst != 0)
        return rst + day;


    for (int i = 0; i < 4; ++i) {
        int nr = cur.row + dr[i];
        int nc = cur.col + dc[i];
        rst = max(rst,DFS({nr,nc}, day+1, map[cur.row][cur.col]) - day);
    }

    return rst + day;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> map[i][j];
        }
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            int start = dp[k][i];
            dp[k][i] = 0;
            start = max(start, DFS({k,i},0,-1));
            dp[k][i] = start;
            ans = max(ans,start);
        }
    }


    cout << ans << endl;

}

