#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

/*
 * 같은 색 뿌요가 4개 이상 하좌우로 연결되어 있으면 같은색 뿌요들이 없어짐
 * 없어진 뿌요 위에 다른 뿌요가 있다면 차례대로 아래로 떨어짐
 * 한번 터지는 걸 1 연쇄
 *
 * 터지는걸 확인하는 방법은 DFS
 * 터진 후 이동은? visit
 *
 */

char box[13][8];
bool visit[13][8];
struct point {
    int row, col;
};
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};
queue<point> start;
int ans;

bool isBoundary(int row, int col) {
    return row >= 0 && row < 13 && col >= 0 && col < 6;
}

void DisplayBox() {
    cout << "-------Box-----------" << endl;
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 6; ++j) {
            cout << box[i][j] << " ";
        }
        cout << endl;
    }
}

void DisplayVis() {
    cout << "-------visit-----------" << endl;
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 6; ++j) {
            cout << visit[i][j] << " ";
        }
        cout << endl;
    }
}

int isPop(point a, char color, queue<point> &q) {
    if (!isBoundary(a.row, a.col)) return -1;
    if (visit[a.row][a.col]) return -1;
    if (box[a.row][a.col] == '.') return -1;
    if (box[a.row][a.col] != color) {
//        cout << a.row << "," << a.col << endl;
//        DisplayVis();
        // if(qsize > 3)
        // Move 함수
        return 1;
    }
    int ret = -1;
    visit[a.row][a.col] = 1;
    q.push(a);
    for (int i = 0; i < 4; ++i) {
        int nr = a.row + dr[i];
        int nc = a.col + dc[i];
        ret = max(ret, isPop({nr, nc}, color, q));
    }
    return ret;

}

void Move() {
    for (int row = 11; row > 0; --row) {
        for (int col = 0; col < 6; ++col) {
            if (box[row][col] != '.') continue;
            if (box[row - 1][col] == '.')continue;
            int irow = row;
            while (irow < 12 && box[irow][col] == '.') {
                irow++;
            }
            irow--;
            box[irow][col] = box[row - 1][col];
            box[row - 1][col] = '.';
        }
    }
}


int main() {
    int start_idx = 0;
    point start;
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 6; ++j) {
            cin >> box[i][j];
            if (box[i][j] != '.' && start_idx == 0) {
                start = {i, j};
                start_idx = 1;
            }
        }
    }

    while (1) {
        int csize = 0;
        for (int i = 0; i < 12; ++i) {
            for (int j = 0; j < 6; ++j) {
                if (box[i][j] == '.') continue;
                point a = {i, j};
                char color = box[a.row][a.col];
                queue<point> q;
                isPop(a, color, q);
                int qsize = q.size();
                while (!q.empty()) { // 연쇄
                    int row = q.front().row;
                    int col = q.front().col;
                    q.pop();
                    if (qsize > 3)
                        box[row][col] = '.';
                    visit[row][col] = 0;
                }
                csize = max(csize, qsize);
            }
        }
        if (csize > 3) {
            Move();
            ans++;
        }
       else
            break;
    }

    cout << ans << endl;

    return 0;
}
