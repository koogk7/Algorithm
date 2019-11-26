// ConsoleApplication2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <stack>
#include <map>
#include <set>

using namespace std;

typedef long long ll;

/*
 * 11724 연결요소의 개수
 * - Uion-Find로 풀 경우, 마지막에 최종 부모를 다시 설정 해줘야 한다.
 *
 */

#define MAX_N 68
#define INF 123456789123


int n, m;
map<int, int> parent;
set<int> rst;

int find(int cur){
    if(parent[cur] == 0){
        parent[cur] = cur;
        return cur;
    }

    if(parent[cur] == cur)
        return cur;

    parent[cur] = find(parent[cur]);
    int a = parent[cur];

    return parent[cur];
}

void merge(int a, int b){
    int aParent = find(a);
    int bParent = find(b);

    if(aParent == bParent)
        return;
    parent[bParent] = aParent;
}

int main() {

    int source, dest;
    cin >> n >> m;

    for (int i = 1; i < n+1; ++i) {
        find(i);
        parent[i] = i;
    }

    for (int i = 0; i < m; ++i) {
        cin >> source >> dest;
        merge(source, dest);
    }

    for(auto item : parent){
        parent[item.first] = find(item.first); // 최종 부모 지정
        rst.insrt(parent[item.first]);
    }

    cout << rst.size();

}


