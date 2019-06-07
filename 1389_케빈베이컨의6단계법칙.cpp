#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;


int N, M;
int d[101][101];
int kebin_baycon[101];

void floyd()
{
    for (int k = 0; k <N ; ++k) { // 거쳐가는 노드
        for (int i = 0; i < N; ++i) { // 출발노드
            for (int j = 0; j < N; ++j) { // 도착노드
                if( d[i][k]+d[k][j] < d[i][j])
                    d[i][j] = d[i][k]+d[k][j];
            }
        }
    }
}

int main()
{


    int min = 100;
    int ans = 0;
    int a, b;

    cin >> N >> M;


    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if(i == j)
                d[i][j] = 0;
            else
                d[i][j] = 10000;
        }
    } // 배열 초기화



    for (int i = 0; i < M; ++i) {
        cin >> a >> b;
        a--; // 0번째 인덱스부터 사용
        b--;
        d[a][b] = 1;
        d[b][a] = 1;
    }


    floyd();


    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            kebin_baycon[i] += d[i][j];
        }
        if(kebin_baycon[i] < min) {
            ans = i;
            min = kebin_baycon[i];
        }
    }

    cout << ans+1 << endl;
}