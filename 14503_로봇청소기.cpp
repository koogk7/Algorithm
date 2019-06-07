#include <iostream>
#include <algorithm>
#include <queue>
#include <cmath>


/*
 1. 현재위치를 청소 --- > bfs 돌리기 전에 한번만!
 5. 회전수가 4일 때(네방향 다 확인), 현재방향에서 한칸 후진, 후진 위치와 방향 큐에 삽입
 5. 회전수가 4이고, 뒤쪽 방향이 벽일 때 작동을 멈춤
 2. 왼쪽방향으로 회전
 3. if - 청소하지 않은 공간이라면 전진 후 , 청소처리, 큐에 좌표,방향삽입
 4. else - 청소 할 공간이 아니라면, 큐에 현재좌표와 왼쪽 회전한 방향 삽입, 회전수++

 * 바운더리 함수에서 M이 아닌 N에 대해서만 체크하고 있었다. 이 문제를 찾는데 2~3시간정도 걸림....
 * 저번 안전영역문제에서도 가장 높은 높이-1에 대해 체크를 안하고 있어서 오류를 찾는데 한참걸림
 * ----> 알고리즘에 대해 문제가 없고, 테스트케이스 및 반례가 제대로 동작한다면 체크범위에 대해 다시 한번 검토하자!

 * */

using namespace std;

struct robot{
    int row,col, d; // d는 방향
};

int d_row[] = {-1,0,1,0};// 북 서 남 동
int d_col[] = {0,1,0,-1};
int N,M;
int box[52][52];
int ans = 2; // 정답출력시 -2, box에서 1과 구분되어야함으로 2로 시작
robot robo;
queue<robot> que;



bool isBoundary(int row, int col)
{
    bool isRow = row >= 0 && row < N;
    bool isCol = col >= 0 && col < M;

    return isRow && isCol;
}

void bfs()
{
    int row, col , d;
    int nrow, ncol ,nd;
    int location_cnt = 0;
    int debug = 0;

    while(!que.empty())
    {
        row = que.front().row;
        col = que.front().col;
        d = que.front().d;
        que.pop();

        debug++;

        if(location_cnt == 4) // 네방향 탐색이 완료된 경우
        {
            nd = (d+2)%4; // 후진
            nrow = row + d_row[nd];
            ncol = col + d_col[nd];
            if(!isBoundary(nrow,ncol)) break; // 탐색종료
            if(box[nrow][ncol] == 1) break;
            que.push({nrow,ncol,d}); // 원래 방향 그대로, 후진좌표를 큐에 삽입
            location_cnt = 0; // 회전수 초기화
            continue;
        }
        nd = (d+3)%4; // 왼쪽 회전
        nrow = row + d_row[nd]; // 왼쪽 이동
        ncol = col + d_col[nd]; // 왼쪽 이동

        if(!isBoundary(nrow,ncol)) continue;
        if(box[nrow][ncol] == 0) //청소 가능 구역이라면, 청소처리
        {
            box[nrow][ncol] = ans;
            ans++;
            location_cnt = 0;
            que.push({nrow,ncol,nd});
        }
        else // 청소가 가능한 지역이 아니라면, 왼쪽 회전
        {
            que.push({row,col,nd});
            location_cnt++;
        }
//        --------Print---------------------
//        cout << "Debug : " << debug << " -------------" << endl;
//        cout << "d : " << d << " row : " <<row
//             <<" col : " << col << " location : " << location_cnt << endl;
//        for (int i = 0; i < N; ++i) {
//            for (int j = 0; j < M; ++j) {
//                cout << box[i][j] << "  ";
//            }
//            cout << endl;
//        }

//        if(debug == 20 ) break;


        }
}



int main()
{
    int r,c,d;
    cin >> N >> M;
    cin >> r >> c >> d;
    robo.row = r;
    robo.col = c;
    robo.d = d;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> box[i][j];
        }
    }
    que.push(robo);
    box[r][c] = ans;
    ans++;

    bfs();

//    for (int i = 0; i < N; ++i) {
//        for (int j = 0; j < M; ++j) {
//            cout << box[i][j];
//        }
//        cout << endl;
//    }

    cout << ans-2 << endl;

}