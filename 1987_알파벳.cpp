#include <iostream>
#include <algorithm>

using namespace std;

int d_row[4] = {1,-1,0,0};
int d_col[4] = {0,0,1,-1};

int R, C;
int ans =0;
char box[20][20];
int alpha[26]; // A~Z


bool isBoundary(int row, int col)
{
    int isRow = row >=0  && row < R;
    int isCol = col>=0 && col < C;

    return isRow && isCol;
}

void dfs(int row, int col, int cnt)
{
    ans = max(ans,cnt);

    for (int i = 0; i < 4; ++i) {
        int nrow = row + d_row[i];
        int ncol = col + d_col[i];

       if(!isBoundary(nrow,ncol)) continue;

       int k = (int)box[nrow][ncol] - 65; // A = 65
       if(alpha[k]) continue;

       alpha[k]++;
       dfs(nrow,ncol,cnt+1);
       alpha[k]--;

    }
}

int main()
{
    cin>>R>>C;

    for(int i=0;i<R;i++)
        for(int j=0;j<C;j++){
            cin>>box[i][j];
        }

    alpha[(int)box[0][0]-65]++; //(0,0)지점 방문 체크
    dfs(0,0,1);

    cout<<ans<<endl;

}