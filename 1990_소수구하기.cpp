#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <stack>
#include <map>
#include <set>

typedef long long ll;


#define MAX_N 68
#define INF 987654321



using namespace std;

/* 1990 소수구하기
 * 난이도 중
 *
 */

vector<string> prime;
map<string,int> palindrome;
vector<string> ans;

void getPrime(int begin, int end){
    // 소수이면 false
    // 소수가 아니면 true이다
    end = end > 10000000 ? 10000000 : end;
    bool *c = new bool[end+1];
    c[1] = true;

    for(int i = 2; i*i<= end; i++){
        if(!c[i]){
            for(int j = i * i; j <= end; j+=i){
                c[j] = true;
            }
        }
    }
    for(int i = begin; i <= end; i++)
        if(!c[i])
            prime.push_back(to_string(i));

    delete[] c;
}

int isPallindrome(string number){
    int &ret = palindrome[number];
    int len = number.size();

    if(number[0] != number[len-1]){
        ret = -1;
        return ret;
    }

    if(len < 2){
        ret = 1;
        return ret;
    }

    if(ret != 0)
        return ret;

    ret = isPallindrome(number.substr(1,len-2));
    return ret;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int begin, end;
    cin >> begin >> end;

    getPrime(begin,end);
    for (int i = 0; i < prime.size(); ++i) {
        if (isPallindrome(prime[i]) == 1) {
            ans.push_back(prime[i]);
        }
    }

    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] << endl;
    }
    cout << -1 << endl;

    return 0;
}










