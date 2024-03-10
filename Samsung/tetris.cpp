/*
 * 2024.03.03
 * 4시간 넘게 잡고 있다가 아래처럼 풀고 틀림
*/

#include <iostream>

using namespace std;

int k;
int total_score;
int total_block;
int red[4][6];
int yellow[6][4];
int nextBlock[4][4];

int ToRed(int t, int x){
    int ny=5;
    if(t <= 2){     // 1x1, 1x2 블록
        // x행의 nY를 찾기
        for(int j=0; j<=5; j++){
            if(red[x][j] == 1){
                ny = j-1;
                break;
            }
        }
        if(t == 1)
            red[x][ny] = 1;     
        else
            red[x][ny] = red[x][ny-1] = 1;
    }
    else{            // 2x1 블록
        for(int j=0; j<=5; j++){
            if(red[x][j] == 1 || red[x+1][j] == 1){
                ny = j-1;
                break;
            }
        }
        red[x][ny] = red[x+1][ny] = 1;
    }
    return ny;
}

int ToYellow(int t, int y){
    int nx = 5;     // 일단 제일 끝에 들어간다고 가정하기
    if(t == 1 || t == 3){           // 1x1, 2x1 블록
        for(int i=0; i<=5; i++){
            if(yellow[i][y] == 1){
                // 1을 만나면
                nx = i-1;
                break;
            }
        }

        if(t == 1){
            yellow[nx][y] = 1;
        }
        else{
            yellow[nx][y] = yellow[nx-1][y] = 1;
        }
    }
    else{           // 1x2 블록
        for(int i=0; i<=5; i++){
            if(yellow[i][y] == 1 || yellow[i][y+1] == 1){
                nx = i-1;
                break;
            }
        }
        yellow[nx][y] = yellow[nx][y+1] = 1;
    }
    return nx;
}

void InitializeNext(){
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            nextBlock[i][j] = 0;
}

void DeleteFullRed(){
    // step 0. 먼저 다음 배열 초기화하기
    InitializeNext();
    bool ExistFull = false;
    // step 1. 꽉찬 열이 있다면 지워주기
    for(int j=2; j<=5; j++){
        bool IsFull = true;
        for(int i=0; i<4; i++){
            if(red[i][j] == 0) // 만약 빈 칸이 하나라도 있다면 그 열은 꽉 차지 않음
                IsFull = false;
        }
        if(IsFull){     // 열이 꽉 찼다면
            // 해당 열 지워주기
            ExistFull = true;
            for(int i=0; i<4; i++)
                red[i][j] = 0;
            total_score++;
        }
    }

    if(!ExistFull)
        return;

    // step 2. 빈 열이 있다면 오른쪽으로 밀어서 없애주기
    int curY = 3;
    for(int j=5; j>=2; j--){
        bool existBlock = false;        // 현재 확인하는 행에 블럭이 존재하는가?
        for(int i=0; i<4; i++){
            if(red[i][j] == 1)       // 블럭이 하나라도 존재한다면 true
                existBlock = true;
        }
        if(existBlock){             // 블럭이 존재하는 줄을 next로 옮기기
            for(int i=0; i<4; i++){
                nextBlock[i][curY] = red[i][j];
            }
            curY--;
        }
    }

    // step 3. next를 원래 블럭으로 옮겨주기
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            red[i][j+2] = nextBlock[i][j];
        }
    }
}

void DeleteFullYellow(){
    // step 0. 먼저 다음 배열 초기화하기
    InitializeNext();
    bool ExistFull = false;
    // step 1. 꽉찬 행이 있다면 지워주기
    for(int i=2; i<=5; i++){
        bool IsFull = true;
        for(int j=0; j<4; j++){
            if(yellow[i][j] == 0) // 만약 빈 칸이 하나라도 있다면 그 행은 꽉 차지 않음
                IsFull = false;
        }
        if(IsFull){     // 행이 꽉 찼다면
            // 해당 행 지워주기
            ExistFull = true;
            for(int j=0; j<4; j++)
                yellow[i][j] = 0;
            total_score++;
        }
    }

    if(!ExistFull)
        return;

    // step 2. 빈 행이 있다면 아래로으로 밀어서 없애주기
    int curX = 3;
    for(int i=5; i>=2; i--){
        bool existBlock = false;        // 현재 확인하는 행에 블럭이 존재하는가?
        for(int j=0; j<4; j++){
            if(yellow[i][j] == 1)       // 블럭이 하나라도 존재한다면 true
                existBlock = true;
        }
        if(existBlock){             // 블럭이 존재하는 줄을 next로 옮기기
            for(int j=0; j<4; j++){
                nextBlock[curX][j] = yellow[i][j];
            }
            curX--;
        }
    }

    // step 3. next를 원래 블럭으로 옮겨주기
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            yellow[i+2][j] = nextBlock[i][j];
        }
    }
}

void ProcessLightRed(int t, int px, int ny){    // t번 블럭이 (px, ny)에 놓였을 때 처리 
    if(t == 1 || t == 3){      // 1x1, 2x1 블럭의 경우 오른쪽으로 1열 밀어야 함
        // 2~4 열을 3~5로 밀기
        for(int j=4; j >= 2; j--){
            for(int i=0; i<4; i++){
                red[i][j+1] = red[i][j];
            }
        }
        // 2열을 모두 0으로
        for(int i=0; i<4; i++)
            red[i][2] = 0;
        // 2열에 블럭 놓기
        if(t == 1){
            red[px][ny+1] = 1;
            red[px][ny] = 0;
        }
        else{
            red[px][ny+1] = red[px+1][ny+1] = 1;
            red[px][ny] = red[px+1][ny] = 0;
        }
    }
    else{      // 1x2 블럭의 경우 오른쪽으로 2열 밀어야 함    
        // 2,3열을 3,4로 밀기
        for(int j=3; j >= 2; j--){
            for(int i=0; i<4; i++){
                red[i][j+2] = red[i][j];
            }
        }
        // 2,3 열을 모두 0으로
        for(int i=0; i<4; i++){
            for(int j=2; j<=3; j++)
                red[i][j] = 0;
        }

        // 2,3열에 블럭 놓기
        red[px][2] = red[px][3] = 1;
        red[px][0] = red[px][1] = 0;
    }
}

void ProcessLightYellow(int t, int nx, int py){ // t번 블럭이 (nx, py)에 놓였을 때 처리

    if(t == 1 || t == 2){      // 1x1, 1x2 블럭의 경우 아래쪽으로 1열 밀어야 함
        // 2~4 행을 3~5로 밀기
        for(int i=4; i >= 2; i--){
            for(int j=0; j<4; j++){
                yellow[i+1][j] = yellow[i][j];
            }
        }
        // 2행을 모두 0으로
        for(int j=0; j<4; j++)
            yellow[2][j] = 0;
        // 2행에 블럭 놓기
        if(t == 1){
            yellow[nx+1][py] = 1;
            yellow[nx][py] = 0;
        }
        else{
            yellow[nx+1][py] = yellow[nx+1][py+1] = 1;
            yellow[nx][py] = yellow[nx][py+1] = 0;
        }
    }
    else{      // 2x1 블럭의 경우 아래쪽으로 2열 밀어야 함    
        // 2,3행을 3,4로 밀기
        for(int i=3; i >= 2; i--){
            for(int j=0; j<4; j++){
                yellow[i+2][j] = yellow[i][j];
            }
        }
        // 2,3 행을 모두 0으로
        for(int j=0; j<4; j++){
            for(int i=2; i<=3; i++)
                yellow[i][j] = 0;
        }

        // 2,3행에 블럭 놓기
        yellow[2][py] = yellow[3][py] = 1;
        yellow[0][py] = yellow[0][1] = 0;
    }
}

void Move(int t, int x, int y){     // (x,y)에 놓인 t번 블록을 이동시키기
    // Step 1. 먼저 주어진 타일 이동시키기
    int ny = ToRed(t, x);
    int nx = ToYellow(t, y);   
    // Step 2. 진한 영역에 채워진 줄이 있다면 처리하기
    DeleteFullRed();

    DeleteFullYellow();
    // Step 3. 연한 영역 처리하기
    if(ny <= 1)
        ProcessLightRed(t, x, ny);
    if(nx <= 1)
        ProcessLightYellow(t, nx, y);

}

void Simulate(){
    cin >> k;

    while(k--){
        int t, x, y;
        cin >> t >> x >> y;
        Move(t, x, y);

    }
}

void Output(){
    // red 블록 합
    for(int i=0; i<4; i++){
        for(int j=2; j<=5; j++){
            total_block += red[i][j];
        }
    }
    for(int i=2; i<=5; i++){
        for(int j=0; j<4; j++){
            total_block += yellow[i][j];
        }
    }
    cout << total_score << '\n';
    cout << total_block << '\n';
}

int main() {
    // 시뮬레이션 진행하기
    Simulate();
    
    // 출력하기
    Output();
    return 0;
}