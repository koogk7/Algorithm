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
 * 1325 효율적인 해킹
 *  회고
 *  - 처음에 DP로 풀려고 접근했다. 그러나 최대 노드 수만큼 2차원 배열을 만들어 400MB로 메모리 초과를 받았다.
 *  - DP없이 N * M 시간복잡도를 가지는 코드를 작성했으나 시간초과를 받았다.
 *  - 원인은 DFS에서 나오면서 visit을 해제하는데 이렇게 되면 엄청 많은 반복이 생기게 된다.
 *  - 단순히 자식 노드 수만 카운트하면 되는데 나는 자식노드로 가는 경로까지 모두 구할려고 했다.
 */

#define MAX_NODE 10001

int n, m;
vector<int> graph[MAX_NODE];
bool visit[MAX_NODE];

int DFS(int curNode){ // 해당 노드에서 해킹 할 수 있는 최댓값을 반환

    int nextNode;

    int ret = 0;

    for(int i = 0; i < graph[curNode].size(); ++i) {
        nextNode = graph[curNode][i];
        if(visit[nextNode]) continue;
        visit[nextNode] = 1;
        ret += DFS(nextNode);
        ret++;
    }

    return ret;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int a, b;
    int maxHackNum = 0;
    int hackNum = 0;
    vector<int> hackNums;
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        cin >> a >> b;
        graph[b].push_back(a);
    }


    for (int i = 1; i < n+1; ++i) {
        visit[i] = 1;
        hackNum = DFS(i);
        maxHackNum = max(maxHackNum, hackNum);
        hackNums.push_back(hackNum);
        fill(visit, visit+MAX_NODE, false);
    }

    for (int i = 0; i < hackNums.size(); ++i) {
        if(maxHackNum == hackNums[i])
            cout << i + 1 << " ";
    }


}

