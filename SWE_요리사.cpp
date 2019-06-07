#include <stdio.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <stack>
#include <string.h>
#include <queue>
#include <set>
using namespace std;

#define MA 10000000

int T,n;
int map[18][18];
int ans;


int getGap(vector<int>& arr){
    int a = 0;
    int b = 0;
    int bidx = 0;
    vector<int> brr = vector<int>(n/2,-1);
    for (int i = 0; i < n; ++i) {
        bool flag = true;
        for (int j = 0; j < n/2; ++j) {
            if(arr[j] == i) flag = false;
        }
        if(flag){
            brr[bidx++] = i;
        }
    }


    for (int k = 0; k < n/2; ++k) {
        int arow = arr[k];
        int brow = brr[k];
        for (int i = 0; i < n/2; ++i) {
            a += map[arow][arr[i]];
            b += map[brow][brr[i]];
        }
    }

    return abs(a-b);
}


int BackTracking(int idx, int cnt, vector<int>& select)
{
    if(cnt == n/2){
        return getGap(select);
    }
    if(idx >= n){
        return MA;
    }
    int ret = MA;


    select[cnt] = idx;
    ret = min(ret, BackTracking(idx+1,cnt+1,select));
    select[cnt] =  -1;

    ret = min(ret, BackTracking(idx+1,cnt,select));

    return ret;
}


int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cin >> T;

    for (int t = 0; t < T; ++t) {
        cin >> n;
        vector<int> sel = vector<int>(n/2,-1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> map[i][j];
            }
        }

        cout << "#" << t+1 << " " << BackTracking(0,0, sel)  << endl;
    }


}
