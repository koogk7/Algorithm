#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

bool issued1[16]; // column 체크
bool issued2[40]; // \ 방향 체크 row+col
bool issued3[40]; // / 방향 체크 row-col+N


int cnt = 0;
int n;

void BackTracking(int row)
{
    if(row == n) {
        cnt++;
        return;
    }

    for (int i = 0; i < n; ++i) {
        if(issued1[i] or issued2[row+i] or issued3[row-i+n]) // 유망성 체크
            continue;
        issued1[i] =1;
        issued1[row+i] =1;
        issued1[row-i+n] =1; //방문 체크
        BackTracking(row+1); // dfs
        issued1[i] = 0;
        issued1[row+i] = 0;
        issued1[row-i+n] =0; //방문 해제


    }
}


int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    BackTracking(0);
    cout << cnt;
}