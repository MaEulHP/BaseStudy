#include <iostream>
#include <array>
using namespace std;

int main()
{
    int N;
    cin >> N;

    array<int, 4> change = {500, 100, 50, 10};
    int res = 0;

    for(auto x : change){
        res += N / x;
        N %= x;
    }

    cout << res;
}