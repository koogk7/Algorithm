// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <queue>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;


/**
 * 1005번 ACM Craft
 *
 *  회고
 *  1. 문제의 핵심은 규칙을 어떻게 저장하고 다룰지이다. 규칙이 없다면 단순한 dp문제
 *  2. 규칙을 이차원 벡터에 저장하고, 이 벡터를 타고 들어가서 먼저 건설해야할 건물의 최대시간을 dp에 저장
 *  3. 시간복잡도 K(벡터 타고 들어가는 수 = 규칙수) * N(먼저 건설해야할 최대 건물 수 = 트리 Depth)
 */

int T, n, k, w;
int dp[1003];
int costs[1001];
vector<vector<int>> build_order;


int BackTracking(int cur_number){

    if(build_order[cur_number].size() == 1){
        dp[cur_number] = costs[cur_number];
        return dp[cur_number];
    }
    if(dp[cur_number] != -1)
        return dp[cur_number];

    int &ret = dp[cur_number];

    for (int i = 1; i < build_order[cur_number].size(); ++i) {
        ret = max(ret,BackTracking(build_order[cur_number][i])+costs[cur_number]);
    }

    return ret;

}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> T;

    while(T--){
        cin >> n >> k;
        int a, b;
        build_order = vector<vector<int>>(n+1,vector<int>(1,0)); // 2차원 벡터 초기화
        for(int i = 1; i < n+1; i++) cin >> costs[i];
        memset(dp,-1, sizeof(dp));
        for (int i = 0; i < k; ++i) {
            cin >> a >> b;
            build_order[b].push_back(a);
        }
        cin >> w;
        cout << BackTracking(w) << endl;
    }

}

