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
#include <set>
#include <sstream>
#include <string.h>
using namespace std;
typedef long long ll;
#define MAX_NODE 1000001

vector<int> tree[MAX_NODE];
int n;
int parent[MAX_NODE];


//dfs로 탐색
int dfs(int cur){
    if(cur > n){
        return -1;
    }

    int node;

    for (int i = 0; i < tree[cur].size(); ++i) {
        node = tree[cur][i];
        if(parent[tree[cur][i]]) continue;
        parent[node] = cur;
        dfs(node);
    }

    return 1;
}


int main(){

    cin >> n;
    int first_node, seceond_node;

    for (int i = 0; i < n-1; ++i) {
        cin >> first_node >> seceond_node;
        tree[first_node].push_back(seceond_node);
        tree[seceond_node].push_back(first_node);
    }

    dfs(1);

    for (int i = 2; i <= n; ++i) {
        cout << parent[i] << "\n";
    }


}

