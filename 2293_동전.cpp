#include <iostream>
#include <cstring>
using namespace std;


int dp[10001], n[101];
int N, K ; // N은 동전의 갯수 , K은 총합


int coin(int k ){

    for (int i = 0; i < N; ++i) {
        for (int j = n[i]; j<= K; ++j) {
            dp[j] += dp[j- n[i]];
        }
    }
    return dp[k];
}

int main() {

    memset(dp,0,sizeof(dp));
    dp[0] = 1; // 0원은 모든 동전을 사용하지 않은 경우 한가지 존재
    int rst;

    cin >> N >> K;

    for (int i = 0; i < N; ++i) {
        cin >> n[i];
    }

    rst = coin(K);

    cout << rst << endl;

    return 0;
}



//for(int j= a; j<=k; j++){
//    d[j] += d[j-a]
//}