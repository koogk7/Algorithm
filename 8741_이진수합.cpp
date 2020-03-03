#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <stack>
#include <map>
#include <set>
#include <math.h>

typedef long long ll;


#define MAX_N 68
#define INF 987654321



using namespace std;

/* 8741 이진수 합
 *
 * 난이도 중?
 *
 * 회고
 *  k가 너무 커서, 어떻게 접근할지 감이 잘 안 왔다.
 *  그래서 우선 터지는 걸 각오하고 int로 찍어봄
 *  그러다 보니 규칙성이 보여서... 허무하게 품
 *
 * * k = 1
 * 1
 * k = 2
 * 01 + 10 + 11 = 110 (6)
 * k = 3
 * 11100 (28)
 *
 * 1. 2^(k+1) - 1 만큼 합을 구한다.
 * 2. 이진수로 변환
 *      2-1. 나머지만 취한다.
 */

ll k;

string getSum(ll num) {
    string ans;
    ll maxNumber = powl(2L, num) - 1L;
    ll sum = maxNumber * (maxNumber+1L)/2L;
    ll rest = 0L;
    ll remainValue = sum;

    while (remainValue > 0L) {
        rest = remainValue % 2L;
        remainValue /= 2L;
        ans += to_string(rest);
    }

    for (int i = ans.size()-1; i >=0 ; i--) {
        cout << ans[i];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> k;
    string ans = "";
    for (int i = 0; i < k; ++i) {
        ans += "1";
    }

    for (int i = 0; i < k-1; ++i) {
        ans += "0";
    }
    cout << ans;
}










