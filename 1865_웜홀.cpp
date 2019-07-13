// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <queue>
#include <vector>
#include <string.h>
#include <algorithm>
#include <map>
#include <math.h>
using namespace std;


/**
 * 1865번 웜홀
 *
 * 삽질노트
 *  1. 웜홀 과 도로를 따로 그래프를 그래셔, 각각의 최단거리를 구해서 더해서 결과를 출력할려 했음
 *      ---> 다시 돌아오는 최단경로를 구하기가 어렵다. 웜홀의 사이클이 형성 될 경우 체크가 안됨
 *  2. 문제 이해를 잘 못하고 있었다. 나는 도로로 여행 후 웜홀을 타고 돌아온다는 상황을 가정을 했는데
 *  문제는 웜홀만 타고 돌아와도 하나의 시간여행으로 간주한다. 즉 음의 사이클이 있는지를 체크하는 여부이다.
 *  3. 2차원 벡터 초기화... 실수
 */
#define MAX_N 503
#define INF 987654321

struct edge {
    int nodeNum, value;
};
int t;
int n, m, w;
int _dist[MAX_N];
int _cycle[MAX_N];
bool _inQ[MAX_N];
vector<edge> graph[MAX_N];

void init(){
    for (int i = 0; i <= n; ++i) {
        _dist[i] = INF;
        _cycle[i] = 0;
        _inQ[i] = false;
    }
}

bool SPFA(int startNode, int dist[], int cycle[], bool inQ[]){

    queue<int> que;
    dist[startNode] = 0;
    inQ[startNode] = true;
    que.push(startNode);

    while(!que.empty()){
        int cur = que.front();
        que.pop();
        inQ[cur] = false;

        for (int i = 0; i < graph[cur].size(); ++i) {
            int nextNode = graph[cur][i].nodeNum;
            int nextValue = graph[cur][i].value;
            bool isUpdate = dist[cur] + nextValue < dist[nextNode];
            if(!isUpdate) continue;
            dist[nextNode] = dist[cur] + nextValue;
            if(inQ[nextNode]) continue;
            if(cycle[nextNode] >= n-1){
                return false;
            }
            que.push(nextNode);
            inQ[nextNode] = true;
            cycle[nextNode]++;
        }
    }

    return true;
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> t;

    while(t--){
        int s,e,v;
        bool isNCycle;

        string ans;
        cin >> n >> m >> w;

        for (int i = 0; i <= n; ++i) {
            graph[i].clear();
        }

        for (int i = 0; i < m; ++i) {
            cin >> s >> e >> v;
            graph[s].push_back({e,v});
            graph[e].push_back({s,v});
        }

        for (int i = 0; i < w; ++i) {
            cin >> s >> e >> v;
            graph[s].push_back({e,v*-1});
        }

        for (int i = 1; i <= n; ++i) {
            init();
            isNCycle = !SPFA(i, _dist, _cycle, _inQ);
            if(isNCycle) break;
        }

        ans = isNCycle ? "YES" : "NO";
        cout << ans << "\n";
    }


}

