/*
 * 2024.03.03
 * 1. 블록 놓기
 * 1-1. 블록을 떨어뜨리기 전에 현재 위치에서 다음 위치로 이동할 수 있는지 확인한다.
 * 1-2. 이동할 수 없다면, 현재 위치에 블록을 놓는다.
 * 2. 보드의 진한 영역에서 가득 찬 행이나 열이 있는지 검사하여 점수를 획득하고, 해당 행 지우기
 * 3. 보드의 연한 영역에 대해 블록이 존재하면 그 행을 방향에 따라 내림
 * 시간복잡도는 행이나 열을 내리는 과정에서 최악의 경우 전체 행이나 열을 매번 확인해야 함
 * 입력된 블록의 수를 K, 보드의 크기를 NxM => O(K*N*M)
 */

#include <iostream>
#define BOARD_NUM 2
#define MAX_N 6
#define MAX_M 4
#define TILE_NUM 3

using namespace std;

// 3가지 타일 모양을 지정한다.
int shapes[TILE_NUM+1][2][2] = {
    {},

    {{1,0},     // 1x1 타일
     {0,0}},
    
    {{1,1},     // 1x2 타일
     {0,0}},
    
    {{1,0},     // 2x1 타일
     {1,0}}
};

int n = MAX_N, m = MAX_M, k;

int score;

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < m;
}

bool CanGo(int b_num, int tile_type, int x, int y){
    // 바닥에 부딪히거나, 벽돌이 존재하는 경우에는
    // 진행이 불가하다.
    for(int dx = 0; dx < 2; dx++)
        for(int dy = 0; dy < 2; dy++)
            if(shapes[tile_type][dx][dy]){
                int nx = x + dx, ny = y + dy;
                if(!InRange(nx, ny) ||
                    board[b_num][nx][ny])
                        return false;
            }
    return true;
}

void Put(int b_num, int tile_type, int x, int y){
    for(int dx = 0; dx < 2; dx++)
        for(int dy = 0; dy < 2; dy++)
            if(shapes[tile_type][dx][dy]){
                int nx = x + dx, ny = y + dy;
                board[b_num][nx][ny] = 1;
            }
}

bool AllFilled(int b_num, int row){
    for(int col = 0; col < m; col++)
        if(board[b_num][row][col] == 0)
            return false;
    return true;
}

void DownOneLine(int b_num, int end_row){
    for(int row = end_row; row >= 1; row--)
        for(int col = 0; col < m; col++){
            board[b_num][row][col] = board[b_num][row-1][col];
            board[b_num][row-1][col] = 0;
        }
}

void ProcessDark(int b_num){
    // 아래에서 위 방향으로 줄마다 가득 채워져 있는지 확인하여
    // 그 경우에는 점수에 1을 더해주고 한 줄씩 당겨준다.
    int row = n-1;
    while(row >= 2){
        if(AllFilled(b_num, row)){
            score++;
            DownOneLine(b_num, row);
        }
        else
        {
            row--;
        }
    }
}

void ProcessLight(int b_num){
    // Stpt 1. 첫 번째 행, 두 번째 행 중
    // 블럭이 한 개라도 놓여있는 행의 수를 센다.
    
    int drop_cnt = 0;
    if(BlockExist(b_num, 0))
        drop_cnt++;
    if(BlockExist(b_num, 1))
        drop_cnt++;
    
    // Stpe 2.
    // 해당 수만큼 타일을 한 줄식 내려준다.
    while(drop_cnt--)
        DownOneLine(b_num, n-1);
}

void Drop(int b_num, int tile_type, int col){
    // Step 1. 블럭을 떨어뜨린다.
    for(int row = 0; row < n; row++){
        // 그 다음 행으로 진행할 수 없다면
        // 블럭을 안착시킨다.
        if(!CanGo(b_num, tile_tupe, row+1, col)){
            Put(b_num, tile_tupe, row, col);
            break;
        }
    }
    // Step 2. 진한 부분에 대한 처리를 진행한다.
    ProcessDark(b_num);
    // Step 3. 연한 부분에 대한 처리를 진행한다.
    ProcessLight(b_num);
}

void Simulate(int t, int x, int y){
    // Step 1. 노란색 영역에서 진행한다.
    Drop(0, t, y);

    // Step 2. 빨간색 영역에서 진행한다.
    // 이는 그림에서 빨간색 영역을
    // 시계방향으로 90' 회전하여
    // 노란색 영역에서와 같이 진행하면 된다.
    // 각각의 블럭 type에 대해
    // 떨어지는 위치 선정이 중요하다.
    if(t == 1)
        Drop(1, 1, m-1-x);
    else if(t == 2)
        Drop(1, 3, m-1-x);
    else
        Drop(1, 2, m-1-(x+1));
}

int RemainingNum(){
    int cnt = 0;

    for(int l=0; l<2; l++)
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
                cnt += board[l][i][j];
    return cnt;
}

int main() {
    cin >> k;

    // k번 시뮬레이션을 반복한다.
    while(k--){
        int t, x, y;
        cin >> t >> x >> y;
        Simulate(t, x, y);
    }    
    
    cout << score << '\n' << RemainingNum();
    return 0;
}