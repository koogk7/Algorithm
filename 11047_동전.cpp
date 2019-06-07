#include <iostream>
#include <algorithm>
#include <queue>


using namespace std;
/*
 * 동전의 종류 N, 각각의 동전은 매우 많음
 * 이들을 이용해서 가치의 합 K를 만듬
 * ---> 가장 적은 동전의 수로 K를 만드는 문제
 * 그럼 가장 큰 동전으로 먼저 K를 채워나가야겠네!
 * 코인배열 입력후 정렬,
 * c[I] <= K 을 경우, K = K - I , cnt++
 * c[I] > K 경우, i--
 * ---> K가 딱 0이 될때까지!
 */

int N, K;
int coin[12];
int cnt;


int main()
{
    int i;
    int temp;
    cin >> N >> K;

    for (i = 0; i < N; ++i) {
        cin >> coin[i];
    }
    sort(coin, coin+i);
    i--;

    while(K != 0)
    {
        temp = K-coin[i];
        if(temp >= 0){
            K = K - coin[i];
            cnt++;
        }
        else{
            i--;
        }

    }

    cout << cnt<< endl;



}