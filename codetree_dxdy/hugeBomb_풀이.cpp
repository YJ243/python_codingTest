/*
 * 2024.1.25
 * 해설 풀이
 * 시간복잡도: O(M*N^2)
 * 공간복잡도: O(N^2)
*/

#include <iostream>

#define MAX_N 100
#define DIR_NUM 4
using namespace std;

int n, m, r, c;         // n: 격자 크기, m: 시간, (r,c) 초기 폭탄의 위치

int grid[MAX_N][MAX_N];         // 0: 빈칸, 1: 폭탄 칸
int next_grid[MAX_N][MAX_N];    // 임시로 옮길 배열

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

void Expand(int x, int y, int dist){
    int dx[DIR_NUM] = {-1,1,0,0};
    int dy[DIR_NUM] = {0,0,-1,1};
    for(int i=0; i<4; i++){
        int nx = x+dx[i]*dist, ny = y+dy[i]*dist;
        if(InRange(nx,ny))
            next_grid[nx][ny] = 1;
    }
}

void Simulate(int dist){
    // Step 1. next_grid 값을 0으로 초기화
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            next_grid[i][j] = 0;

    // Step 2. 폭탄을 던지는 시뮬레이션을 진행
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            if(grid[i][j])
                Expand(i,j,dist);

    // Step 3. next_grid 값을 grid로 업데이트 해주기
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            if(next_grid[i][j]) // 1이 있을 때만 업데이트 해주면 되기 때문에 처음에 next를 모두 0으로 초기화해도 됨
                grid[i][j] = 1;

}

int main() {
    // 입력
    cin >> n >> m >> r >> c;
    grid[r-1][c-1] = 1;
    
    // 총 m번 시뮬레이션 진행
    int dist= 1;
    while(m--){
        Simulate(dist);
        dist *= 2;
    }

    int ans = 0;
    // 출력:
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            ans += grid[i][j];
    cout << ans;
    return 0;
}