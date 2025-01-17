#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;
    cin >> n;
    
    string plan;
    getline(cin, plan);

    int x = 1, y = 1;

    for (auto move: plan){
        switch (move)
        {
            case 'L':
                if(x==1){
                    break;
                }
                --x;
                break;
            case 'R':
                if(x==n){
                    break;
                }
                ++x;
                break;
            case 'U':
                if(y==1){
                    break;
                }
                --y;
                break;
            case 'D':
                if(y==n){
                    break;
                }
                ++y;
                break;
            default:
                break;
        }
    }
    cout << y << " " << x;
}