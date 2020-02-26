#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <stack>
#include <map>
#include <set>

typedef long long ll;


#define MAX_N 68
#define INF 987654321



using namespace std;

/* 1495 기타리스트
 *
 * 회고
 *  - 완전탐색으로 시간 복잡도가 O(2^100)이라 충분하다 생각, 복잡도 잘 못 계산함
 *  - DP로 쉽게 풀었으나, ans가 0일 때도 -1로 바꾸고 있었음... 때문에 아래 반례 발생
 * 반례
 *  1 1 1
    1
    답 0, 출력 -1
 *
 */

int n,s,m;
int ans = -1;
int volumes[101];
bool cache[101][1050]; // [index][volume]

bool isBoundary(int value){
    return value >= 0 && value <= m;
}

void backTracking(int idx, int current) {
    if(cache[idx][current])
        return;

    cache[idx][current] = true;

    if(idx == n) {
        ans = max(ans, current);
        return;
    }

    if(isBoundary(current + volumes[idx]))
        backTracking(idx+1, current + volumes[idx]);

    if(isBoundary(current - volumes[idx])){
        backTracking(idx+1, current - volumes[idx]);
    }

    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> s >> m;

    for (int i = 0; i < n; ++i) {
        cin >> volumes[i];
    }

    backTracking(0,s);
    cout << ans << "\n";
}









