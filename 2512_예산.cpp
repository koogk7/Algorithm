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
typedef long long ll;

int n,m;
int buket[10001];
ll remainBucket;
int maxRequest;

int BSearch(int start, int end, int target){ // start ~ end 사이의 target보다 최초로 큰 인덱스
    if(start >= end)
        return start;

    int mid = (start + end) / 2;
    if( buket[mid] < target ){
        return BSearch(mid+1, end, target);
    } else
        return BSearch(start, mid, target);
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);


    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> buket[i];
        maxRequest = max(maxRequest, buket[i]);
    }

    cin >> m;

    remainBucket = m;
    int s = 0;
    int e = n-1;
    int mean = m/n;

    sort(buket, buket + n);

    while(buket[s] < mean and s < e){
        int ns =  BSearch(s,e, mean);
        for (int i = s; i < ns; ++i) {
            remainBucket -= buket[i];
        }
        s = ns;
        mean = remainBucket / (e - s + 1);
    }

    if(mean <= buket[s])
        cout << mean;
    else {
        cout << buket[s] << "\n";
    }


}

