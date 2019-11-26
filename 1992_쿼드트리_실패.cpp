// ConsoleApplication2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef long long ll;

/*
 * 1992 쿼드트리
 * 1. 구간 나누기
 * 2. 구간마다 압축가능 확인
 * 3. 가능하면 압축 결과, 실패하면 해당 구간부터 다시 1번반복
 *
 * 압축 확인은 for문 순회, N*N = 2^12, 재귀 Depth = 2^6
 * 시간복잡도 2^6 * 2^ 12 = 2^8 * 1000
 *
 * 삽질회고
 *  구간을 나누는 좌표값을 잘못 설정하고 있었음
 *  모두 0이거나 1일 때 압축을 못했음
 *
 */

#define MAX_N 68
#define INF 987654321

int n;
int box[MAX_N][MAX_N];
struct point{
    int row, col;
};

int compact(vector<point>& subBox){
    point start = subBox[0];
    point end = subBox[1];

    int compactValue = box[start.row][start.col];

    for (int i = start.row; i < end.row + 1; ++i) {
        for (int j = start.col; j < end.col + 1; ++j) {
            if(compactValue != box[i][j])
                return -1;
        }
    }

    return compactValue;

}

string BackTracking(point start, point end){
    if(start.row == end.row and start.col == end.col)
        return to_string(box[start.row][start.col]);

    string ret = "";
    int centerRow = (start.row + end.row) / 2;
    int centerCol = (start.col + end.col) / 2;

    vector<point> leftUp = {{start.row, start.col}, {centerRow, centerCol}};
    vector<point> rightUp = {{start.row, centerCol + 1}, {centerRow, end.col}};
    vector<point> leftDown = { {centerRow + 1, start.col}, {end.row, centerCol}};
    vector<point> rightDown = {{centerRow + 1, centerCol+1}, {end.row, end.col}};
    vector<vector<point>> subBoxes = {leftUp, rightUp, leftDown, rightDown};

    for (int i = 0; i < 4; ++i) {
        int compactValue = compact(subBoxes[i]);
        if(compactValue > -1){
            ret += "" + to_string(compactValue) + "";
        } else{
            ret += "(" + BackTracking(subBoxes[i][0], subBoxes[i][1]) + ")";
        }
    }

    return ret;

}


int main() {
    cin >> n;
    char input;
    string ans = "";

    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < n + 1; ++j) {
            cin >> input;
            box[i][j] = input - '0';
        }
    }

    ans = BackTracking({1,1}, {n,n});

    if(ans.size() == 4){
        char beforValue = ans[0];
        string ret = "";
        ret += ans[0];
        for (int i = 1; i < 4; ++i) {
            if(beforValue != ans[i])
                ret += ans[i];
            beforValue = ans[i];
        }
        ans = ret;
    } else{
        ans = "(" + ans + ")";
    }


    cout << ans;
}


