#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <queue>

using namespace std;

struct tomato
{
    int x, y, z;
};

int box[101][101][101]; // height , row, col 순
int M,N,H; // col, row , height
int d_col[] = {0, 0,-1 ,1, 0 , 0}; // 좌, 우
int d_row[] = {-1, 1,0 ,0, 0 , 0}; // 상 , 하
int d_height[] = {0, 0,0 ,0, -1, 1}; // 위, 아래
queue<tomato> q;

bool isBoundary(int col, int row , int height)
{
    bool isCol = col >= 0 && col < M;
    bool isRow = row >= 0 && row < N;
    bool isHeight = height >= 0 && height < H;

    return (isCol && isRow && isHeight);
}

void bfs()
{
    int _x, _y , _z;
    int nx, ny, nz; // 탐색할 좌표 위치
    while(!q.empty())
    {
        _x = q.front().x;
        _y = q.front().y;
        _z = q.front().z;
        q.pop();

        for (int i = 0; i < 6; ++i) {
            nx = _x + d_col[i];
            ny = _y + d_row[i];
            nz = _z + d_height[i];

            if(isBoundary(nx,ny,nz) )
            {
//                cout << "Ok Boundary" <<endl;
                if(box[nz][ny][nx] == 0){
                    q.push({nx,ny,nz});
                    box[nz][ny][nx] =  box[_z][_y][_x] + 1;
                }
            }
        }
    }
}


int main()
{
    int rslt = 0;
    cin >> M >> N >> H;

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < M; ++k) {
                scanf("%d", &box[i][j][k]);
                if(box[i][j][k] == 1)
                    q.push({k,j,i});
            }
        }
    }

    bfs();

//    cout << "--------------" <<endl;

    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < M; ++k) {
//                cout << box[i][j][k] << ' ';
                if(box[i][j][k] == 0 ){
                    rslt = -1;
                    cout << rslt << endl;
                    return 0;
                }

                if(rslt < box[i][j][k] ){
                    rslt = box[i][j][k];
                }
            }
//            cout << endl;
        }

//        cout << "--------------" <<endl;
    }

    cout << rslt-1 << endl;


    return 0;
}




