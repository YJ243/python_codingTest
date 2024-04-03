/*
 * 2024.03.29
 * 시공의 돌풍
 * 해설 풀이
 * 1. 먼지 확산 2. 시공의 돌풍 기계로 청소
 * 청소 시에는 시공의 돌풍의 위치를 바탕으로 격자를 두 부분으로 나누고,
 * 각 부분에 대하여 벽과 시공의 돌풍을 경계로 삼아 반시계방향과 시계방향으로 먼지를 한 칸씩 이동
 * 돌풍이 먼지를 흡수하는 과정도 함께 처리, 이러한 과정을 주어진 시간 t동안 반복
 * 시간 복잡도는 확산과 청소의 각 루프 내부에서 선형적으로 각 칸을 방문하는 연산 수행
 * 총 시간복잡도: O(T*N*M)
*/

#include <iostream>
#include <vector>

#define MAX_NUM 50
#define DIR_NUM 4
#define WINDBLAST -1

using namespace std;

int n, m, t;

int dust[MAX_NUM][MAX_NUM];
int next_dust[MAX_NUM][MAX_NUM];

bool InRange(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < m;
}

bool CanSpread(int x, int y) {
    return InRange(x, y) && dust[x][y] != WINDBLAST;
}

// (x, y)에서 인접한 4방향으로 확산이 일어난다.
void Spread(int x, int y){
    int dx[DIR_NUM] = {-1, 1, 0, 0};
    int dy[DIR_NUM] = {0, 0, -1, 1};

    int curr_dust = dust[x][y];

    // 인접한 4방향으로 확산이 일어난다.
    for(int i=0; i<DIR_NUM; i++){
        int nx = x + dx[i], ny = y + dy[i];

        // 격자 안이면서, 시공의 돌풍이 없는 곳으로만 확산이 가능하다.
        if(CanSpread(nx, ny)){
            next_dust[nx][ny] += curr_dust / 5;
            dust[x][y] -= curr_dust / 5;
        }
    }
}

void Diffusion(){
    // next_dust 값을 0으로 초기화한다.
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            next_dust[i][j] = 0;
    
    // 시공의 돌풍을 제외한 위치에서만 확산이 일어난다.
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            if(dust[i][j] != WINDBLAST)
                Spread(i, j);
    
    // next_dust 값을 확산 후 남은 dust에 더해준다.
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            dust[i][j] += next_dust[i][j];
}

void CounterClockwiseRotation(int start_row, int start_col, int end_row, int end_col){
    // Step 1-1. 직사각형 가장 왼쪽 위 모서리 값을 temp에 저장한다.
    int temp = dust[start_row][start_col];

    // Step 1-2. 직사각형 가장 위 행을 왼쪽으로 한 칸씩 shift 한다.
    for(int col = start_col; col < end_col; col++)
        dust[start_row][col] = dust[start_row][col+1];
    
    // step 1-3. 직사각형 가장 오른족 열을 위로 한 칸씩 shift 한다.
    for(int row = start_row; row < end_row; row++)
        dust[row][end_col] = dust[row+1][end_col];
    
    // step 1-4. 직사각형 가장 아래 행을 오른쪽으로 한 칸씩 shift 한다.
    for(int col = end_col; col > start_col; col--)
        dust[end_row][col] = dust[end_row][col-1];
    
    // step 1-5. 직사각형 가장 왼쪽 열을 아래로 한 칸씩 shift 한다.
    for(int row = end_row; row > start_row; row--)
        dust[row][start_col] = dust[row-1][start_col];
    
    // step 1-6. temp를 가장 왼쪽 위 모서리를 기존으로 바로 아래 칸에 넣는다.
    dust[start_row+1][start_col] = temp;
}

void ClockwiseRotation(int start_row, int start_col, int end_row, int end_col){
    // STep 1-1. 직사각형 가장 왼쪽 위 모서리 값을 temp에 저장한다.
    int temp = dust[start_row][start_col];

    // Step 1-2. 직사각형 가장 왼쪽 열을 위로 한 칸씩 shift 한다.
    for(int row = start_row; row < end_row; row++)
        dust[row][start_col] = dust[row+1][start_col];

    // Step 1-3. 직사각형 가장 아래 행을 왼쪽으로 한 칸씩 shift 한다.
    for(int col = start_col; col < end_col; col++)
        dust[end_row][col] = dust[end_row][col+1];
    
    // Step 1-4. 직사각형 가장 오른쪽 열을 아래로 한 칸씩 shift 한다.
    for(int row = end_row; row > start_row; row--)
        dust[row][end_col] = dust[row-1][end_col];
    
    // Step 1-5. 직사각형 가장 위 행을 오른쪽으로 한 칸씩 shift 한다.
    for(int col = end_col; col > start_col; col--)
        dust[start_row][col] = dust[start_row][col-1];
    
    // Step 1-6. temp를 가장 왼쪽 위 모서리를 기준으로 바로 오른쪽 칸에 넣는다.
    dust[start_row][start_col+1] = temp;
}

void Cleaning(){
    vector<int> windblast_rows;
    for(int i=0; i<n; i++)
        if(dust[i][0] == WINDBLAST)
            windblast_rows.push_back(i);

    CounterClockwiseRotation(0, 0, windblast_rows[0], m-1);
    ClockwiseRotation(windblast_rows[1], 0, n-1, m-1);

    // 돌풍 보정
    dust[windblast_rows[0]][0] = dust[windblast_rows[1]][0] = -1;
    dust[windblast_rows[0]][1] = dust[windblast_rows[1]][1] = 0;
}

void Simulate(){
    // 확산이 일어난다.
    Diffusion();

    // 시공의 돌풍이 청소를 진행한다.
    Cleaning();
}

int main(){
    cin >> n >> m >> t;

    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            cin >> dust[i][j];

    // 총 t번 시뮬레이션을 진행한다.
    while(t--)
        Simulate();
    
    int ans = 0;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            if(dust[i][j] != WINDBLAST)
                ans += dust[i][j];
    cout << ans;
    return 0;
}