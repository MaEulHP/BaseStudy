#include <iostream>
#include <string>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int cnt = 0;
    for(int i = 0; i <= n; i++){
        for(int j = 0 ; j < 60; j++){
            for(int k = 0; k < 60; k++){
                string tmpString = to_string(i) + to_string(j) + to_string(k);
                if(tmpString.find('3') != string::npos){
                    ++cnt;
                }
            }
        }
    }
    cout << cnt;
}