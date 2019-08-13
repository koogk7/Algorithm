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

/* 10942번 팰린드롬?
 *  - 처음에는 dp에 단순히 for문으로 stack으로 팰린드롬을 채우고 시작했다.
 *  dp에 값채우는 걸 시간복잡도 계산을 안해서 시간초과가 났다.
 *  - 해서 dp를 어떻게 고민하다 양쪽에서 하나씩 줄여가면서 dp에
 *  저장하고, 팰린드롬 검사를 양쪽 끝에서 하나씩 체크하면서 진행했다.
 */


using namespace std;


int n,m;
int seq[2001];
int dp[2001][2001]; // dp[start][end] : start~end 가 팰린드롬인지;


bool isPalindrom(int s, int e){
    stack<int> st;
    bool isOdd = (s+e+1) % 2;
    int mid = (s+e) / 2;

    for (int i = s; i < e+1; ++i) {
        if(isOdd and i == mid) continue;
        if(!st.empty() and st.top() == seq[i]) st.pop();
        else st.push(seq[i]);
    }

    return st.empty();

}

int DFS(int s, int e){
    if(s >= e)
        return 1;
    int &ret = dp[s][e];
    if(ret != 0)
        return ret;

    if(seq[s] != seq[e]){
        ret = 0;
    } else {
        ret += DFS(s+1, e-1);
    }

    return ret;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int start, end;

    memset(dp,0,sizeof(dp));
    cin >> n;
    for (int i = 1; i < n+1; ++i) {
        cin >> seq[i];
    }

//    for (int i = 1; i < n+1; ++i) {
//        for (int j = 1; j < n+1; ++j) {
//            dp[i][j] = isPalindrom(i,j);
//        }
//    }


    cin >> m;

    for (int i = 0; i < m; ++i) {
        cin >> start >> end;
        cout << DFS(start,end) << "\n";
    }


}

