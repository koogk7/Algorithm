// ConsoleApplication2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*
구역을 두 개의 선거구로 나눠야 한다.
선거구는 구역을 적어도 하나 포함해야한다
한 선거구에 포함되어 있는 구역은 모두 연결되어야 한다.

선거구에 포함된 인구의 차이를 최소로 할려고한다.

*/
#define INF 987654321
int n;
vector<int> graph[13];
vector<int> peoples;
vector<int> team[2];
int where[13];
bool visit[13];
/*
각 노드마다 팀을 선택 --> 2^13
팀을 선택할 때마다 팀 벡터에 삽입
팀 노드 하나로 BFS 탐색, 팀 노드들 중 선택 되지 않은 노드가 있을 경우 패스
*/


void initVisit() {
    for (int i = 0; i < n; i++)
    {
        visit[i] = false;
    }
}

// 연결된 노드들 마킹
void BFS(int team_number) {
    queue<int> que;
    que.push(team[team_number][0]);
    visit[team[team_number][0]] = 1;

    while (!que.empty()) {
        int current = que.front();
        que.pop();

        for (int i = 0; i < graph[current].size(); i++) {
            int next = graph[current][i];
            if (visit[next])
                continue;
            if (where[next] != team_number)
                continue;
            visit[next] = true;
            que.push(next);
        }
    }
}

bool isConnected(int team_number) {

    for (int i = 0; i < team[team_number].size(); i++)
    {
        int node = team[team_number][i];
        if (!visit[node])
            return false;
    }

    return true;
}

int getSum(int team_number) {
    int sum = 0;

    for (int i = 0; i < team[team_number].size(); i++) {
        int node = team[team_number][i];
        sum += peoples[node];
    }

    return sum;
}


bool isValid(int team_number) {
    initVisit();
    BFS(team_number);
    return isConnected(team_number);
}


int dfs(int idx) {
    if (idx >= n) {

        if (team[0].size() < 1 or team[1].size() < 1)
            return INF;

        if (isValid(0) == false or isValid(1) == false)
            return INF;

        // BFS 탐색
        return abs(getSum(0) - getSum(1));
    }

    int ret = INF;

    team[0].push_back(idx);
    where[idx] = 0;
    ret = dfs(idx + 1);
    team[0].pop_back();

    team[1].push_back(idx);
    where[idx] = 1;
    ret = min(ret, dfs(idx + 1));
    team[1].pop_back();

    where[idx] = -1;

    return ret;
}


int main()
{
    cin >> n;

    int input, cnt;
    peoples = vector<int>(n+1, 0);

    // 인구수 할당
    for (int i = 0; i < n; i++)
    {
        cin >> peoples[i];
        where[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        cin >> cnt;

        for (int j = 0; j < cnt; j++)
        {
            cin >> input;
            input--;
            graph[i].push_back(input);
        }

    }

    int ans = dfs(0);

    if (ans == INF)
        ans = -1;

    cout << ans;

}
