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

/*
 * 2304 창고다각형 실패 회고
 *  - 가장 높은 기둥을 기준으로 왼쪽과 오른쪽을 나눔
 *  - 각 방향 끝부터 높은 기둥쪽으로 탐색하면서 자기보다 높은 기둥을 만날시에 넓이를 구해줌
 *  - 알고리즘이 코드를 짜다가 굉장히 꼬임... 그렇게 로직이 복잡해지고 알고리즘이 명확해지지가 않음
 *  - 알고리즘을 처음에 분명하게 설계하고 코드를 짜자!
 *
 * 뻘짓 회고
 *  - 정렬을 하기 전에 leftMax, rightMax를 구하고 있었다
 *  - leftMax, rightMax를 인덱스로 받고 있었다..... 조심좀 하자!
 *
 */


using namespace std;

struct point{
    int postion, height;
};

int n;
int ans;
int maxHeight;
int leftMax = -1;
int rightMax = -1;
point stickList[1003];
stack<point> st;

int getArea(){

    int rst = 0;

    while(st.size() > 1){
        point stTop = st.top();
        st.pop();
        int height = st.top().height;
        int width = abs(stTop.postion - st.top().postion);
        rst += height * width;
    }
    st.pop();

    return rst;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for (int i = 0; i < n; ++i) {
        cin >> stickList[i].postion >> stickList[i].height;
        if(maxHeight < stickList[i].height){
            maxHeight = stickList[i].height;
        }
    }

    sort(stickList, stickList + n, [](point a, point b){
        return a.postion < b.postion;
    });

    for (int i = 0; i < n; ++i) {
        if(maxHeight == stickList[i].height && leftMax == -1)
            leftMax = stickList[i].postion;
        if(maxHeight == stickList[i].height)
            rightMax = stickList[i].postion;
    }


    st.push(stickList[0]);
    // 왼쪽부터 탐색
    for (int i = 1; i < n; ++i) {
        if(st.top().height < stickList[i].height)
            st.push(stickList[i]);
    }

    ans += getArea();


    st.push(stickList[n-1]);
    // 오른쪽 탐색
    for (int i = n-2; i >= 0; --i) {
        if(st.top().height < stickList[i].height)
            st.push(stickList[i]);
    }

    ans += getArea();

    int maxWidth = rightMax == leftMax ? 1 : rightMax - leftMax + 1;
    ans += maxHeight * maxWidth;


    cout << ans;


}

