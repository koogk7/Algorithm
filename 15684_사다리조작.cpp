#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <set>


/*
 * 회고 :
 * 문제 n,m,h를 잘못 이해해서, 한참 해맸다.
 * */

using namespace std;


int n, m, h;
int box[31][12];
int ans = -1;
int target = 0;



bool Play()
{
    for (int i = 1; i <= n; ++i) {
        int current = i;
        for (int j = 1; j <= h; ++j) {
            if(box[j][current] == true)
                current += 1;
            else if(current-1 > 0 && box[j][current-1] == true)
                current -= 1;
        }

        if(i == current)
            continue;
        else
            return false;
    }

    return true;
}


void Combi(int row, int cnt)
{
    if(ans != -1) return;
    if(cnt == target)
    {
        if(Play()) ans = cnt;
        return;
    }

    for (int i = row; i <= h; ++i) {
        for (int j = 1; j < n; ++j) {
            if(box[i][j] == 1) continue; // 사다리를 놓지 않은 경우
            if(box[i][j-1] == 1 || box[i][j+1] == 1) continue; // 연속
            box[i][j] = 1;
            Combi(i,cnt+1);
            box[i][j] = 0;

        }
    }
}


int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m >> h;
    int a, b;
    for (int i = 0; i < m; ++i) {
        cin >> a>> b;
        box[a][b] = 1;
    }

    for (int j = 0; j < 4; ++j) {
        target = j;
        Combi(1,0);
        if(ans != -1) break;
    }

    cout << ans << endl;



}

