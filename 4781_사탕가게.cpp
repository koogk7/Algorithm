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

/*
 * 4781 사탕가게
 * 소요시간 : 22분분게
 * - 구매한 사탕의 칼로리가 더 큰 사람이 이긴다.
 * - 사탕 가격과 칼로리가 주어졌을 때, 칼로리의 합이 가장 크게!
 * 삽질
 *  - float, double 타입을 int로 바꿀 때는 0.5를 더해줘야 한다.
 *  - 구매할 수 없을 때 -1이 출력되고 있었다
 *  - dp값이 -1로 초기화 되어있는데 물건을 사지 못하는 경우 그대로 -1이 리턴 되어서 오차가 발생했다.
 */

struct Candy {
    int calorie;
    int amount;
};
vector<Candy> candyList;
int dp[10001];
int n;

void init(){
    for (int i = 0; i < 10001; ++i) {
        dp[i] = -1;
    }
}

int backTracking(int remain){
    if(remain == 0)
        return 0;

    int &ret = dp[remain];

    if(ret != -1)
        return ret;

    ret = max(ret, 0);

    for (int i = 0; i < n; ++i) {
        if(remain < candyList[i].amount)
            continue;
        ret = max(ret, backTracking(remain - candyList[i].amount) + candyList[i].calorie);
    }

    return ret;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    candyList = vector<Candy>(5002);

    while(1){
        int remain;
        int inputCalorie;
        double m, inputAmount;
        init();

        cin >> n >> m;

        remain = int(m*100 + 0.5);

        if(n == 0 and m == 0.00)
            break;

        for (int i = 0; i < n; ++i) {
            cin >> inputCalorie >> inputAmount;
            candyList[i] = {inputCalorie, int(inputAmount*100 + 0.5)};
        }

        backTracking(remain);
        cout << max(dp[remain],0) << "\n";
    }
}









