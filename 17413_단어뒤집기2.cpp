#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <stack>
#include <map>
#include <set>
#include <math.h>

typedef long long ll;


#define MAX_N 68
#define INF 987654321



using namespace std;

/* 17413 단어 뒤집기2
 */

struct Item {
    bool isTag;
    string word;
};

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
//    ios::sync_with_stdio(false);
//    cin.tie(NULL);
    string inputs, ans, buf;
    queue<Item> que;
    bool isTag = false;
    getline(cin, inputs);

    for (int i = 0; i < inputs.size(); ++i) {
        if(isTag and inputs[i] == '>'){
            que.push({true, buf});
            buf = "";
            isTag = false;
        } else if (!isTag and (inputs[i] == ' ' || inputs[i] == '<')){
            que.push({false, buf});
            buf = "";
        } else if(isTag) {
            buf += inputs[i];
        } else {
            buf = inputs[i] + buf;
        }

        if(inputs[i] == '<') isTag = true;
    }

    if(buf != "") que.push({false, buf});

    while(!que.empty()){
        if(que.front().isTag)
            ans += "<" + que.front().word + ">";
        else
            ans += que.front().word;
        ans += ",";
        que.pop();
    }

    ans = ReplaceAll(ans, ",<", "<");
    ans = ReplaceAll(ans, ">,", ">");
    ans = ReplaceAll(ans, ",", " ");
    ans[0] == ' ' ? ans = ans.substr(1,ans.size()-2) : ans = ans;
    cout << ans;

}









