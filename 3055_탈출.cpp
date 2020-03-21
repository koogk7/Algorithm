#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <stack>
#include <map>
#include <set>
#include <math.h>

typedef long long ll;

using namespace std;

/*
 * 3055 탈출 20.03.21 20:48
 * 난이도 중
 * S ==> D , 고슴도치는 네칸 중 하나로 이동, 물은 비어있는 칸으로 확장
 * . ==> 비어있음
 * * ==> 물
 * x ==> 돌
 * 물은 .만 이동 가능
 * 고슴도치가 비버의 굴로 이동하기 위해 필요한 최소시간 구해라
 * 고슴도치는 물이 찰 예정인 칸으로 이동 할 수 없다.
 *
 * R*C = 50 * 50
 */

#define NO_ANS "KAKTUS"
#define MAX_V 51

int r,c;
char field[MAX_V][MAX_V];
bool visit[MAX_V][MAX_V];
int dr[] = {-1,1,0,0};
int dc[] = {0,0,-1,1};

struct Item {
    int r,c, d;
    bool isWater;
};

struct cmp {
    bool operator()(Item a, Item b){
        return a.d > b.d;
    }
};

priority_queue<Item, vector<Item>, cmp> pq;
Item start;
vector<Item> waters;

bool isIn(int row, int col) {
    return row>=0 and row<r and col>=0 and col<c;
}

void print(){
    cout << "========================" << endl;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cout << field[i][j] << " ";
        }
        cout << endl;
    }
}

int BFS(){
    for (int i = 0; i < waters.size(); ++i) {
        pq.push(waters[i]);
        visit[waters[i].r][waters[i].c] = true;
    }

    pq.push(start);
    visit[start.r][start.c] = true;

    while(!pq.empty()){
        Item cur = pq.top();
        pq.pop();

        for (int i = 0; i < 4; ++i) {
            int nr = dr[i] + cur.r;
            int nc = dc[i] + cur.c;

            if(!isIn(nr,nc)) continue;
            if(field[nr][nc] == 'D' and !cur.isWater)
                return cur.d + 1;
            if(field[nr][nc] == 'D') continue;
            if(field[nr][nc] == 'X' or field[nr][nc] == '*') continue;
            if(!cur.isWater and visit[nr][nc]) continue;

            pq.push(Item{nr,nc, cur.d+1, cur.isWater});
            if(cur.isWater)
                field[nr][nc] = '*';
            else{
                visit[nr][nc] = true;
            }
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> r >> c;

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cin >> field[i][j];
            if(field[i][j] == 'S'){
                start.r = i, start.c = j;
                start.isWater = false;
            }
            if(field[i][j] == '*'){
                waters.push_back({i,j,0,true});
            }
        }
    }

    int ans = BFS();
    if(ans == -1)
        cout << NO_ANS;
    else
        cout << ans;

}









