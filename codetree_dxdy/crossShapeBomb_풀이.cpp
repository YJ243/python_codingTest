/*
 * 2024.1.19
 * 해설 풀이
*/
#include <iostream>
#include <cmath>

#define MAX_N 200

using namespace std;
int n;
int grid[MAX_N][MAX_N];
int next_grid[MAX_N][MAX_N];

bool InBombRange(int x, int y){
    return (x == center_x || y == center_y) && abs(x-center_x) + abs(y-center_y) < bomb_range;
}

void Bomb(int center_x, int center_y){
    int bomb_range = grid[center_x][center_y];

    // Step 1. 폭탄이 터질 위치는 0으로 채워주기
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            if(InBombRange(i,j, center_x, center_y, bomb_range))
                grid[i][j] = 0;

    // Step 2. 폭탄이 터진 이후의 결과를 next_grid에 저장    
    for(int j=0; j<n; j++){
        int next_row = n-1;
        for(int i=n-1; i>=0; i--){
            if(grid[i][j]){
                next_grid[next_row--][j] = grid[i][j];
            }
        }
    }
}
int main() {
    // 입력:
    cin >> n;

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> grid[i][j];
    int r, c;
    cin >> r >> c;
    
    Bomb(r-1, c-1);

    // 출력:
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            cout << result[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}