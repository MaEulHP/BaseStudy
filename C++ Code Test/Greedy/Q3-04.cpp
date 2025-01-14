#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int N;
    vector<int> coin;
    cin >> N;
    for(int i=0, j; i<N; i++){
        cin >> j;
        coin.push_back(j);
    }

    sort(coin.begin(), coin.end());
    int target = 1;
    for(auto x : coin){
        if(target < x){
            break;
        }
        target += x;
    }
    cout << target;
}   