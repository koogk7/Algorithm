#include <vector>
using namespace std;
 
//핵심 소스코드의 설명을 주석으로 작성하면 평가에 큰 도움이 됩니다.
class Solution{
public:
    int solution(vector<int> marks){
        float target = 9.5;
        float cur_avg = 0;
        float total = 0;
        
        for (auto i : marks) {
            total += i;
        }
        cur_avg = total/ marks.size();
        if(cur_avg >= 9.5){
            cout << cur_avg;
            return 0 ;
        }
        int i = marks.size();
        while(cur_avg < 9.5)
        {
            // cout << " cur : " << cur_avg <<endl;
            total += 10;
            i++;
            cur_avg = total / i ;
        }
        // cout << cur_avg << endl;
        // cout << i-marks.size() << endl;
        return i-marks.size();
    }
};