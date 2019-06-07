#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
/*
 *  사과를 먹으면 뱀 길이가 늘어남
 *  뱀이 벽 또는 자기자신의 몸과 부딪히면 게임이 끝남
 *  뱀은 맨위 맨좌측(0,0)에 위치, 길이는 1, 오른쪽을 향함
 *
 *  1. 뱀은 몸길이를 늘려, 머리를 다음 칸에 위치
 *  2. 이동한 칸에 사과가 있다면, 사과가 없어지고 꼬리는 움직이지 않아
 *  3. 사과가 없다면, 몸길이를 줄여서 꼬리가 위치한 칸을 비워준다. 즉 몸길이는 변하지 않는다.
 *  --> 사과를 먹어야만 길어지네
 *  게임이 몇 초에 끝나는 지 계산
 *  input
 *      k개의 사과 위치
 *      l개의 뱀의 방향 변환정보 , X초가 끝난 뒤에 c방향으로 이동
 *
 *  box 의 값
 *      0 : 빈공간
 *      1: 사과
 *      2 : 뱀의 몸, 바운더리,
 *
 *  전체 로직
 *  if(time == ans )dque에서 하나를 꺼내 뱀을 이동
 *  현재방향으로 뱀의 몸을 +1 늘림
 *  박스값 확인
 *  1. 사과
 *      사과없애고 진행
 *  2. 빈공간
 *      뱀의 꼬리 부분 칸 이동 => 큐!
 *  3. 2 : 게임오버
 * * */

using namespace std;


struct point{
    int row, col;
};

struct direct{
    int sec;
    char dir;
};

int n, k, t;
int box[102][102];
int dr[] = {0,1,0,-1}; // 좌하우상
int dc[] = {-1,0,1,0};
int ans = 0;
int go_flag = 1;
int cur_dir; // 0 : 좌, 1: 하 , 2: 우 , 3: 상
queue<direct> dque; // 사과위치 저장
queue<point> snake; // 뱀의 좌표를 저장, 맨 앞에 녀석이 꼬리
point tail;
point head;


void Print()
{
    cout << "-----------------"<<endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << box[i][j] << " ";
        }
        cout << endl;
    }
    cout << "head : " << head.row << " , " << head.col <<endl;
    cout << "tail : " << tail.row << " , " << tail.col <<endl;
    cout << "Sec  : " << ans << endl;
    cout << "Dir  : " << cur_dir << endl;

}

bool isBoundary(int r, int c)
{
   return r >=0 && r<n && c>=0 && c<n;
}


int TransDir(char c, int cur)
{
   if(c == 'L') return (cur+1)%4;
   if(c == 'D') return (cur+3)%4;
   return -1;
}
void ChangeDir()
{
    int nextsec = dque.front().sec;
//    cout << "next sec : "  << nextsec << endl;
    if(ans == nextsec){
        char dir = dque.front().dir;
        dque.pop();
        cur_dir = TransDir(dir,cur_dir);
    }
}

void Move()
{
    int nr, nc;
    nr = head.row + dr[cur_dir];
    nc = head.col + dc[cur_dir];
    if(!isBoundary(nr,nc)){
        go_flag = 0;
        return;
    }
    if(box[nr][nc] == 2){ // 머리가 몸통에 닿으면
        go_flag = 0;
        return;
    }
    if(box[nr][nc] == 0){ // 사과가 없으면
        head.row = nr;
        head.col = nc;
        box[nr][nc] = 2;
        snake.push({nr,nc});
        tail.row = snake.front().row;
        tail.col = snake.front().col;
        box[tail.row][tail.col] = 0;
        snake.pop();
        return;
    }
    // 사과가 있다면
    head.row = nr;
    head.col = nc;
    box[nr][nc] = 2;
    snake.push({nr,nc});
    return;

}




int main(){

    int a, b;
    char c;
    cin >> n;
    cin >> k;

    for (int i = 0; i < k; ++i) {
        cin >> a >> b;
        a--;
        b--;
        box[a][b] = 1;
    }

    cin  >> t;
    for (int j = 0; j < t; ++j) {
        cin >> a >>c;
        dque.push({a,c});
    }

    head.row = 0;
    head.col = 0;
    tail.row = 0;
    tail.col = 0;
    cur_dir = 2; // 오른쪽으로 설정;
    box[0][0] = 2;
    snake.push({0,0});

    while(go_flag)
    {
        Move();
        ans++;
//       Print();
        ChangeDir();
    }
    cout << ans << endl;

}

