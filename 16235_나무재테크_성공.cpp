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

/* 16235 나무 재테크
 *
 * 모든 나무의 위치를 우선순위 큐에 저장함, 우선순위 큐는 삽입의 시간복잡도가 logN
 * 나무의 나이가 겹치는 녀석끼리만 정렬해야함, 그러지 않아서 시간초과남
 * 잘 생각해보면 정렬이 필요하지 않다. 한번 정해진 나이의 순서들은 변하지 않기때문!
 * 단 새로생긴 나무들은 나이가 1이므로 이 녀석만 앞에 넣어주면된다 --- > Deque
 *
 *
 * 봄
 * - 나무가 나이만큼 양분을 먹고 나이가 +1 증가, 하나의 칸에 여러개의 나무가 있다면 나이가 어린 나무부터!
 * - 양분을 먹지못하면 사망
 *
 * 여름
 * - 봄에 죽은나무가 양분으로 변함, 나이를 2로 나눈 값이 양분이 됨
 *
 * 가을
 * - 번식, 나이가 5의 배수일때만!, 인접한 8개의 칸에 나이가 1인 나무가 생김
 *
 * 겨울
 * - 입력만큼 양분추가
 *
 * K년이 지난 후 살아있는 나무의 갯수를 구하라
 *
 */

int n,m,k;
int field[11][11];
int food[11][11];

struct Tree{
    int row, col;
    int age;
};
struct cmp{
    bool operator()(Tree A, Tree B){
        return A.age > B.age;
    }
};
priority_queue<Tree, vector<Tree>, cmp> alive_pq;
queue<Tree> death;
deque<Tree> alive;
int dr[] = {-1, -1, -1,  1,  1,  1,   0,  0};
int dc[] = {-1,  1,  0, -1,  1,  0,  -1, 1};


bool isBoundary(int row, int col){
    return row >= 0 and row < n and col >= 0 and col < n;
}


void Display(string mode, string when){

    cout << "****************" << when << "****************" << endl;


    cout << "=====Field=====" << "\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << field[i][j] << " ";
        }
        cout << endl;
    }
    cout << "=====Alive=====" << "\n";
    deque<Tree> que = alive;
    while(!que.empty()){
        cout <<"row : "<<que.front().row << " col: " << que.front().col << " age: " << que.front().age << "\n";
        que.pop_front();
    }


}

deque<Tree> spring(deque<Tree> que){

    deque<Tree> rst;

    while(!que.empty()){
        int row = que.front().row;
        int col = que.front().col;
        int age = que.front().age;
        que.pop_front();

        if(field[row][col] < age){
            death.push({row,col,age});
            continue;
        }

        field[row][col] -= age;
        rst.push_back({row,col,age+1});
    }

    return rst;

}

void summer(){
    while(!death.empty()){
        int row = death.front().row;
        int col = death.front().col;
        int age = death.front().age;
        death.pop();
        field[row][col] += age/2;
    }
}

void fall(deque<Tree> que){


    while(!que.empty()){
        int row = que.front().row;
        int col = que.front().col;
        int age = que.front().age;
        que.pop_front();

        if(age % 5 != 0) continue;

        for (int i = 0; i < 8; ++i) {
            int nr = row + dr[i];
            int nc = col + dc[i];
            if(!isBoundary(nr,nc)) continue;
            alive.push_front({nr,nc,1});
        }

    }
}

void winter(){

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            field[i][j] += food[i][j];
        }
    }

}

int main(){

    cin >> n >> m >> k;

    int row,col,age;
    int input;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> input;
            field[i][j] = 5;
            food[i][j] = input;
        }
    }

    for (int i = 0; i < m; ++i) {
        cin >> row >> col >> age;
        alive.push_back({row-1,col-1,age});
    }


    for (int i = 0; i < k; ++i) {
//        cout << "#################### " << i << " Year" << "#################### "<< endl;
        alive = spring(alive);//봄
//        Display("field","spirng");

        summer();//여름
//        Display("field","summer");

        fall(alive);//가을
//        Display("field","fall");

        winter(); //겨울
//        Display("field","winter");
    }
    cout << alive.size();


}

