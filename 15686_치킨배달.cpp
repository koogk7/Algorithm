#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>

/*
 * 치킨 거리 : 집가 가장 가까운 치킨집 사이의 거리
 * 도시의 치킨거리는 모든 집의 치킨 커리의 합, ---> 치킨거리는 집의 수와 동일
 * 0은 빈칸, 1은 집, 2는 치킨집
 * 도시에 있는 치킨 집중 최대 M개를 고르고, 나머지 페업
 * 치킨거리가 가장 작게 되야함
 * 가장~~ --> 최단경로 혹은 그리디 일 가능성이 높아
 * 핵심은 치킨집을 골라내는 것!
 * 어떤  치킨집을 없앨거야? ---> 치킨점수를 매겨서 낮은 순으로!
 * 치킨점수는 어떻게? 치킨거리의 기준이되면 +1
 * 치킨거리가 같은 녀석에 대해 어떻게 우선순위??? 0--->  여기서 막힘.... 완전탐색!
 *
 *
 * */
using namespace std;

struct point{
    int row, col;
};

int N,M;
int box[52][52];
int ans = 1000000; // 도시 치킨거리의 최솟값


vector<point> chiken_store ; // 치킨가게 좌표 저장
vector<vector<int>> chiken_dist ; // 치킨거리 저장
vector<point> house ; // 집 좌표 저장
vector<int> open;



void BackTracking(int cur_num, int cnt) // cur_num : 선택할 가게 번호, cnt : 현재 선택된 가게 갯수
{

    if(cur_num >= chiken_store.size()) return; // 가게번호가 치킨가게보다 커졌을 때

    if(cnt == M) // M개 만큼 열었을 때
    {
        int cmp = 0;
        

        for (int i = 0; i < house.size(); ++i) {
            int dist = 100000;
            for (int j = 0; j < chiken_store.size(); ++j) {
                if(open[j]) {// 선택된 가게에 대하여, 최소 치킨거리 체크
                    int d = chiken_dist[i][j];
                    dist = min(d,dist);
                }
            }
            cmp += dist;// 각 집에서 치킨거리++,
        }
        ans  = min(ans,cmp);

        return;
    }

    for (int k = cur_num; k < chiken_store.size(); ++k) { // 조합
        if(open[k] == 0) {
            open[k] = 1; // 현재 가게 선택
            BackTracking(k, cnt + 1);
            open[k] = 0; // 선택취소
        }
    }

}


int main()
{
    cin >> N >> M;

    for (int i = 0; i <N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> box[i][j];
            if(box[i][j] == 2) {
                chiken_store.push_back({i, j});
                open.push_back(0);
            }
            if(box[i][j] == 1)
                house.push_back({i,j});
        }
    } // 입력

    for (int i = 0; i < house.size(); ++i) {
        vector<int> dist;
        for (int j = 0; j < chiken_store.size(); ++j) {
            int distance = abs(house[i].row-chiken_store[j].row)
                           + abs(house[i].col-chiken_store[j].col);
            dist.push_back(distance);
        }

        chiken_dist.push_back(dist);
    }

//    for (int i = 0; i < house.size(); ++i) {
//        for (int j = 0; j < chiken_store.size(); ++j) {
//            cout << chiken_dist[i][j] << " ";
//        }
//        cout << endl;
//    }
//
//


    BackTracking(0,0);

    cout << ans << '\n';

    return 0;





}