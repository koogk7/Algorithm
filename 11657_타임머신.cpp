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



#define MAX_N 502
#define INF 987654321

struct edge {
    int nodeNum, value;
};
int n, m;
vector<edge> graph[MAX_N];
int _dist[MAX_N];
int _cycle[MAX_N];
bool _inQ[MAX_N];


bool SPFA(int dist[], int cycle[], bool inQ[]){


    queue<int> que;
    dist[1] = 0;
    inQ[1] = true;
    que.push(1);

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
            if(cycle[nextNode] == n-1){
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

    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int from, to , val;
        cin >> from >> to >> val;
        graph[from].push_back({to, val});
    }

    fill(_dist, _dist + MAX_N , INF);
    bool isNCylcle = SPFA(_dist, _cycle, _inQ);

    if(isNCylcle) {
        for (int j = 2; j <= n; ++j) {
            int ans = _dist[j] != INF ? _dist[j] : -1;
            cout << ans << "\n";
        }
    } else {
        cout << "-1\n";
    }

}

