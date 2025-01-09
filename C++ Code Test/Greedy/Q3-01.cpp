//모험가 길드
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    int N;
    cin >> N;
    vector<int> v;
    for(int i = 0, j; i < N; i++){
        cin >> j;
        v.push_back(j);
    }
    sort(v.begin(), v.end(), greater<int>());
    int cnt = 0;
    for(int i = 0; i < N; i++){
        ++cnt;
        i += v.at(i)-1;
    }
    cout << cnt;
}