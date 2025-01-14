#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int N, M;
    cin >> N >> M;
    vector<int> ball;
    for(int i=0, j; i<N; ++i){
        cin >> j;
        ball.push_back(j);
    }
    int Comb = 0;
    for(int i=0; i<N-1; ++i){
        for(int j=i+1; j<N; ++j){
            if(ball.at(i) == ball.at(j)){
                continue;
            }
            ++Comb;
        }
    }
    cout << Comb;
    return 0;
}