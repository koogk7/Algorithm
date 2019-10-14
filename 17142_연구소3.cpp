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
#define INF 987654321
/*
 * 17142 연구소 3
 *
 * 바이러스는 활성과 비활성이 있음
 * 처음에는 모두 비활성 상태, 활성 상태인 바이러스는 상하좌우로 빈칸으로 복제되며 1가 걸림
 * 연구소의 바이러스 M개를 활성 상태로 변경할려고 한다.
 *
 * 1. 바이러스 k개 중 m개를 활성상태로 바꾼다. 10 C 1 --> 완탐가능, 10! = 4 * 10^6
 * 2. BFS를 통해 바이러스 감염 시작 --> N*N = 2500 * 10! == 10 ^9...
 * 3. 모든 칸이 바이러스 인지 확인
 */

int n;
int m;
int lab[51][51];
int visit[51][51];
struct Virus {
    int row, col;
};
vector<Virus> viruses;
vector<int> sel;
int dr[] = {-1,1,0,0};
int dc[] = {0,0,-1,1};

void init(){
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            visit[i][j] = 0;
        }
    }
}

void Display(){
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << visit[i][j] << " ";
        }
        cout << endl;
    }
}

bool isInBoundary(int row, int col){
    return row>=0 and row < n and col >= 0 and col < n;
}

int getAllTime(){

    int ret = 1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if(lab[i][j] == 0 and visit[i][j] == 0)
                return INF;
            if(lab[i][j] == 0)
                ret = max(ret, visit[i][j]);
        }
    }


    return ret - 1;
}

void BFS(){

    queue<Virus> que;

    init();
    for (int i = 0; i < m; ++i) {
        int idx = sel[i];
        int row = viruses[idx].row;
        int col = viruses[idx].col;
        que.push(viruses[idx]);
        visit[row][col] = 1;
    }

    while(!que.empty()){
        int row = que.front().row;
        int col = que.front().col;
        que.pop();

        for (int i = 0; i < 4; ++i) {
            int nr = row + dr[i];
            int nc = col + dc[i];

            if(!isInBoundary(nr,nc))
                continue;
            if(lab[nr][nc] == 1) // 벽
                continue;
            if(visit[nr][nc])
                continue;

            que.push({nr,nc});
            visit[nr][nc]= visit[row][col] + 1;
        }
    }


}

int combi(int idx, int cnt){
    if(cnt == m){
        BFS();
        return getAllTime();
    }

    if(idx >= viruses.size())
        return INF;

    int ret;

    sel.push_back(idx);
    ret = combi(idx+1, cnt+1);
    sel.pop_back();

    ret = min(ret, combi(idx+1, cnt));

    return ret;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> lab[i][j];
            if(lab[i][j] == 2)
                viruses.push_back({i,j});
        }
    }

    int ans = combi(0,0);
    if(ans == INF)
        ans = -1;
    cout << ans << endl;


}

