#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>


using namespace std;

/*
 * 최대한 많은 로프를 사용하게 되면 가장 많은 중량을 버틸 수 있다!
 * 가장 작은 로프가 버틸 수 있는 중량 * 그보다 큰 로프 수가 정답이 되겠네
 * 가장 큰 로프에서 가장 작은 로프의 값을 뺀 녀석이 로프에 걸리는 중량보다 작다면 오키?
 * */

int N;
int weight[100002];
int ans;
int temp;

int main()
{

    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> weight[i];
    }

    sort(weight,weight+N);
//    for (int i = 0; i < N; ++i) {
//        cout << weight[i] << " ";
//    }

    for (int j = 0; j < N; ++j) {
        temp = weight[j] * (N-j);
        if(ans < temp)
            ans = temp;
    }
    if(N == 1)
        ans = weight[0];

    cout << ans << endl;

}