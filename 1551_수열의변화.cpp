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

/* 1551 수열의 변화
 * N = 20
 *
 */


int n,k;
queue<int> a,b;

void execute(queue<int>& master, queue<int>& slave) {
    int before = master.front();
    master.pop();

    while(!master.empty()){
        slave.push(master.front() - before);
        before = master.front();
        master.pop();
    }
}

void print(queue<int>& que) {
    string ret = "";
    while(!que.empty()){
        ret += to_string(que.front());
        que.pop();
        if(!que.empty())
            ret += ",";
    }
    cout << ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;
    int input;
    char det;
    bool isTurnOfA = true;

    for (int i = 0; i < n; ++i) {
        if(i+1 == n)
            cin >> input;
        else
            cin >> input >> det;
        a.push(input);
    }

    while(k--){
        isTurnOfA ? execute(a,b) : execute(b,a);
        isTurnOfA = !isTurnOfA;
    }
        isTurnOfA ? print(a) : print(b);
}










