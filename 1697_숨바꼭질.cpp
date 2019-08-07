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

using namespace std;
#define MAX_N 100001


int start, dest;
int field[MAX_N];
queue<int> que;

bool isBoundary(int n){
    return n >=0 && n < MAX_N;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> start >> dest;
    que.push(start);
    field[start] = 1;

    if(start == dest) {
        cout << "0";
        return 0;
    }

    while(true){
        int cur = que.front();
        que.pop();
        int nexts[] = {cur + 1, cur - 1, cur * 2};

        for (int i = 0; i < 3; ++i) {
            int next = nexts[i];
            if(!isBoundary(next)) continue;
            if(field[next]) continue;
            if(next == dest){
                cout << field[cur];
                return 0;
            }
            field[next] = field[cur] + 1;
            que.push(next);
        }

    }

}

