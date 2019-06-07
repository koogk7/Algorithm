#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
/*
 * * */


using namespace std;

struct point{
    int row, col;
};

int n,m;
int box[102][102];
int dr[] = {-1,0,1,0};
int dc[] = {0,-1,0,1};
int dist = 2;
queue<point> que;

bool isBoundary(int r, int c)
{
    return r>=0 && r< n && c>=0 && c<m;
}

void BFS()
{
    int nr , nc;
    int r, c;
    box[0][0] = dist;
    while(!que.empty())
    {
        r = que.front().row;
        c = que.front().col;
        que.pop();
        dist = box[r][c] + 1;
        for (int i = 0; i < 4; ++i) {
            nr = r+ dr[i];
            nc = c+ dc[i];
            if(!isBoundary(nr,nc)) continue;
            if(box[nr][nc] != 1) continue;
            box[nr][nc] = dist;
            que.push({nr,nc});
        }
    }
}



int main(){

    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%1d", &box[i][j]);
        }
    }


    que.push({0,0});
    BFS();

//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < m; ++j) {
//            cout << box[i][j] << "  ";
//        }
//        cout << endl;
//    }

    cout << box[n-1][m-1]-1 <<endl;


}

