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

/*
 * 12851 숨바꼭질2 - 회고
 *  경로 갯수 올려줄 때, 하나씩만 올려줘서 계속 오답이 나왔다. 이전까지의 값을 더해줘야한다.
 *
 */

using namespace std;
#define MAX_N 100001


int start, dest;
int num[MAX_N];
int visit[MAX_N];
queue<int> que;

bool isBoundary(int n){
    return n >=0 && n < MAX_N;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> start >> dest;
    que.push(start);
    visit[start] = 1;
    num[start] = 1;

    if(start == dest) {
        cout << "0" << "\n";
        cout << "1" << "\n";
        return 0;
    }

    while(!que.empty()){
        int cur = que.front();
        que.pop();
        int nexts[] = {cur + 1, cur - 1, cur * 2};

        for (int i = 0; i < 3; ++i) {
            int next = nexts[i];
            if(!isBoundary(next)) continue;
            if(next == 6)
                cout<<"";
            if(visit[next]){
                if(visit[next] == visit[cur]+1) {
                    num[next] += num[cur];
                }
                continue;
            }
            visit[next] = visit[cur] + 1;
            num[next] += num[cur];
            que.push(next);
        }

    }
    cout << visit[dest]-1 << "\n";
    cout << num[dest] << "\n";

}

