// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <iostream>
#include <queue>
#include <vector>
#include <string.h>
#include <algorithm>
#include <map>
#include <math.h>
#include <stack>
#include <set>
#include <sstream>
#include <string.h>
using namespace std;
typedef long long ll;

/*
 * 16326 아기상어
 * 물고기 m, 상어 1마리, 한칸에는 물고기가 최대 1마리 존재
 * 아기상어의 크기는 2, 1초에 상하좌우 이동
 * 아기상어는 자기보다 큰 물고기를 지나갈 수 없다.
 * 아기상어는 자기보다 작은 물고기만 먹을 수 있다
 * 같은 크기는 지나만 갈 수 있다.
 * 이동
 *  - 더 이상 먹을 수 있는 물고기가 없으면 끝
 *  - 가장 가까운 물고기를 먹으러감
 *  - 상좌 순으로 탐색함
 *  자신의 크기와 같은 수의 물고기를 먹을 때마다 크기 1증가
 * N = 400
 *
 * 회고
 *  아기상어 먹이 탐색시 먹이를 찾자말자 탐색을 끝내면 안됨, 먹이를 찾았을 때 큐에 들어있는 녀석들은 탐색해야한다.
 *  저번에 푼 코드와 차이점은 후보군을 이번에는 우선순위 큐에 넣었다. 그러나 저번 코드는 단일책임을 잘 가지게 코드를
 *  잤다는 점에서, 저번 코드가 더 좋은 것 같다.
 *
 */

int sea[21][21];
int visit[21][21];
struct Shark{
    int row,col,age,exp;
};
int dr[] = {-1,0,0,1};
int dc[] = {0,-1,1,0};
int n;
int ans;
Shark baby;

struct cmp{
    bool operator()(Shark a, Shark b){
        if(a.age == b.age){
            if(a.row == b.row)
                return a.col > b.col;
            return a.row > b.row;
        }
        return a.age > b.age;
    }
};

bool isBoundary(int r, int c){
    return r >=0 and r < n and c >= 0 and c < n;
}

void Display(){
    cout << "========================" << "\n";
    cout << "age : "<< baby.age << " exp : " << baby.exp << "\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << sea[i][j] << " ";
        }
        cout << endl;
    }
}

int BFS(){
    queue<Shark> que;
    priority_queue<Shark, vector<Shark>, cmp> candi_shark;
    que.push(baby);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            visit[i][j] = 0;
        }
    }

    visit[baby.row][baby.col] = 1;

    while(!que.empty()){
        int row = que.front().row;
        int col = que.front().col;
        int dist = visit[row][col];
        que.pop();

        for (int i = 0; i < 4; ++i) {
            int nr = row + dr[i];
            int nc = col + dc[i];
            if(!isBoundary(nr,nc)) continue;
            if(visit[nr][nc]) continue;
            if(sea[nr][nc] > baby.age) continue;
            if(sea[nr][nc] == baby.age or sea[nr][nc] == 0){
                que.push({nr,nc,dist+1,0});
                visit[nr][nc] = dist + 1;
            } else{ // 먹을 수 있음
                candi_shark.push({nr,nc,dist+1,0});
                visit[nr][nc] = dist+1;
            }
        }
    }

    if(candi_shark.empty())
        return -1;

    Shark next_shark = candi_shark.top();
    sea[baby.row][baby.col] = 0;
    sea[next_shark.row][next_shark.col] = 9;
    baby.exp++;
    if(baby.exp == baby.age){
        baby.age++;
        baby.exp = 0;
    }
    baby = {next_shark.row,next_shark.col, baby.age, baby.exp};
    ans += visit[next_shark.row][next_shark.col] - 1;
    return 1;

}


int main(){
    cin >> n;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> sea[i][j];
            if(sea[i][j] == 9){
                baby = {i,j,2,0};
            }
        }
    }
    while(BFS() != -1);
    cout << ans << "\n";
        // 1.먹이탐색 --> BFS
        // 2.상어좌표이동
        // 3.탐색 실패까지 1번 반복


}

