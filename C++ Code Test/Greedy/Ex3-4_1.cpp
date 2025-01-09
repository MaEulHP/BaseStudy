/*
단순한 반복문 시행 -> 숫자 단위가 커지면 오래걸림
-1 과정을 한번에 처리
*/
#include <iostream>
using namespace std;

int main()
{
    int N, K;
    cin >> N >> K;
    int cnt = 0;

    while(N >= K){
        if(N%K){
            cnt += N%K;
            N -= N%K;
        }
        N /= K;
        ++cnt;
    }
    cnt += (N-1);
    cout << cnt;
}