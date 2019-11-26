// ConsoleApplication2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*
 * 다리만들기 2
 * 1. BFS로 각 섬들 마킹
 * 2. 모든 섬들 사이의 최단 경로 저장
 * 3. 최단경로에서 엣지를 저장
 * 4. MST
 *
 * 삽질음
 * 0. 섬 좌표를 미리 저장하지 않았음
 * 1. optimalPath의 범위를 n,m으로 잡아 줬음
 * 2. optimalPath는 갱신이 될 수 있는데, 이걸 그냥 덮어씌어주고 있었
 *
*/
#define INF 987654321

int sea[11][11];
int visit[10][10];
int optimalPath[7][7];
bool nodeVisit[7][7];
int n, m;
struct point{
    int row, col;
};
struct edge{
    int node1, node2;
    int dist;
};
int dr[] = {-1,0,1,0};
int dc[] = {0,-1,0,1};
int marking_number = 1;
vector<point> landQue[7];
vector<edge> edges;
int parent[7];

void display(){
    cout << "==========" << endl;
    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            cout << optimalPath[i][j] << " ";
        }
        cout << endl;
    }

    cout << "==========" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << sea[i][j] << " ";
        }
        cout << endl;
    }
}

void initVisit(){
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            visit[i][j] = 0;
        }
    }
}

bool isIn(int r, int c){
    return r>=0 and r < n and c>=0 and c < m;
}

// 섬들의 번호 부여
int Marking(point start, int number){
    if(sea[start.row][start.col] == 0)
        return 0;
    if(visit[start.row][start.col])
        return 0;

    queue<point> que;
    que.push({start});
    visit[start.row][start.col] = number;
    sea[start.row][start.col] = number;
    landQue[number].push_back(start);

    while(!que.empty()){
        int row = que.front().row;
        int col = que.front().col;
        que.pop();

        for (int i = 0; i < 4; ++i) {
            int nr = row + dr[i];
            int nc = col + dc[i];

            if(!isIn(nr,nc))
                continue;
            if(visit[nr][nc])
                continue;
            if(sea[nr][nc] == 0)
                continue;
            que.push({nr,nc});
            visit[nr][nc] = number;
            sea[nr][nc] = number;
            landQue[number].push_back({nr, nc});
        }
    }

    return 1;
}

// 시작 섬부터 다른 섬간의 거리를 구함,
void getDistance(int source, int dir){
    queue<point> que;

    for (int i = 0; i < landQue[source].size(); ++i) {
        int row = landQue[source][i].row;
        int col = landQue[source][i].col;
        que.push({row,col});
        visit[row][col] = 1;
    }


    while(!que.empty()){
        int row = que.front().row;
        int col = que.front().col;
        int dist = visit[row][col];
        que.pop();

        if(sea[row][col] != 0 and sea[row][col] != source){
            // 다른섬 도착
            int dest = sea[row][col];
            if(dist-2 == 1)
                continue;
            optimalPath[source][dest] = min(optimalPath[source][dest], dist-2);
            continue;
        }


        int nr = row + dr[dir];
        int nc = col + dc[dir];

        if(!isIn(nr,nc))
            continue;
        if(visit[nr][nc])
            continue;

        que.push({nr,nc});

        if(sea[nr][nc] == source)
            visit[nr][nc] = dist;
        else
            visit[nr][nc] = dist + 1;

    }

}

void setEdge(){

    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 7; ++j) {
            if(optimalPath[i][j] < 2 or optimalPath[i][j] == INF)
                continue;
            if(nodeVisit[i][j] and nodeVisit[j][i])
                continue;
            edges.push_back({i,j,optimalPath[i][j]});
            nodeVisit[i][j] = true;
            nodeVisit[j][i] = true;
        }
    }

    sort(edges.begin(), edges.end(), [](edge a, edge b){
        return a.dist < b.dist;
    });

}

int find(int nodeNumber){
    if(parent[nodeNumber] == nodeNumber)
        return nodeNumber;

    return find(parent[nodeNumber]);
}

void merge(int a, int b){
    int parentA = find(a);
    int parentB = find(b);

    if(parentA == parentB)
        return;

    parent[parentB] = parentA;
    return;
}

bool isCycle(int a, int b){
    return find(a) == find(b);
}

int MST(){
    int rst = 0;

    for (int i = 0; i < edges.size(); ++i) {
        int source = edges[i].node1;
        int dest = edges[i].node2;

        if(isCycle(source, dest))
            continue;

        merge(source, dest);
        rst += edges[i].dist;
    }

    int p = find(1);

    for (int i = 2; i < marking_number; ++i) {
        if(find(i) != p)
            return -1;
    }

    return rst;

}

int main() {

    cin >> n >> m;

    for (int i = 0; i < 7; ++i) {
        parent[i] = i;
        landQue[i] = vector<point>();

        for (int j = 0; j < 7; ++j) {
            optimalPath[i][j] = INF;
        }

    }


    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> sea[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            marking_number += Marking({i,j}, marking_number);
        }
    }


    for (int i = 1; i < marking_number; ++i) {
        for (int j = 0; j < 4; ++j) { // 방향
            initVisit();
            getDistance(i,j);
        }
    }

    // MST 만 짜면 됨 여기까지 1시
    setEdge();
    cout << MST();
//    display();
}


