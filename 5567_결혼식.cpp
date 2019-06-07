#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
/*
 * 학번이 있네, 상근이의 학번은 1
 * 상근이는 동기들의 친구관계를 조사한 리스트를 가지고 있어
 * 이 리스트를 바탕으로 결혼식에 초대할 사람의 수를 구해!
 * 상근이는 자신의 친구와, 친구의 친구를 초대
 * 즉 그래프 그려서, 상근이로부터 거리가 2인 노드들의 수를 체크하면 되겠다!
 * DFS를 사용하자
 * */



using namespace std;

int ans;
int n, m;
int invite[502]; // 1의 수만큼 정답
vector<vector<int>> f_list;

void DFS(vector<int>& node,int dist)
{
    if(dist == 2) return;

    for (int i = 1; i < node.size(); ++i) {
        if(invite[node[i]] == 0)
            invite[node[i]] = 1; // 초대장 발급
        DFS(f_list[node[i]], dist+1);
    }
}


int main(){

    int a, b;
    cin >> n >> m;

    for (int i = 0; i < n+1; ++i) {
        vector<int> v;
        v.push_back(0);
        f_list.push_back(v);
    } // 0 인덱스는 안씀

    for (int j = 0; j < m; ++j) {
        cin >> a >> b;
        f_list[a].push_back(b);
        f_list[b].push_back(a); // 이 부분을 빼먹어서 한번틀림
    }

    DFS(f_list[1],0);

    for (int k = 0; k < n+1; ++k) {
        if(invite[k] == 1)
            ans++;
    }

    cout << ans-1 <<endl; // 상근이를 포함함으로



}

