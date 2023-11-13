/*
 * 2023.11.12
 * 해설 풀이
*/

#include <iostream>

#define DIR_NUM 4
#define MAX_N 100

using namespace std;

// 전역 변수 선언:
int n;

int curr_x, curr_y;
int move_dir, move_num;

int grid[MAX_N][MAX_N];

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

// 한 칸 움직임
void Move(){
    // 문제에서 원하는 진행 순서대로
    // 오른쪽, 위, 왼쪽, 아래 방향이 되도록 정의
    int dx[DIR_NUM] = {0,-1,0,1};
    int dy[DIR_NUM] = {1,0,-1,0};

    curr_x += dx[move_dir]; curr_y += dy[move_dir];
}

bool End(){
    return !InRange(curr_x, curr_y);
}

int main(){
    // 입력:
    cin >> n;

    // 시작 위치와 방향,
    // 해당 방향으로 이동할 횟수를 설정
    curr_x = n/2; curr_y = n/2;
    move_dir = 0; move_num = 1;

    int cnt = 1;

    while(!End()){
        // move_num 만큼 이동
        for(int i=0; i<move_num; i++){
            grid[curr_x][curr_y] = cnt++;
            Move;

            // 이동하는 도중 격자를 벗어나면 움직이는 것을 종료
            if(End()) break;
        }

        // 방향을 바꿈
        move_dir = (move_dir + 1) % 4;

        // 만약 현재 방향이 왼쪽/오른쪽이 된 경우
        // 특정 방향으로 움직여야 할 횟수를 1 증가
        if(move_dir == 0 || move_dir == 2)
            move_num++;
    }

    // 출력:
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout <<grid[i][j] << " ";
        }
        cout<<'\n';
    }
    return 0;
}