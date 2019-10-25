// ConsoleApplication2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define INF 987654321
typedef long long ll;

/*
 * 1946 신입사원
 * 1. 서류 내림차순으로 정렬
 * 2. 면접 최대점수를 가지고 비교하면서 업데이트
 *
 * 회고
 *  - 문제를 잘못 이해해서, 최대증가순열로 착각
 */

#define MAX_N 100000
#define NINF -987654321
struct applicant{
    int paper, interview;
};

int main() {
    int t;
    cin >> t;

    while(t--){
        int n;
        int ans = 1;
        int maxInterview = 0;

        cin >> n;

        vector<applicant> peoples = vector<applicant>(n);

        for (int i = 0; i < n; ++i) {
            cin >> peoples[i].paper >> peoples[i].interview;
        }

        sort(peoples.begin(), peoples.end(), [](applicant a, applicant b){
            return a.paper < b.paper;
        });

        maxInterview = peoples[0].interview;

        for (int i = 1; i < n; ++i) {
            if(maxInterview > peoples[i].interview){
                maxInterview = peoples[i].interview;
                ans++;
            }
        }

        cout << ans << "\n";

    }

}


