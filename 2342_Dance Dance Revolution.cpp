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

/* 2342 Dance Dance Revolution
 *
 * - 두 발이 같은 지점에 있음 안됨
 * - 동시에 움직이지 않음
 * - 중앙 --> 2
 * - 인접 --> 3
 * - 반대 --> 4
 * - 반복 --> 1
 * - 입력 10^5
 */
#define MAX_V 100001
#define INF 987654321
int inputs[MAX_V];
int len;
int cache[5][5][MAX_V]; // left,right,idx

int getCost(int current, int next){
    if(current == next)
        return 1;
    if(current == 0)
        return 2;
    if(abs(next-current) == 2)
        return 4;
    return 3;
}

int bt(int left, int right, int depth) {
    if(depth == len){
        return 0;
    }

    int &ret = cache[left][right][depth];
    if(ret != INF){
        return ret;
    }

    int nextDir = inputs[depth];
    if(nextDir != right){
        ret = bt(nextDir, right, depth+1) + getCost(left,nextDir);
    }
    if(nextDir != left){
        ret = min(ret, bt(left, nextDir, depth+1) + getCost(right,nextDir));
    }

    return ret;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    while(1){
        cin >> inputs[len];
        if(inputs[len] == 0)
            break;
        len++;
    }

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            for (int k = 0; k < len; ++k) {
                cache[i][j][k] = INF;
            }
        }
    }

    cout << bt(0,0,0);
}










