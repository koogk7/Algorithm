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

/*
 * 1780 종이의 개수
 * - 분할정복
 * - 시작 좌표를 선정하는 것이 핵심
 */

int n;
int ans[3];
int paper[2200][2200];

void cutPaper(int startRow, int startCol, int paperSize){
    bool isAllSame = true;
    int cache = paper[startRow][startCol];
    int nextSize = paperSize/3;

    for (int i = startRow; i < startRow + paperSize; ++i) {
        for (int j = startCol; j < startCol + paperSize; ++j) {
            if(cache == paper[i][j]) continue;
            isAllSame = false;
            break;
        }
    }

    if(isAllSame)
        ans[cache+1]++;
    else{
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cutPaper(nextSize*i + startRow, nextSize*j + startCol, nextSize);
            }
        }
    }

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> paper[i][j];
        }
    }

    cutPaper(0,0,n);
    for(auto item : ans)
        cout << item << "\n";
}









