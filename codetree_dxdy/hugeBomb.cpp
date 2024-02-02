/*
 * 2024.1.25
 * 내 풀이
*/

#include <iostream>
#include <cstdlib>
#include <cmath>

#define MAX_N 100
#define DIR_NUM 4
using namespace std;
int n, m, r, c;         // n: 격자 크기, m: 시간, (r,c) 초기 폭탄의 위치
int grid[MAX_N][MAX_N]; // 0: 빈칸, 1: 폭탄 칸
int temp[MAX_N][MAX_N];         // 임시로 옮길 배열
int dirs[DIR_NUM][2] = {{1,0},{0,1},{-1,0},{0,-1}};   // 방향

int ans;

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

void InitializeTemp(){
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            temp[i][j] = grid[i][j];
}

void CopytoGrid(){
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            grid[i][j] = temp[i][j];
}

void Simulate(int sec){
    // 먼저 임시로 옮길 배열 초기화
    InitializeTemp();

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            // 만약 폭탄이 놓여있다면
            if(grid[i][j]){
                // 상하좌우 방향으로 거리 2^(t-1)만큼 떨어진 방향으로 폭탄 만들기
                for(int d=0; d<DIR_NUM; d++){
                    int nx = i+dirs[d][0]*pow(2,sec-1), ny = j+dirs[d][1]*pow(2,sec-1);
                    if(InRange(nx,ny)){
                        // 만약 격자 안에 있다면
                        temp[nx][ny] = 1;
                    }
                }
            }
        }
    }

    // temp배열을 grid로 옮기기
    CopytoGrid();
}

int main() {
    // 입력
    cin >> n >> m >> r >> c;
    r--;c--;
    grid[r][c] = 1;
    
    for(int i=1; i<=m; i++){
        // m초까지 폭탄 터뜨리기
        Simulate(i);
    }

    // 출력:
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            ans += grid[i][j];
    cout << ans;
    return 0;
}