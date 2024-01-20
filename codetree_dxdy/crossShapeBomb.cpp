/*
 * 2024.1.19
 * 내 풀이
*/
#include <iostream>
#define MAX_N 200

using namespace std;
int n;
int grid[MAX_N][MAX_N];
int result[MAX_N][MAX_N];
int dirs[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

int main() {
    // 입력:
    cin >> n;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> grid[i][j];
    int r, c;
    cin >> r >> c;
    r--; c--;
    
    // Step 0. 터질 크기 정하기
    int bombLength = grid[r][c]-1;
    grid[r][c] = 0;
    
    // Step 1. 인접한 상하좌우 방향으로 폭탄 터뜨리기
    for(int i=1; i<=bombLength; i++){
        for(int d=0; d<4; d++){
            int nx = r+dirs[d][0]*i, ny = c+dirs[d][1]*i;
            if(InRange(nx, ny)){
                grid[nx][ny] = 0;                
            }
        }
    }
    
    // Step 2. 열 단위로 보면서 중력 작용시키기   
    for(int j=0; j<n; j++){
        // j 열에 대해서 확인
        int tmpLastIdx = n-1;
        for(int i=n-1; i>=0; i--){
            if(grid[i][j] != 0){
                result[tmpLastIdx][j] = grid[i][j];
                tmpLastIdx--;
            }
        }
    }
    
    // 출력:
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            cout << result[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}