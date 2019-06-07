#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define  SIZE 1000
int visit[SIZE+1]; // 이거에 대해서 물어보기
vector<int> graph[SIZE+1]; // 크기가 SIZE+1인 vector<int>형 배열

void dfs(int x)
{
    if(visit[x]) return;
    visit[x] = true;
    cout << x << ' ';

    // 정점이 여러개 인 경우 정점 번호가 작은 것부터 방문 할 수 있도록 정렬합니다.
    sort(graph[x].begin(),graph[x].end());

    for (int i = 0; i < graph[x].size(); ++i) {
        int y = graph[x][i]; // 인접한 node를 탐색합니다.
        dfs(y);
    }
}

void bfs(int x)
{
    queue<int> q;
    q.push(x); // 시작점을 que에 넣습니다.
    visit[x] = true; // 큐에 들어가면 방문처리를 합니다.

    while(!q.empty()){
        int k = q.front(); //
        q.pop();
        cout << k << ' ';
        sort(graph[x].begin(),graph[x].end());
        for (int i = 0; i < graph[k].size(); ++i) {
            int y = graph[k][i];
            if(visit[y] == false){
                q.push(y);
                visit[y] = true;
            }
        }
    }

}




void connectEdge(int a, int b)
{

    graph[a].push_back(b);
    graph[b].push_back(a);

}

int main()
{
    int n, m, v;
    int a, b;
    cin >> n >> m >> v;

    for (int i = 0; i < m; ++i) {
        cin >> a >> b;
        connectEdge(a,b);
    }

    dfs(v);
    cout << endl;
    for (int j = 0; j < n+1; ++j) {
        visit[j] = false;
    }
    
    bfs(v);

    return 0;
}


