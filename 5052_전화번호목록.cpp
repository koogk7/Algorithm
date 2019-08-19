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

/*
 * 5052번 전화번호 목록
 *  - 한 시간동안 고민했다. 처음에 Redix Sort를 이용해서 무언가를 해볼려고 했으나 쉽지 않았다.
 *  - 결국 정답을 찾아봤고, map을 평소에 자주 사용해봤다면 쉽게 풀 수 있는 문제였다. map을 사용하는 문제를 몇 개 더 풀어보자
 */

int t,n;
string num[10001];



int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> t;

    while(t--){
        cin >> n;
        map<string, bool> mp;

        for (int i = 0; i < n; ++i) {
            cin >> num[i];
        }

        sort(num, num + n, [](string a, string b){
            return a.size() < b.size();
        });

        mp[num[0]] = true;
        bool ans = true;

        for (int i = 1; i < n; ++i) {
            for (int len = 1; len < 11; ++len) {
                if(mp[num[i].substr(0, len)] == 1){ // substr(a, n) : a부터 a+n-1까지
                    ans = false;
                    break;
                }
            }
            mp[num[i]] = true;
        }

        if(ans)
            cout << "YES" << "\n";
        else
            cout << "NO" << "\n";

    }

}

