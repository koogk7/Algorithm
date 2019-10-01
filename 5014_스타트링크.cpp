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
 * 5014 스타트링크
 *
 */

int f,s,g,u,d;
int visit[10000001];
int dir[2];

int BFS(int start){
    queue<int> que;
    que.push(start);
    visit[start] = 1;

    while(!que.empty()){
        int cur = que.front();
        int dist = visit[cur];
        que.pop();

        if(cur == g)
            return dist -1;

        for (int i = 0; i < 2; ++i) {
            int next = cur + dir[i];
            if(next > f or next < 1) continue;
            if(visit[next]) continue;
            que.push(next);
            visit[next] = dist + 1;
        }
    }

    return -1;
}

int main(){
    cin >> f >> s >> g >> u >> d;
    dir[0] = u;
    dir[1] = d*-1;
    int ans = BFS(s);


    if(ans == -1)
        cout << "use the stairs" << "\n";
    else
        cout << ans;
}

