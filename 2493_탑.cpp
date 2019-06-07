#include <stdio.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <stack>

using namespace std;


struct item{
    int value, index;
};
int n;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    stack<item> st;
    int ans[500000];
    fill(ans,ans+n,0);

    for (int i = 1; i <=n; ++i) {
        int temp;
        cin >> temp;
        if(st.empty()) {st.push({temp,i}); ans[i] = 0; continue;}
        if(temp < st.top().value){
            ans[i] = st.top().index;
            st.push({temp,i});
        }
        else{
            while(temp > st.top().value){
                st.pop();
                if(st.empty()){
                    ans[i] = 0;
                    st.push({temp,i});
                    break;
                }
            }
            if(st.top().value != temp){
                ans[i] = st.top().index;
                st.push({temp,i});
            }

        }
    }

    for (int i = 1; i < n+1; ++i) {
        cout << ans[i] << " ";
    }

}
