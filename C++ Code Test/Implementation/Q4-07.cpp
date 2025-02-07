#include <iostream>
#include <string>
using namespace std;

string N;
int sum = 0;

int main()
{
    cin >> N;
    for(int i = 0; i < N.size()/2; i++){
        sum += N[i] - '0';
    }
    for(int i = N.size()/2; i < N.size(); i++){
        sum -= N[i] - '0';
    }

    if(sum == 0) cout << "LUCKY" << "\n";
    else cout << "READY" << "\n";
    

    return 0;
}