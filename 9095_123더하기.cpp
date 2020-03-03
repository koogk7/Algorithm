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

/* 9095 1,2,3 더하기
 * 난이도 하
 *
 */

int n,T;
int cache[13];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cache[0] = 0;
    cache[1] = 1;
    cache[2] = 2;
    cache[3] = 4;
    cin >> T;
    for (int i = 4; i <= 11; ++i) {
        cache[i] = cache[i-1] + cache[i-2] + cache[i-3];
    }

    while(T--){
        cin >> n;
        cout << cache[n] << endl;
    }



}










