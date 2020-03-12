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

#include <string>
#include <vector>
#include <map>


string solution(vector<string> participant, vector<string> completion) {
    string answer = "";
    map<string, int> checker;

    for (int i = 0; i < completion.size(); ++i) {
        checker[completion[i]]++;
    }

    for (int i = 0; i < participant.size(); ++i) {
        if(checker[participant[i]]){
            checker[participant[i]]--;
        } else {
            answer = participant[i];
            break;
        }
    }

    return answer;
}
using namespace std;

int main() {
//    ios::sync_with_stdio(false);
//    cin.tie(NULL);

}









