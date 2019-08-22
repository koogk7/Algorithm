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
#include "typeinfo"




using namespace std;

/*
 * 2565 전깃줄
 *  - 문제를 잘 살펴보면 결국 LIS 문제이다.
 *  - 중간에 말려서 계속 답이 맞게 나오는데 안 나온다고 삽질하고 있었다.
 */

int n;
struct line{
    int numA, numB;
};
vector<line> lines;
int lastMinDigit[101];
int last;


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    int numA, numB;
    for (int i = 0; i < n; ++i) {
        cin >> numA >> numB;
        lines.push_back({numA, numB});
    }

    sort(lines.begin(), lines.end(), [](line a, line b){
        return a.numA < b.numA;
    });


    for (int i = 0; i < n; ++i) {
        if(lastMinDigit[last] == lines[i].numB) continue;
        if(lastMinDigit[last] < lines[i].numB) lastMinDigit[++last] = lines[i].numB;
        else{
            int lowerBound = int(lower_bound(lastMinDigit, lastMinDigit+last, lines[i].numB) - lastMinDigit);
            lastMinDigit[lowerBound] = lines[i].numB;
        }
    }


    cout << n - last << "\n";

}

