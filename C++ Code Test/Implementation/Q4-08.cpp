#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string Input;
vector<char> result;
int val = 0;

int main()
{
    cin >> Input;

    for(int i = 0; i < Input.size(); i++){
        if(isalpha(Input[i])){
            result.push_back(Input[i]);
        }
        else {
            val += Input[i] - '0';
        }
    }
    sort(result.begin(), result.end());

    for(int i = 0; i < result.size(); i++){
        cout << result[i];
    }
    if(val != 0) cout << val;
    cout << "\n";

    return 0;
}
