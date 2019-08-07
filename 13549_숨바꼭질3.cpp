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
 * 13549 숨바꼭질3 - 회고
 *   가중치가 다를 경우 BFS를 사용 할 수 없다. 가중치가 다를 때 최단경로를 찾는
 *   알고리즘으로는 다익스트라고 있어 이를 적용햇다. 단 문제를 푸는 과정에서 이미 방문한
 *   정점에 대해 갱신을 하지 않았다.
 *   다익스트라 vs BFS
 *   다익스트라는 방문된 노드를 갱신하고, 각 가중치가 다를 수 있다.
 *
 */

using namespace std;
#define MAX_N 100001


int start, dest;
int visit[MAX_N];
int cost[] = {0,1,1};
struct point{
    int pos, value;
};

struct cmp {
    bool operator()(point A, point B){
        return A.value > B.value;
    }
};

priority_queue<point, vector<point>, cmp> pq;

bool isBoundary(int n){
    return n >=0 && n < MAX_N;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);


    for (int i = 0; i < MAX_N; ++i) {
        visit[i] = 987654321;
    }

    cin >> start >> dest;
    pq.push({start,1});
    visit[start] = 1;

    if(start == dest) {
        cout << "0" << "\n";
        return 0;
    }


    while(!pq.empty()){
        int cur = pq.top().pos;
        int value = pq.top().value;
        pq.pop();
        int nexts[] = {cur * 2, cur - 1, cur + 1};

        for (int i = 0; i < 3; ++i) {
            int next = nexts[i];
            if(!isBoundary(next)) continue;
            if(value + cost[i] < visit[next]) {
              visit[next] = value + cost[i];
              pq.push({next,value + cost[i]});
            }
        }

    }
    cout << visit[dest]-1 << "\n";

}

