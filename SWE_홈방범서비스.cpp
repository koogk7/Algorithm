#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <set>


using namespace std;

/*
 * 운영비용은 서비스 영역의 면적과 동일
 * 운영 비용 = K * K + (K - 1) * (K - 1)
 * 방범 서비스를 제공받는 집에서는 M의 비용을 지불
 * 회사는 손해를 보지 않고, 가장 많은 집들에게 제공하는 서비스 영역을 찾고자 한다.
 * 이때 제공받는 집의 수를 구하여라
 *
 * 조건 : 운영비용 - 총 지불 비용 <= 0
 *
 * 별 다른 규칙은 없는 거같은데? 완전탐색?
 * box의 최대 크기는 400,
 *
 * 탐색 어떻게?
 *      1. 집의 좌표를 큐에 넣는다
 *      2. 해당 집에 대해서 서비스 영역을 확장해보자
 *      3. K의 범위는? 20 --> 하나의 집에 대해서 20번 돌아
 *         총 탐색 횟수는 400*20 = 8000 충분!
 *
 * 중복된 탐색이 있는가? 좌표가 바뀔 때마다 서비스 영역은 무조건 달라진다.
 *
 * 가지치기 조건
 *      1. box 범위 벗어나면 탈락
 *      2. 운영비용이 손해면 탈락
 *      3. k가 1일 때는 검사하지 않는다.
 *
 * 서비스영역 확장은 어떻게?
 *      1. BFS로! k 만큼의 깊이 들어가서 상하좌우 탐색
 *
 * 필요한 함수
 *      1. 운영이익 계산하는 함수
 *      2. depth k만큼 bfs 탐색하는 함수
 *      3. boundary check
 *
 *
 * */

struct point {
    int row, col;
};
int t;
int n, m; // 도시의 크기, 하나의 집이 지불하는 비용
int box[22][22];
int visit[22][22];
queue<point> house; // 집들의 좌표를 저장.
queue<point> que; // BFS를 위한 큐
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};
int ans;


void Print() {
//    cout << "-----Visit---------" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << visit[i][j] << " ";
        }
        cout << endl;
    }
}

bool isBoundary(int row, int col) {
    return row >= 0 && row < n && col >= 0 && col < n;
}

bool isNotCost(int k, int profit) {
    return (k * k + (k - 1) * (k - 1) - profit) <= 0;
}

int getCost(int k) {
    return k * k + (k - 1) * (k - 1);
}

int initVisit() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            visit[i][j] = 0;
        }
    }
}


int BFS() {
    int k = 0;
    while (!que.empty()) {
        int row = que.front().row;
        int col = que.front().col;
        que.pop();
        int depth = visit[row][col] + 1;
        k = max(depth, k);
        for (int i = 0; i < 4; ++i) {
            int nrow = row + dr[i];
            int ncol = col + dc[i];
            if (!isBoundary(nrow, ncol)) continue;
            if (visit[nrow][ncol]) continue;
            visit[nrow][ncol] = depth;
            que.push({nrow, ncol});
        }
    }

    return k;
}

int getProfit(int k) {
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (visit[i][j] <= k && box[i][j] == 1)
                cnt++;
        }
    }
//    cout << "Profit : " << cnt * m << endl;
    return cnt * m;
}


int main() {
    int index =1;
    cin >> t;
    while (t--) {
        ans = 0;
        cin >> n >> m;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> box[i][j];
                if (box[i][j] == 1)
                    house.push({i, j});
            }
        }
        int max_profit = house.size() * m;

        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                que.push({r, c});
                visit[r][c] = 1;
                int k = BFS();
                for (int i = 2; i < k; ++i) {
                    int profit = getProfit(i);
                    int cost = getCost(i);
                    if (cost > max_profit) break;
                    if (!isNotCost(i, profit)) continue;
                    ans = max(ans, profit / m);
                }
                initVisit();
            }
        }
        cout <<"#" <<index << " "<< ans << endl;
        index++;
    }



}

