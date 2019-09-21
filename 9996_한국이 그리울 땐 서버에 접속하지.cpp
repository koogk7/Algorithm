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
#include <set>
#include <sstream>
#include <string.h>
using namespace std;
typedef long long ll;

/*
 * 1744 수묶기
 *
 * 양수만 있을 때 --> 무조건 큰수끼리 묶는게 최고
 * 양수, 음수 존재 --> 정렬해서, 음수끼리 묶고, 양수끼리 묶고 절대값 기준으로!
 */

int n;
string pattern;


int main(){

    cin >> n;
    cin >> pattern;

    string left, right;
    string file;

    int i = 0;

    for (i = 0; pattern[i] != '*'; ++i) {
        left+= pattern[i];
    }

    i++;

    for (i; i < pattern.size(); ++i) {
        right += pattern[i];
    }

    reverse(right.begin(), right.end());

    for (int i = 0; i < n; ++i) {
        cin >> file;
        int left_size = left.size();
        int right_size = right.size();

        if(file.substr(0,left_size) != left) {
            cout << "NE" << "\n";
            continue;
        }

        string file_right = file.substr(left_size, file.size());
        reverse(file_right.begin(), file_right.end());

        if(file_right.substr(0, right_size) == right)
            cout << "DA" << "\n";
        else
            cout << "NE" << "\n";

    }

}

