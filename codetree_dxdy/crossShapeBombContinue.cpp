/*
 * 2024.1.20
 * 내 풀이
*/
#include <iostream>
#define MAX_N 200
#define MAX_M 10

using namespace std;
int n, m;
int grid[MAX_N][MAX_N];
int next_grid[MAX_N][MAX_N];
int dirs[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}
void Bomb(int idx){     // idx번째 열 터뜨리기
    // 1. 터져야 할 크기 탐색
    int bombL = -1, startR=-1;
    for(int i=0; i<n; i++){
        if(grid[i][idx]){
            bombL = grid[i][idx]-1;
            startR = i;
            break;
        }
    }
    if(bombL == -1){
        // 만약 해당 열에 더이상 터질 폭탄이 없다면 
        // 아무런 변화를 일으킬 수 없으므로 바로 리턴
        return;
    }
    // 2. 폭탄 터트리기
    grid[startR][idx] = 0;
    for(int i=1; i<=bombL; i++){
        for(int d=0; d<4; d++){
            int nx = startR + dirs[d][0]*i, ny = idx + dirs[d][1]*i;
            if(InRange(nx,ny)){
                grid[nx][ny] = 0;
            }
        }
    }
    // 3. 중력 작용시키기
    // 3-1. next_grid 0으로 만들기
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            next_grid[i][j] = 0;
        }
    }

    // 3-2. 열을 차례로 보면서 옮기기
    for(int j=0; j<n; j++){
        int tempLastIdx = n-1;
        for(int i=n-1; i>=0; i--){
            if(grid[i][j]){
                next_grid[tempLastIdx--][j] = grid[i][j]; 
            }
        }
    }

    // 3-3. 원래 배열로 옮기기
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            grid[i][j] = next_grid[i][j];
        }
    }
}

int main() {
    // 입력:
    cin >> n >> m;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> grid[i][j];
        }
    }       

    while(m--){
        int c;
        cin >> c;
        Bomb(c-1);

    }
    
    // 출력
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            cout << grid[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}