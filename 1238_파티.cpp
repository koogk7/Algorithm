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

/*

 * */
#define INF 987654321

int v, e;
int dest;
int dist[1002][1002];
struct vertex{
    int num, value;
};
int ans;

struct cmp{
    bool operator()(vertex A, vertex B){
        return A.value > B.value;
    }
};

vector<vector<vertex>> graph;


void dijkstra(int start){

    priority_queue<vertex, vector<vertex>, cmp> pq;
    pq.push({start,0});

    while(!pq.empty()){
        int cur_num = pq.top().num;
        int cur_dist = pq.top().value;
        pq.pop();

        if(dist[start][cur_num] < cur_dist) continue;

        for (int i = 1; i < graph[cur_num].size(); ++i) {
            int next_num = graph[cur_num][i].num;
            int next_dist = cur_dist + graph[cur_num][i].value;
            if(dist[start][next_num] < next_dist) continue;
            dist[start][next_num] = next_dist;
            pq.push({next_num, next_dist});
        }
    }
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> v >> e >> dest;

    graph = vector<vector<vertex>>(v+1,vector<vertex>(1,{0,0}));
    int s,d,w;

    for (int i = 0; i < v+1; ++i) {
        for (int j = 0; j < v+1; ++j) {
            dist[i][j] = INF;
        }
    }

    for (int i = 0; i < e; ++i) {
        cin >> s >> d >> w;
        graph[s].push_back({d,w});
    }


    for (int i = 1; i < v+1; ++i) {
        dist[i][i] = 0;
        dijkstra(i);
    }


    for (int i = 1; i < v+1; ++i) {
        ans = max(ans, dist[dest][i] + dist[i][dest]);
    }
    cout << ans << "\n";

}

