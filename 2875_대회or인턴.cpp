#include <stdio.h>
#include <iostream>

/*
 * 2명의 여학생, 1명의 남학생
 * 참여 학생중 k명은 반드시 인터쉽 프로그램에 참여
 * N,M 이 주어졌을 때 k명을 제외하고 가장 많은 팀을 만들 수 있으면 됨!
 * 팀의 수는 곧 남학생의 수와 똑같네?
 * 200명중의 3명을 뽑는 경우의 수는 200*199*191/ 6 --> 그렇게 크지 않아
 * 순서대로 M에서 1을 빼고, N에서 2를 빼, 그리고 N+M이랑 k랑 비교
 * k보다 크다면 계속 진행, k보다 작다면 stop, 그리고 M이 0이 되도 stop
 * */



using namespace std;


int n,m,k;
int ans;

void Solution()
{
    while(1)
    {
        if((k > n+m-3)) break; // N+M에서 3명을 뺐을 때 인턴십에 데리고 갈 녀석이 존재하니?
        if(m < 1) break; // 팀을 만들 수 있는 남자가 존재?
        if(n < 2) break; // 팀을 만들 수 있는 여자가 존재?
        n = n-2;
        m = m-1;
        ans++;

    }
}


int main(){

   cin >> n >> m >> k;
   Solution();
   cout << ans << endl;

}

