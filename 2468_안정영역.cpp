#include <iostream>
#include <algorithm>
#include <queue>

/*
 * h를 2부터 n-1까지 선형적으로 올려가면서, 해당 이하의 높이를 cbox에 0로 마킹
 * cbox에서 0이 아닌 좌표에 대해 dfs 탐색, 탐색완료공간은 -k으로 마킹, k는 몇 번째 안전한 구역인지 나타냄
 * h for문이 한번 종료될때마다 k를 확인하고 ans값을 갱신, 다시 k을 초기화, cbox 초기화
 * */

using namespace std;

int box[101][101];
int cbox[101][101]; // clone box
int d_row[] = {-1,1,0,0};
int d_col[] = {0,0,-1,1};
int N;
int max_h = 0;
int k = 0;
int ans ;

bool isBoundary(int row, int col)
{
    bool isRow = row >=0 && row < N;
    bool isCol = col >=0 && col < N;

    return isRow && isCol;
}

void dfs(int row, int col)
{
    cbox[row][col] = k; // 방문 마킹
    int nrow, ncol;

    for (int i = 0; i < 4; ++i) {
        nrow = row + d_row[i];
        ncol = col + d_col[i];

        if(!isBoundary(nrow,ncol)) continue;
        if(cbox[nrow][ncol] > 0)
                dfs(nrow,ncol);
    }

}

void Solution()
{
    for (int h = 1; h < max_h; ++h) { // 물 높이
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if(box[i][j] <= h)
                    cbox[i][j] = 0; // 높이보다 낮다면 침수
                else
                    cbox[i][j] = box[i][j];
            }
        }
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if(cbox[i][j] > 0) { // 침수되지 않고, 방문하지 않은 노드
                    k--;
                    dfs(i, j);
                }
            }
        }
//        ---------------Print----------------
//        for (int i = 0; i < N; ++i) {
//            for (int j = 0; j < N; ++j) {
//                cout << cbox[i][j] << " ";
//            }
//            cout << endl;
//        }
//        cout << "K : " << k <<endl;
//        cout << "--------------------------" <<endl;
        if(ans < -k)
            ans = -k;
//        ans = max(ans,-k);
        k = 0;

    }
}



int main()
{
    cin >> N;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> box[i][j];
            if(max_h < box[i][j])
                max_h = box[i][j];
        }
    }

    Solution();

    if(ans == 0)
        ans = 1;
    cout << ans << endl;

    return 0;

}