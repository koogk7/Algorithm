#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <stack>
#include <map>
#include <set>
#include <math.h>

typedef long long ll;


#define MAX_N 68
#define INF 987654321



using namespace std;

/* 14500 테트로미노
 * 난이도 : 중
 * 시간 : 40분
 *
 * 회고
 * 1. 처음에 테트로미노를 한개만 놓는다는 문구를 놓쳐, 어렵게 접근
 * 2. DP로 접근이 가능 할 거라는 생각이 들었음
 *    2-1. [row][col][depth]로 접근하게 되면 중복방문 문제가 생김
 * 3. ㅗ 모양은 단순히 dfs 4번으로 안됨, 방향이 바뀌기 때문에! 따라서 따로 예외 처리를 해줘야함:
 */

int n,m;
int field[501][501];
int cache[501][501][4];
int visit[501][501];
int dr[4] = {1,-1,0,0};
int dc[4] = {0,0,-1,1};

bool isIn(int r, int c){
    return r >= 0 and r < n and c>=0 and c < m;
}

int specialCase(int row, int col){
    priority_queue<int> pq;
    int ret = field[row][col];

    for (int i = 0; i < 4; ++i) {
        int nr = row + dr[i];
        int nc = col + dc[i];
        if(!isIn(nr,nc)) continue;
        pq.push(field[nr][nc]);
    }

    for (int j = 0; j < 3; ++j) {
        if(pq.empty()) continue;
        ret += pq.top();
        pq.pop();
    }

    return ret;

}

int bt(int row ,int col, int depth) { // ㅗ를 제외한 나머지 테트로미노
    if(depth == 4)
        return 0;
//    int &ret = cache[row][col][depth];
    int ret = 0;
    visit[row][col] = true;

    for (int i = 0; i < 4; ++i) {
        int nr = row + dr[i];
        int nc = col + dc[i];
        if(!isIn(nr,nc)) continue;
        if(visit[nr][nc]) continue;
        ret = max(ret, bt(nr,nc,depth+1) + field[row][col]);
    }

    visit[row][col] = false;
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> field[i][j];
        }
    }

    int ans = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if( i == 1 and j == 0 )
                cout << "";
            ans = max(ans, bt(i,j,0));
            ans = max(ans, specialCase(i,j));
        }
    }
    cout << ans;
}









