/*
 * 2024.1.20
 * 내 풀이
*/
#include <iostream>
#include <algorithm>

#define MAX_N 4
#define ASCII_NUM 128
#define NONE -1

using namespace std;

int n = 4;

int grid[MAX_N][MAX_N];
int next_grid[MAX_N][MAX_N];


// grid를 시계방향으로 90도 회전
void Rotate(){
    // next_grid를 0으로 초기화
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            next_grid[i][j] = 0;
    // 90도 회전하기
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++){
            //next_grid[i][j] = grid[n-1-j][i];
            next_grid[j][n-1-i] = grid[i][j];
        }
    
    // next_grid를 grid에 옮겨주기
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            grid[i][j] = next_grid[i][j];
}

// 아래로 숫자들을 떨어뜨리기
void Drop(){
    // next_grid를 0으로 초기화하기
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            next_grid[i][j] = 0;
    
    // 아래 방향으로 떨어뜨리기
    for(int j=0; j<n; j++){
        // 같은 숫자끼리 단 한번만 합치기 위해 떨어뜨리기 전 숫자 하나를 Keep해주기
        int keep_num = NONE, next_row = n-1;
        for(int i=n-1; i >= 0; i--){
            if(!grid[i][j]) continue;   // 0이면 패스하기

            // 아직 떨어진 숫자가 없다면 갱신해주기
            if(keep_num == NONE)
                keep_num = grid[i][j];
            
            // 가장 최근에 관찰한 숫자가 현재 숫자와 일치한다면
            // 하나로 합쳐주고, keep 값을 비워주기
            else if(keep_num == grid[i][j]){
                next_grid[next_row--][j] = keep_num*2;
                keep_num = NONE;
            }
            // 가장 최근에 관찰한 숫자와 현재 숫자가 다르다면
            // 최근에 관찰한 숫자를 실제 떨어뜨려주고, keep 값을 갱신해주기
            else{
                next_grid[next_row--][j] = keep_num;
                keep_num = grid[i][j];
            }
        }

        // 전부 다 진행했는데도 keep 값이 남아있다면 실제로 한 번 떨어뜨려주기
        if(keep_num != NONE)
            next_grid[next_row--][j] = keep_num;

    }
    // next_grid를 grid에 옮겨주기
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            grid[i][j] = next_grid[i][j];

}

// move_dir 방향으로 기울이는 것을 진행
// 회전을 규칙적으로 하기 위해서 아래, 오른쪽, 위, 왼쪽 순으로 dx, dy 순서를 가져가기
void Tilt(int move_dir){
    // Step 1.
    // move_dir 횟수만큼 시계방향으로 90도 회전하는 것을 반복
    // 항상 아래로만 숫자들을 떨어뜨리면 되게끔 하기
    for(int i=0; i<move_dir; i++)
        Rotate();
    
    // Step 2.
    // 아래 방향으로 떨어뜨리기
    Drop();

    // Step 3.
    // 4-move_dir 횟수만큼 시계방향으로 90도 회전하는 것을 반복
    // 처음 상태로 돌아오게 하기 (총 360도 회전)
    for(int i=0; i<4-move_dir; i++)
        Rotate();
}

int main(){
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            cin >> grid[i][j];
    
    char dir_char;
    cin >> dir_char;

    // 아래, 오른쪽, 위, 왼쪽 순으로 mapper를 저장
    int dir_mapper[ASCII_NUM];
    dir_mapper['D'] = 0;
    dir_mapper['R'] = 1;
    dir_mapper['U'] = 2;
    dir_mapper['L'] = 3;

    // 기울이기
    Tilt(dir_mapper[dir_char]);

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            cout << grid[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}