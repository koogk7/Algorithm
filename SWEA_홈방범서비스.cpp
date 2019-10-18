// ConsoleApplication2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*
홈방범 서비스는 마름모 모양의 영역에서만 제공
서비스 영역의 크기 K가 커질수록 운영비용이 커짐
운용비용은 서비스 영역의 면적과 동일
운용비용 = k*k + (k-1) * (k-1)

도시의 크기 N과 하나의 집이 지불 할 수 있는 비용 m
손해를 보지 않으면서 홈방범 서비스를 가장 많은 집들에게 제공하는 서비스 영역을 찾고 그때의 서비스를 받는 집 수 출력

2*(k-1) + 1 < n 까지 검사
마름모 검사를 어떻게?

dist가 k-2까지만 4방향 방문

*/
#define INF 987654321

int T, n, m;
int box[22][22];
int origin[22][22];
int visit[22][22];
int dr[4] = { -1,0,1,0 };
int dc[4] = { 0,-1,0,1 };
struct point {
    int row, col;
};
queue<point> endQue;

void display()
{
    cout << "=====================" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << visit[i][j] << " ";
        }
        cout << endl;
    }
}

void initVisit() {
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            visit[i][j] = 0;
            box[i][j] = origin[i][j];
        }
    }
}

bool isIn(int r, int c) {
    return r >= 0 and r < n and c >= 0 and c < n;
}

int getCost(int k) {
    return k * k + (k - 1) * (k - 1);
}


int BFS(point start, int k) {

    queue<point> que;
    int house_cnt = 0;

    if (!visit[start.row][start.col] and box[start.row][start.col] == 1) {
        house_cnt++;
        box[start.row][start.col] = 0;
    }


    que.push(start);
    visit[start.row][start.col] = 1;

    while (!endQue.empty()) {
        que.push(endQue.front());
        endQue.pop();
    }

    while (!que.empty()) {
        int row = que.front().row;
        int col = que.front().col;
        int dist = visit[row][col];
        que.pop();

        if (dist == k) {
            endQue.push({ row,col });
            continue;
        }


        for (int i = 0; i < 4; i++)
        {
            int nr = row + dr[i];
            int nc = col + dc[i];

            if (!isIn(nr, nc))
                continue;
            if (visit[nr][nc])
                continue;

            if (box[nr][nc] == 1) {
                house_cnt++;
                box[nr][nc]--;
            }

            que.push({ nr,nc });
            visit[nr][nc] = dist + 1;

        }

    }

    return house_cnt;

}


int main() {

    cin >> T;

    for (int t = 1; t <= T; t++) {
        int ans = 0;

        cin >> n >> m;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> box[i][j];
                origin[i][j] = box[i][j];
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                initVisit();
                int house_cnt = 0;
                if (i == 0 and j == 1)
                    cout << "";
                for (int k = 1; k <= n + 1; k++) {
                    house_cnt += BFS({i, j}, k);
                    int this_profit = house_cnt * m - getCost(k);
                    if (0 <= this_profit) {
                        ans = max(ans, house_cnt);
                    }
                }

                while (!endQue.empty()) {
                    endQue.pop();
                }
            }
        }

        cout << "#" << t << " " << ans << endl;

    }

}


