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
#define MAX 123456789

/*
 * 7662 우선순위큐 실패
 *  - 최댓값 범위 잘 지정하기!
 */


int main(){
   int n;
   cin >> n;

   vector<int> end_name;

   // n = 10^4, n^2 = 10^8, 이중루프
    for (int i = 666; i < MAX; ++i) { // n번째 영화제목
        string number_str = to_string(i);
        int seq_six = 0;

        for (int j = 0; j < number_str.size(); ++j) { // i가 종말번호인지 체크

            if(number_str[j] == '6')
                seq_six++;
            else
                seq_six = 0;

            if(seq_six == 3) {
                end_name.push_back(i);
                break;
            }

        }

        if(end_name.size() == n){
            cout << end_name[end_name.size() - 1];
            break;
        }
    }

//    for(auto i : end_name) cout << i << " ";




}

