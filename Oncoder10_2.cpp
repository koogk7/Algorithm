#include <vector>
using namespace std;
 
//핵심 소스코드의 설명을 주석으로 작성하면 평가에 큰 도움이 됩니다.
// k개를 고를 때는 1~k의 종류들을 모두 포함해야함
// 같은 종류의 사탕을 두개 고를 수는 없다
// 같은 종류의 사탕이라도 서로 다른 경우로 취급
class Solution{
public:
    int solution(vector<int> type){
        int count_candy[52] = {0,};        
        int k = 1;
        int ans = 0;
        int temp = 1;
        for (auto i : type) {
            count_candy[i]++;
        }
        
    //   for(int i = 1; i< type.size()+1; i++)
    //   {
    //       cout << count_candy[i] << ' ';
    //   }
       cout << endl;
        int i = 1;
        while(temp != 0)
        {
            for(int j = 1 ; j< i+1; j++){
                temp = temp * count_candy[j];
            }
            if(temp == 0)
                break;
            // cout << "temp : " << temp <<endl;
            ans += temp;
            temp = 1;
            i++;
        }
        // cout << ans;
        return ans;
    }
};