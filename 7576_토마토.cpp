#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <queue>
using namespace std;

struct  tomato {
    int x, y;
};

int m, n ,ans;
int box[1001][1001];
const int dx[] = {-1,0,1,0}, dy[]= {0,1,0,-1};
queue<tomato> q;

bool isInside(int row, int colum)
{
    return (row>=0 && row <n) && (colum >= 0 && colum < m);
}


void bfs()
{
    while(!q.empty()){
        int x = q.front().x, y= q.front().y;
//        cout << "x: " << x << " y: " << y <<endl;
        q.pop();
        for (int i = 0; i < 4; ++i) {
            int nx = x+dx[i];
            int ny = y+dy[i];
            if(isInside(nx,ny) && (box[nx][ny] == 0)){
                box[nx][ny] = box[x][y] + 1; // depth 표시
                q.push({nx,ny});
            }
        }
    }

}





int main()
{

    cin >> m >> n;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &box[i][j]);
            if(box[i][j] == 1){
                q.push({i,j});
            }
        }
    }

    bfs();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if(box[i][j] == 0){
                cout << "-1" << endl;
                return 0;
            }
            if( ans < box[i][j]) ans = box[i][j];
        }

    }

    cout << ans-1 << endl;
    return 0;
}




