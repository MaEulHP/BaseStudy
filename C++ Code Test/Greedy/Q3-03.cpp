#include <iostream>
#include <string>
using namespace std;

int main()
{
    string str;
    cin >> str;

    int cnt0 = 0, cnt1 = 0;
    for(int i = 0; i < str.length()-1; ++i){
        if(str[i] != str[i+1]){
            if(str[i+1] == '0'){
                ++cnt0;
            } else {
                ++cnt1;
            }
        }
    }
    if(str[0] == '0'){
        cout << cnt1;
    } else {
        cout << cnt0;
    }

}