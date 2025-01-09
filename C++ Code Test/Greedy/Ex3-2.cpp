#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    unsigned int N, M, K;
    cin >> N >> M >> K;

    vector<int> v;
    for(int i = 0, j; i < N; i++){
        cin >> j;
        v.push_back(j);
    }
    sort(v.begin(), v.end(), greater<int>());

    int first = v.at(0);
    int second = v.at(1);
    int cnt = int(M / (K+1)) * K;
    cnt += M % (K+1);

    int result = 0;
    result += cnt * first;
    result += (M - cnt) * second;

    cout << result;
}