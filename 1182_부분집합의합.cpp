#include <stdio.h>
#include <iostream>

/*
 *
 * */



using namespace std;

int n, s;
int myset[22];
int used[22];
int ans;
int sum;

void BackTracking(int cur, int sum, int depth)
{
    if(cur > n) return;
    if(sum == s && cur == n){
        if(depth != 0)
            ans++;
        return;
    }


    BackTracking(cur+1,sum+myset[cur],depth+1); // 현재 원소를 씀
    BackTracking(cur+1,sum, depth);

}

int main(){

    cin >> n >> s;
    for (int i = 0; i < n; ++i) {
        cin >> myset[i];
        used[i] = 0;
    }

    BackTracking(0,0,0);

////-----------비트 마스킹----------------
//    for (int i = 1; i < (1<<n); ++i) {
//        sum = 0;
////        cout << "{ ";
//        for (int j = 0; j <n; ++j) {
//            if(i & (1<<j)){
//                sum += myset[j];
////                cout << myset[j] << ", ";
//            }
//        }
//        if(sum == s)
//            ans++;
////        cout << " } " << endl;
//    }
    cout << ans << endl;

}

