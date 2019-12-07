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
 * 1405 미친 로봇 ( copy code : http://blog.naver.com/PostView.nhn?blogId=kks227&logNo=220620727135)
 * - N이 14, 전체 탐색 사이즈 : 4^14 = 2^10*2^10*16 --> 완탐
 * - 가운데 좌표에서 시작
 * - 양쪽 방향으로 14만큼 움직을 수 있으므로 전체 판의 가로, 세로는 14*2 + 1이 되야한다.
 *
 * 풀이비교
 *  - 내 풀이
 *      backTracking(vector<int> path)
 *      1. 경로선택
 *      2. 단순체크
 *      3. 확률 계산 리턴
 *
 *  - 배운 점
 *      - 시작 좌표를 중앙에 두고 시작할 생각을 못했다.
 *      - 경로를 다 지정한 후 확률 계산을 한 뒤 더 할 생각이었다 --> 단순하지 않은 경로도 탐색하게 됨, 계산 자체도 틀림
 *      - 오차범위를 10^-9까지 허용함으로, 10^10까지 출력해야한다. 기본 출력은 여섯째자리까지만 출력된다.
 */
const int dr[] = {0,0,1,-1};
const int dc[] = {1,-1,0,0};

double probability[4];
bool visit[29][29];

// 현재 row행 col 열에 있고 remainMoveCnt 번 더 이동 할 수 있
double backTracking(int row, int col, int remainMoveCnt){
    // 탐색을 하지 않음으로 항상 단순
    if(remainMoveCnt == 0) return 1.0;

    visit[row][col] = true;
    double ret = 0.0;

    for (int i = 0; i < 4; ++i) {
        int nr = row + dr[i];
        int nc = col + dc[i];
        if(visit[nr][nc]) continue;
        ret += probability[i] * backTracking(nr,nc, remainMoveCnt-1);
    }

    visit[row][col] = false;
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n;

    cin >>n;
    for (int i = 0; i < 4; ++i) {
        cin >> probability[i];
        probability[i] /= 100.0;
    }
    cout.precision(10); // 출력 소숫점
    cout << fixed << backTracking(14,14, n); // 가운데 좌표부터 시
}









