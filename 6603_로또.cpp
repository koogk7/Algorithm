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
 * 6603 로또
 * - 집합 S와 K가 주어졌을 때, 6개를 고를 수 있는 모든 경우의  수
 *
 */

#define MAX_N 68
#define INF 123456789123

int k = -1;
vector<int> inputs;
vector<int> selected;

void dfs(int idx, int cnt){
    if(cnt == 6){
        for(auto number : selected)
            cout << number << " ";
        cout << endl;
        return;
    }

    if(idx >= k)
        return;

    selected.push_back(inputs[idx]);
    dfs(idx+1, cnt+1);
    selected.pop_back();
    dfs(idx+1, cnt);

}

int main() {
    while(1){
        cin >> k;
        if(k == 0)
            break;

        inputs = vector<int>(k);

        for (int i = 0; i < k; ++i) {
            cin >> inputs[i];
        }

        dfs(0,0);
        cout << endl;
    }
}


