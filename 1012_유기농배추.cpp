// ConsoleApplication2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <stack>
#include <map>

using namespace std;

typedef long long ll;


#define MAX_N 68
#define INF 123456789123


int T, n, m,k;
struct point {
    int row, col;
};
int field[51][51];
bool visit[51][51];
vector<point> cabbages;
int dr[] = {-1,1,0,0};
int dc[] = {0,0,-1,1};

bool isBoundary(int r, int c){
    return r >= 0 and r < n and c >= 0 and c < m;
}

int BFS(int startRow, int startCol){
    if(visit[startRow][startCol])
        return 0;

    queue<point> que;
    que.push({startRow, startCol});
    visit[startRow][startCol] = true;

    while(!que.empty()){
        int row = que.front().row;
        int col = que.front().col;
        que.pop();

        for (int i = 0; i < 4; ++i) {
            int nr = row + dr[i];
            int nc = col + dc[i];

            if(!isBoundary(nr,nc))
                continue;
            if(visit[nr][nc])
                continue;
            if(!field[nr][nc])
                continue;

            que.push({nr,nc});
            visit[nr][nc] = true;
        }
    }

    return 1;

}

int main() {
    cin >> T;

    for (int t = 0; t < T; ++t) {
        cin >> n >> m >> k;

        int ans = 0;
        memset(field, 0, sizeof(field));
        memset(visit, 0, sizeof(visit));
        cabbages = vector<point>(k);

        for (int i = 0; i < k; ++i) {
            int inputRow, inputCol;
            cin >> inputRow >> inputCol;
            field[inputRow][inputCol] = 1;
            cabbages[i] = {inputRow, inputCol};
        }

        for (int i = 0; i < k; ++i) {
            ans += BFS(cabbages[i].row, cabbages[i].col);
        }

        cout << ans << "\n";

    }
}


