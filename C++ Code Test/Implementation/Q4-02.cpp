#include <iostream>

using namespace std;

int n, m, x, y, d;

int dx[] {-1, 0, 1, 0};
int dy[] {0, 1, 0, -1};

void turn() {
    --d;
    if(d == -1) d = 3;
}

int main()
{
    cin >> n >> m;
    cin >> x >> y >> d;

    int visit[50][50];
    int map[50][50];

    visit[x][y] = 1;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            int k; cin >> k; map[i][j] = k;
        }
    }

    int cnt = 0;
    int turn_time = 0;
    while(true){
        turn();
        int nextX = x + dx[d];
        int nextY = y + dy[d];
        if(visit[nextX][nextY] == 0 && map[nextX][nextY] == 0){
            visit[nextX][nextY] = 1;
            x = nextX; y = nextY;
            ++cnt;
            turn_time = 0;
            continue;
        }
        else turn_time += 1;
        if(turn_time == 4){
            nextX = x - dx[d];
            nextY = y - dy[d];
            if(map[nextX][nextY] == 0){
                x = nextX; y = nextY;
            }
            else break;
            turn_time = 0;
        }
    }
    cout << cnt;
}