/*
1. N -= 1
2. N/K, N%K == 0일때만

N을 1로 만드는 최소 횟수
N이 K의 배수가 될때까지 1빼기
N을 K로 나누기
반복
*/
#include <iostream>
using namespace std;

int main()
{
    int N, K;
    cin >> N >> K;

    int cnt = 0;
    while(N > 1) {
        if(N % K){
            N -= 1;
        }else{
            N /= K;
        }
        ++cnt;
    }
    cout << cnt;
}