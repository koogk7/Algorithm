#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <set>


using namespace std;

/*
 *  각각의 일꾼은 가로로 연속되도록 m개의 벌통을 채취
 *  단 두명의 일꾼이 벌통이 겹치면 안됨, 꿀은 한번에 채취해야한다
 *  꿀의 제곱만큼 수익이 생김
 *  수익의 합이 최대가 되는 경우를 찾고 이 때의 수익을 출력
 *
 *  1. 두명의 일꾼의 벌통이 겹치면 안됨
 *  2. C라는 최대용량이 정해져있음
 *
 * */

int n,m,c,t;
int box[12][12];
int d[12][12];

// 최대값 계산하기
int calc(vector<int>& v, int n , int sum , int val){
    if(sum > c) return 0;
    if(n == v.size()) return val;

    return max( calc(v,n+1,sum+v[n],val + v[n]*v[n]),
                calc(v, n+1, sum, val));
}

// 최대값 찾기
int getMaxPrice(int row, int col){
    vector<int> v;
    for (int i = 0; i < m; ++i) {
        v.push_back((box[row][col+i]));
    }
    return calc(v,0,0,0);
}

int dfs(int row, int col){
    int ans = 0;

    //같은 라인
    for (int i = col+m; i < n-m+1; ++i) {
        ans = max(ans,d[row][i]);
    }

    //다음라인
    for (int i = row+1; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ans = max(ans, d[i][j]);
        }
    }
    return ans;
}


int main(){

    cin >> t;
    int num = 0;
    while(t--){
        num++;
        cin >> n >> m >> c;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> box[i][j];
                d[i][j] = 0;
            }
        }

        // d배열에 현재칸부터 m칸까지의 최대값을 저장
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n-m +1; ++j) {
                d[i][j] = getMaxPrice(i,j);
            }
        }

        // i,j를 선택한 상태에서 찾을 수 있는 나머지에 대해
        // 비교하여 최대값 찾는다.
        int res = 0;
        for (int i = 0; i < n; ++i) {x
            for (int j = 0; j < n-m+1; ++j) {
                res = max(res, dfs(i,j) + d[i][j]);
            }
        }

        cout << "#"<<num <<" "<<res << endl;


    }

}

