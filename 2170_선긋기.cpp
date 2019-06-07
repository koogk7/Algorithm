#include <stdio.h>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;


int n;
struct line{
    int s, e;
};
vector<line>lines;

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    lines = vector<line>(n);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        cin >> lines[i].s >> lines[i].e;
    }
    sort(lines.begin(), lines.end(), [](line a, line b){
        return a.s < b.s;
    });
    line target = lines[0];

    for (int i = 1; i < n; ++i) {
        if(target.e < lines[i].s){
            ans += target.e- target.s;
            target.s = lines[i].s;
            target.e = lines[i].e;
        }
        else if(target.e < lines[i].e){
            target.e = lines[i].e;
        }
    }
    ans +=  target.e - target.s;

    cout << ans << endl;

}
