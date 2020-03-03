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

/* 1343 폴리오미노
 * 난이도 하
 *
 */

int n;
int cnts[501];
string input;

string ReplaceAll(string &str, const string& from, const string& to){
    size_t start_pos = 0; //string처음부터 검사
    while((start_pos = str.find(from, start_pos)) != std::string::npos)  //from을 찾을 수 없을 때까지
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // 중복검사를 피하고 from.length() > to.length()인 경우를 위해서
    }
    return str;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> input;
    string ans;
    ans = ReplaceAll(input, "XX", "BB");
    ans = ReplaceAll(ans, "BBBB", "AAAA");
    for (int i = 0; i < ans.size(); ++i) {
        if(ans[i] == 'X'){
            cout << -1 << endl;
            return 0;
        }
    }
    cout << ans;

}










