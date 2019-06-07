#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <set>


using namespace std;

/*
 * 우선순위 큐를 쓰자!
 * 배열 끝에서부터 하나씩 큐에 넣고, top 값을 가져와서 현재 배열과 값비교
 * 0보다 크면 ans에다가 +
 * */

int t, n;
int info[1000002];

long ans;

int main() {

    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cin >> t;
    int k = 0;
    while(t--){
        k++;
        cin >> n;
        priority_queue<int> pque;
        ans = 0;
        for (int i = 0; i < n; ++i) {
            cin >> info[i];
        }

        for (int i = 0; i < n; ++i) {
            pque.push(info[n-1-i]);
            int profit = pque.top() - info[n-1-i];
            ans = profit > 0 ? ans+profit : ans;
        }

        cout <<"#" << k << " " <<ans << endl;

    }
}

