#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


/*
	1. 가장자리에 위치한 코어는 전원이 연결되어 있음
	2. 코어에서 바운더리에 연결하면 전원이 흐름
	3. 전선은 겹쳐서는 안됨
	4. 최대한 많은 CORE에 전원을 연결, 길이가 최소가 되도록

	하나의 코어가 선택 할 수 있는 경우의 수는 4가지
	허나 4^12 > 2^24 = 1000 * 1000 * 16 충분

    회고
        코어 갯수가 더많을 때 갱신을 잘 못해서 계속 49개에서 틀렸었음, 반례케이스 생각 잘하자!
        이 문제는 전역변수에 솔루션 구조체를 선언에해서, 리턴할 때 구조체 값을 갱신하는 방법으로 해결함
*/
#define MA 100000000
int T;
int n;
int map[14][14];
int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };
struct point {
    int row, col;
};
struct sol{
    int cnt, lcnt;
};
sol solve;
vector<point> core;
int cidx;

bool isBoundary(int r, int c)
{
    return r >= 0 && r < n && c >= 0 && c < n;
}

void Display()
{
    cout << "-----------------------------" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}

bool isPut(int row, int col, int dir) {

    int nr = row;
    int nc = col;
    while (1) {
        nr += dr[dir];
        nc += dc[dir];
        if (!isBoundary(nr, nc)) return true;
        if (map[nr][nc] != 0) return false;
    }
}

int PutLine(int row, int col, int dir, int value) {

    int nr = row;
    int nc = col;
    int cnt = 0;
    while (1) {
        nr += dr[dir];
        nc += dc[dir];
        if (!isBoundary(nr, nc)) break;
        map[nr][nc] = value;
        cnt++;
    }

    return cnt;
}


int BackTracking(int idx, int ccnt, int lcnt) {

    if (idx == cidx) {
        if(solve.cnt < ccnt){
            solve.cnt = ccnt;
            solve.lcnt = lcnt;
        }
        if(solve.cnt == ccnt){
            solve.lcnt = min(solve.lcnt,lcnt);
        }
        return MA;
    }
    int ret = MA;

    if (core[idx].row == n - 1 || core[idx].col == n - 1
        || core[idx].row == 0 || core[idx].col == 0) {
        ret = BackTracking(idx + 1, ccnt + 1, lcnt);
        return ret;
    }

    int row = core[idx].row;
    int col = core[idx].col;


    for (int i = 0; i < 4; i++)
    {
        int nr = row;
        int nc = col;
        if (!isPut(nr, nc, i)) continue;
        int nlcnt = lcnt + PutLine(nr, nc, i,2);
        ret = min(ret, BackTracking(idx + 1, ccnt + 1, nlcnt));
        PutLine(nr, nc, i, 0);
    }
    ret = min(ret, BackTracking(idx + 1, ccnt, lcnt));


    return ret;

}

int main()
{
    cin >> T;

    for (int t = 0; t < T; t++)
    {
        cin >> n;
        core = vector<point>(12);
        cidx = 0;
        solve = {0,MA};
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> map[i][j];
                if (map[i][j] == 1) {
                    core[cidx++] = { i,j };
                }
            }
        }
        int ans =  BackTracking(0, 0, 0);
        if (ans == MA) ans = 0;
        cout <<"#"<< t+1 << " " <<solve.lcnt << endl;
    }
}