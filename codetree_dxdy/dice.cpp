/*
 * 2024.1.24
 * 내 풀이
*/
#include <iostream>
#define MAX_N 100
#define INT_SUM 7
using namespace std;

int n, m, r, c;
char move_dir;
int curU = 1, curF = 2, curR = 3;
int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};
int ans;
int grid[MAX_N][MAX_N];

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

void update_dice(){
    int nextU, nextF, nextR;
    if(move_dir == 'U'){
        nextU = curF, nextF = INT_SUM-curU, nextR = curR;
    }
    else if(move_dir == 'R'){
        nextU = INT_SUM-curR, nextF = curF, nextR = curU;
    }
    else if(move_dir == 'D'){
        nextU = INT_SUM-curF, nextF = curU, nextR = curR;
    }
    else{
        nextU = curR, nextF = curF, nextR = INT_SUM-curU;
    }
    curU = nextU, curF = nextF, curR = nextR;

}

int GetDirNum(){
    int ret;
    if(move_dir == 'U'){
        ret = 0;
    }
    else if(move_dir == 'R'){
        ret = 1;
    }
    else if(move_dir == 'D'){
        ret = 2;
    }
    else{
        ret = 3;
    }
    return ret;
}

int main() {
    cin >> n >> m >> r >> c;    // n: 격자 크기, m: 주사위 굴릴 횟수, (r,c): 초기 위치
    r--; c--;
    // Step 1. 현재 주어진 위치에 초기 숫자 적기
    grid[r][c] = INT_SUM-curU;

    for(int i=0; i<m; i++){
        cin >> move_dir;        // 움직이는 방향
        int d = GetDirNum();
        int nx = r+dx[d], ny = c+dy[d];
        //  2-1. 움직일 수 있다면 주사위 모양 특정 위해 up, front, right 업데이트
        if(InRange(nx,ny)){
            r = nx, c = ny;
            update_dice();
            grid[r][c] = INT_SUM-curU;
        }

    }
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            ans += grid[i][j];
    cout << ans;
    return 0;
}