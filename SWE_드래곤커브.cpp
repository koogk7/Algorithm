#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <set>
#include <stack>


using namespace std;

struct point{
    int row, col;
};
int dr[] = {0,-1,0,1};
int dc[] = {1,0,-1,0};
int n;
int visit[102][102];
int answer;

void MakeDC(vector<point>& dragon_curve ,int gene){
    int make_num = gene;
    while(make_num--){
        int dsize = dragon_curve.size();
        point pivot = dragon_curve.back();
        for (int i = dsize - 2; i >= 0 ; i--) {
            // 원점이동 -> 회전이동 -> 원점이동 후 삽입
            int move_row = pivot.row - pivot.col + dragon_curve[i].col;
            int move_col = pivot.row + pivot.col - dragon_curve[i].row;
            dragon_curve.push_back({move_row,move_col});
        }
    }
}

int main() {

    cin >> n;
    int x,y,d,g;
    for (int i = 0; i < n; ++i) {
        cin >> x >> y >> d >> g;
        vector<point> _dragon_curve;
        _dragon_curve.push_back({y,x});
        _dragon_curve.push_back({y+dr[d],x+dc[d]});

        MakeDC(_dragon_curve,g);
        for(auto i : _dragon_curve) {
            visit[i.row][i.col] = 1;
        }

    }
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            if(visit[i][j] && visit[i][j+1]
            && visit[i+1][j] && visit[i+1][j+1])
                answer++;
        }
    }

    cout << answer << endl;


}

