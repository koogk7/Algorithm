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
#define INF 987654321

int n,m;
int box[51][51];
int dist[51][51];
int dr[] = {-1,1,0,0};
int dc[] = {0,0,-1,1};
struct edge{
    int row, col, weight;
};
struct cmp{
    bool operator()(edge A, edge B){
        return A.weight > B.weight;
    }
};


bool isBoundary(int row, int col)
{
    return row>=0 && row<n && col>=0 && col<=m;
}

int dijkstra(edge start){

    priority_queue<edge, vector<edge>, cmp> pq;
    pq.push(start);
    int rst = -1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            dist[i][j] = INF;
        }
    }
    dist[start.row][start.col] = 0;

    while(!pq.empty()){
        int row = pq.top().row;
        int col = pq.top().col;
        int weight = pq.top().weight;
        pq.pop();

        for (int i = 0; i < 4; ++i) {
            int nr = row + dr[i];
            int nc = col + dc[i];
            if(!isBoundary(nr,nc)) continue;
            if(box[nr][nc]) continue;
            if(weight + 1 < dist[nr][nc]){
                dist[nr][nc] = weight + 1;
                pq.push({nr,nc,weight+1});
                rst = max(rst, weight+1);
            }
        }

    }

    return rst;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    char input;
    int ans = -1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> input;
            if(input == 'W')
                box[i][j] = 1;
            else
                box[i][j] = 0;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if(box[i][j]) continue;
            ans = max(ans, dijkstra({i,j,0}));
        }
    }
    cout << ans;

}

