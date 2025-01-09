/*
한 행씩 최소값 찾기
최소값을 모아서 그 중 최대값 찾기
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    unsigned int N, M;
    cin >> N >> M;
    vector<int> result;
    for(int i = 0; i<N; i++){
        vector<int> v;
        for(int j = 0;j<M;j++){
            int input;
            cin >> input;
            v.push_back(input);
        }
        result.push_back(*min_element(v.begin(), v.end()));
    }
    cout << *max_element(result.begin(), result.end());
}