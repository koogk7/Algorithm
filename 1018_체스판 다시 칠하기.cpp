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


using namespace std;


int n,m;
char box[51][51];
struct point {
    int row, col;
};

int getChangeSquaer(point start, point end){

    int whiteStartCnt = 0;
    int blackStartCnt = 0;

    for (int i = start.row; i < end.row + 1; ++i) {
        for (int j = start.col; j < end.col + 1; ++j) {
            // start white
            if((i+j) % 2 == 0 && box[i][j] != 'W')
                whiteStartCnt++;
            if((i+j) % 2 == 1 && box[i][j] != 'B')
                whiteStartCnt++;

            //start black
            if((i+j) % 2 == 0 && box[i][j] != 'B')
                blackStartCnt++;
            if((i+j) % 2 == 1 && box[i][j] != 'W')
                blackStartCnt++;
        }
    }

    return min(whiteStartCnt, blackStartCnt);

}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    char input;
    int ans = 987654321;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> box[i][j];
        }
    }

    for (int i = 0; i < n - 8 + 1; ++i) {
        for (int j = 0; j < m - 8 + 1; ++j) {
            point start = {i,j};
            point end = {i+7, j+7};
            ans = min(ans, getChangeSquaer(start, end));
        }
    }


    cout << ans << endl;

}

