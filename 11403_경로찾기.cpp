// ConsoleApplication2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <stack>
#include <map>

using namespace std;

typedef long long ll;

/*
 * 11403 경로찾기
 * - 방향이 없는 그래프 인줄 알고 Union find로 풀려고 했다..
 * - rst[i][i]는 0이 디폴트!, 문제 조건 잘 읽기!
 */

#define MAX_N 68
#define INF 123456789123


vector<int> ad[101];
bool visit[101];
int rst[101][101];


void BFS(int startIdx){
    queue<int> que;
    que.push(startIdx);

    while (!que.empty()){
        int cur = que.front();
        que.pop();

        for (int i = 0; i < ad[cur].size(); ++i) {
            int next = ad[cur][i];

            if(visit[next])
                continue;

            que.push(next);
            visit[next] = true;
            rst[startIdx][next] = 1;
        }
    }
}


int main() {
    int n,input;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> input;
            if(input)
                ad[i].push_back(j);
        }
    }


    for (int i = 0; i < n; ++i) {
        BFS(i);
        memset(visit,0, sizeof(visit));
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << rst[i][j] << " ";
        }
        cout << endl;
    }

}


