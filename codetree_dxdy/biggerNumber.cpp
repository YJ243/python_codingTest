/*
 * 2024.1.21
 * 내 풀이
*/
#include <iostream>
#define MAX_N 100
using namespace std;

int n, r, c;
int grid[MAX_N][MAX_N];
int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};   // 상하좌우 우선순위

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

void Simulate(){
    int curNum = grid[r][c];
    while(true){ // 움직일 수 있을 때까지
        bool IsMove = false;
        for(int d=0; d<4; d++){
            int nx = r+dirs[d][0], ny = c+dirs[d][1];
            if(InRange(nx,ny) && curNum < grid[nx][ny]){
                curNum = grid[nx][ny];
                r = nx, c = ny;
                IsMove = true;
                cout << curNum << ' ';
                break;
            }
        }
        if(!IsMove) break;
    }
}

int main(){
    // 입력:
    cin >> n >> r >> c;
    r--; c--;
    for(int i=0; i<n; i++)
        for(int j=0; j<n;j++)
            cin >> grid[i][j];
    cout << grid[r][c] << ' ';
    Simulate();
    return 0;
}