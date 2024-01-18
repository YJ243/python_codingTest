/*
 * 2024.1.18
 * 내 풀이
*/

#include <iostream>
#define MAX_N 100
using namespace std;


int n;
int grid[MAX_N][MAX_N];
void DoWind(int r, int c, int m1, int m2, int m3, int m4, int d){
    int curR, curC;
    int dirs[4][2];
    if(d==1){
        // dirs[0]: 좌하, dirs[1]: 좌상, dirs[2]: 우상, dirs[3]: 우하
        dirs[0][0] = 1; dirs[0][1] = -1;
        dirs[1][0] = -1; dirs[1][1] = -1;
        dirs[2][0] = -1; dirs[2][1] = 1;
        dirs[3][0] = 1; dirs[3][1] = 1;

        curR = r+dirs[2][0]*m1, curC = c+dirs[2][1]*m1;
    }
    else{
        // dirs[0]: 우상, dirs[1]: 좌상, dirs[2]: 좌하, dirs[3]: 우하
        dirs[0][0] = -1; dirs[0][1] = 1;
        dirs[1][0] = -1; dirs[1][1] = -1;
        dirs[2][0] = 1; dirs[2][1] = -1;
        dirs[3][0] = 1; dirs[3][1] = 1;
        curR = r, curC = c;
    }
    // 0번째 변 회전
    int nx = curR+dirs[0][0]*m1, ny = curC+dirs[0][1]*m1;
    int px,py;
    int temp = grid[nx][ny];

    for(int i=m1; i >= 1; i--){
        nx = curR+dirs[0][0]*i, ny = curC+dirs[0][1]*i; 
        px = curR+dirs[0][0]*(i-1), py = curC+dirs[0][1]*(i-1);
        grid[nx][ny] = grid[px][py];
    }

    // 1번째 변 회전
    curR = curR+dirs[0][0]*m1, curC = curC+dirs[0][1]*m1;
    nx = curR+dirs[1][0]*m2, ny = curC+dirs[1][1]*m2;
    int temp2 = grid[nx][ny];

    for(int i=m2; i>=2; i--){
        nx = curR+dirs[1][0]*i, ny = curC+dirs[1][1]*i;
        px = curR+dirs[1][0]*(i-1), py = curC+dirs[1][1]*(i-1);
        grid[nx][ny] = grid[px][py];
    }
    grid[curR+dirs[1][0]][curC+dirs[1][1]] = temp;

    // 2번째 변 회전
    curR = curR+dirs[1][0]*m2, curC = curC+dirs[1][1]*m2;
    nx = curR+dirs[2][0]*m3, ny = curC+dirs[2][1]*m3;
    temp = grid[nx][ny];

    for(int i=m3; i>=2; i--){
        nx = curR+dirs[2][0]*i, ny = curC+dirs[2][1]*i;
        px = curR+dirs[2][0]*(i-1), py = curC+dirs[2][1]*(i-1);
        grid[nx][ny] = grid[px][py];
    }
    grid[curR+dirs[2][0]][curC+dirs[2][1]] = temp2;

    // 3번째 변 회전
    curR = curR+dirs[2][0]*m3, curC = curC+dirs[2][1]*m3;
    
    for(int i=m4; i >= 1; i--){
        nx = curR+dirs[3][0]*i, ny = curC+dirs[3][1]*i;
        px = curR+dirs[3][0]*(i-1), py = curC+dirs[3][1]*(i-1);
        grid[nx][ny] = grid[px][py];
    }
    grid[curR+dirs[3][0]][curC+dirs[3][1]] = temp;
}

int main() {
    // 입력: 
    cin >> n;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> grid[i][j];    
    

    // (r,c)에서 시작해서 각 방향으로 m1, m2, m3, m4만큼 순서대로 이동
    // dir->1: 시계방향으로 회전, dir->0: 반시계방향으로 회전
    int r, c, m1, m2, m3, m4, dir;  
    cin >> r >> c >> m1 >> m2 >> m3 >> m4 >> dir;
    r--; c--;

    DoWind(r, c, m1, m2, m3, m4, dir);

    // 출력:
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << grid[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}