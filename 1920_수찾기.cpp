#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
/*
 *
 * */



using namespace std;

int n,m;
struct key{
    int value;
    bool is;
};
vector<int> source;
vector<int> target;


void BSearch(vector<int>& ar, int first, int last, int target)
{
//    cout << first << " " << last << " "<< target << endl;
    int mid = (first+last)/ 2;
    if( last - first <= 1) {
        if(ar[first]==target||ar[last]==target)
            cout << "1" << "\n";
        else cout << "0" <<"\n";
        return;
    }
    if(ar[mid] == target) {
        cout << "1" << "\n";
        return;
    }
    if(ar[mid] > target){
        BSearch(ar,first, mid,target);
    }
    else
        BSearch(ar,mid,last,target);
}


int main(){

    int temp;
    int mid;

    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;


    for (int i = 0; i < n; ++i) {
        cin >> temp;
        source.push_back(temp);
    }
    sort(source.begin(), source.end());
    cin >> m;

    for (int i = 0; i < m; ++i) {
       cin >> temp;
       BSearch(source,0,n-1,temp);
    }



}

