#include <iostream>

using namespace std;

int dx[] {-2, -1, 1, 2, 2, 1, -1, -2};
int dy[] {-1, -2, -2, -1, 1, 2, 2, 1};

int main()
{
    string point;
    cin >> point;

    int row = point[1] - '0';
    int col = point[0] - 'a' + 1;

    int result = 0;
    for (int i = 0; i < 8; i++){
        int nextRow = row + dx[i];
        int nextCol = col + dy[i];

        if(nextRow >= 1 && nextRow <= 8 && nextCol >= 1 && nextCol <= 8){
            result += 1;
        }
    }

    cout << result << '\n';
    return 0;
}