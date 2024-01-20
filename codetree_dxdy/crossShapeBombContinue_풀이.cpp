/*
 * 2024.1.20
 * 해설 풀이
 * 폭탄이 터지고 떨어지는 과정을 총 M번 반복하면 되므로, 시간복잡도는 O(M*N^2)
*/
#include <iostream>
#define MAX_N 200
#define OUT_OF_GRID -1

using namespace std;
int n, m;
int grid[MAX_N][MAX_N];
int next_grid[MAX_N][MAX_N];
int dirs[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};

bool InBombRange(int x, int y, int center_x, int center_y, int bomb_range){
    return (x == center_x || y == center_y) && 
            abs(x-center_x) + abs(y-center_y) < bomb_range; 
}
void Bomb(int center_x, int center_y){
    // Step 1. enxt_grid 값을 0으로 초기화하기
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            next_grid[i][j] = 0;
        }
    }

    // Step 2. 폭탄이 터질 위치는 0으로 채워주기 
    int bomb_range = grid[center_x][center_y];

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            if(InBombRange(i,j,center_x, center_y, bomb_range))
                grid[i][j] = 0;

    // Step 3. 폭탄이 터진 이후의 결과를 next_grid에 저장
    for(int j=0; j<n; j++){
        int next_row = n-1;
        for(int i=n-1; i >= 0; i--){
            if(grid[i][j])
                next_grid[next_row--][j] = grid[i][j];
        }
    }

    // Step 4. grid로 다시 값을 옮겨주기
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            grid[i][j] = next_grid[i][j];
        }
    }
}

// 해당 col열에 폭탄이 터질 위치를 구하기
// 없다면 OUT_OF_GRID를 반환
int GetBombRow(int col){
    for(int row=0; row<n; row++)
        if(grid[row][col] != 0)
            return row;
    return OUT_OF_GRID;

}
int main() {
    // 입력:
    cin >> n >> m;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> grid[i][j];
        }
    }       

    // m번에 걸쳐 폭탄이 터짐
    while(m--){
        int bomb_col;
        cin >> bomb_col; bomb_col--;

        // 폭탄이 터지게 될 위치를 구하기
        int bomb_row = GetBombRow(bomb_col);

        if(bomb_row == OUT_OF_GRID)
            continue;

        Bomb(bomb_row, bomb_col);

    }
    
    // 출력
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            cout << grid[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}