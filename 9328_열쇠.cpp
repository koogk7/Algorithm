// ConsoleApplication2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <stack>
#include <map>
#include <set>

using namespace std;

typedef long long ll;

/*
 * 9328 열쇠
 * - 빌딩에 침입해 문서를 가져오고 싶다
 * - 문을 열려면 열쇠가 필요, 일부 열쇠는 가지고 있다.
 * - 일부 열쇠는 빌딩 바닥의 놓여져 있다.
 * - 상근이가 훔칠 수 있는 문서의 최대 갯수
 * - 상근이는 빌딩 밖으로 나갈 수 있다.
 * - 열쇠는 여러 번 사용 할 수 있다.
 *
 *
 * 삽질
 *  - 계속 로직이 바뀌니 어디가 잘못됬는지 찾기가 힘들다
 *  - 처음에 로직을 잘 설정하자
 *  - 시작 지점 미스, 순간이동하고 있었음
 *  - 테두리에 있는 문 지점을 계속 버리고 있었다.
 *
 *
 */

#define MAX_N 68
#define INF 123456789123

int T, h, w;
char building[101][101];
bool visit[101][101];
map<char, bool> openDoors;
struct point{
    int row, col;
};
int dr[] = {-1,1,0,0};
int dc[] = {0,0,-1,1};
vector<point> startPoints;
map<char, vector<point>> doorPositions;
int ans = 0;

bool isBoundary(int r, int c){
    return r==0 or r==h-1 or c == 0 or c == w-1;
}

bool isInBoundary(int r, int c){
    return r>=0 and r<h and c>=0 and c<w;
}

bool isUpper(char a){
    return a != '.' and a != '$' and a != '*' and a == toupper(a);
}

void BFS(int startRow, int startCol){
    if(visit[startRow][startCol])
        return;

    queue<point> que;
    que.push({startRow, startCol});
    visit[startRow][startCol] = true;

    char door = toupper(building[startRow][startCol]);
    openDoors[door] = true;

    for(auto item : doorPositions[door]){
        visit[item.row][item.col] = true;
        que.push(item);
    }


    while(!que.empty()){
        int row = que.front().row;
        int col = que.front().col;
        que.pop();

        if(building[row][col] == '$')
            ans++;

        for (int i = 0; i < 4; ++i) {
            int nr = row + dr[i];
            int nc = col + dc[i];

            if(!isInBoundary(nr,nc))
                continue;
            if(building[nr][nc] == '*')
                continue;
            if(visit[nr][nc])
                continue;
            if(isUpper(building[nr][nc]) and !openDoors[building[nr][nc]]){ // 잠긴 문을 만났을때
                doorPositions[building[nr][nc]].push_back({nr,nc});
                continue;
            }

            visit[nr][nc] = true;
            que.push({nr,nc});
            char queIndoor = toupper(building[nr][nc]);
            openDoors[queIndoor] = true;

            for(auto item : doorPositions[queIndoor]){
                visit[item.row][item.col] = true;
                que.push(item);
            }

        }
    }
}


int main() {
    cin >> T;

    while(T--){
        cin >> h >> w;

        string input;
        openDoors = map<char, bool>();
        startPoints = vector<point>();
        doorPositions = map<char, vector<point>>();
        memset(visit,0,sizeof(visit));
        ans = 0;

        for (int i = 0; i < h; ++i) {
            cin >> building[i];
        }

        cin>> input;

        // 열수 있는 문 체크
        for (int i = 0; i < input.size(); ++i) {
            openDoors[toupper(input[i])] = true;
        }

        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                // 바운더리이고 대문자가 와 벽이 아닌 녀석들 삽입
                if(!isBoundary(i,j))
                    continue;

                if(!isUpper(building[i][j]) and building[i][j] != '*')
                    startPoints.push_back({i,j});
                else if(isUpper(building[i][j]) and openDoors[building[i][j]])
                    startPoints.push_back({i,j});
                else if(isUpper(building[i][j]))
                    doorPositions[building[i][j]].push_back({i,j});
            }
        }


        for(auto item : startPoints){
            BFS(item.row, item.col);
        }

        cout << ans << "\n";

    }

}


