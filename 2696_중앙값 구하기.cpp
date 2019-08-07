// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <queue>
#include <vector>
#include <string.h>
#include <algorithm>
#include <map>
#include <math.h>
#include <stack>

using namespace std;
#define MAX_N 100000

int T,m;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> T;

    while(T--){
        int seq[MAX_N];
        cin >> m;
        cout << (m+1) / 2 << endl;
        for (int i = 0; i < m; ++i) {
            cin >> seq[i];
            if(i%2 == 0) {
                sort(seq, seq + i + 1); // 마지막 원소보다 + 1 크게
                cout << seq[i/2]<< " ";
            }
        }
        cout << endl;
    }

}

