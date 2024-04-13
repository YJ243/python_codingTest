/*
 * 24.04.14
 * 내풀이
 * 1시간 안에 풀어냈다!
*/
#include <iostream>
#include <cstdlib>
#define MAX_N 10

using namespace std;

int N, M, K;    // N: 격자 크기, M: 참가자 수, K: 게임 시간
int grid[MAX_N][MAX_N];
// 0: 빈칸
// -1 ~ -9: 벽의 내구도
// -10: 출구
// 양수: 참가자 수
int temp[MAX_N][MAX_N]; // 격자를 저장할 중간 배열
int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};    // 상하 우선순위, 그 이후 좌우
int total_moved;    // 모든 참가자들의 이동 거리 합

void Input(){   // 입력을 받는 함수
    cin >> N >> M >> K; // N: 격자 크기, M: 참가자 수, K: 게임 시간
    for(int i=0; i<N; i++){     // 격자 입력받기
        for(int j=0; j<N; j++){
            cin >> grid[i][j];
            grid[i][j] = -grid[i][j];
        }
    }
    for(int i=0; i<M; i++){ // 참가자 입력받기
        int x, y;
        cin >> x >> y;
        grid[x-1][y-1]++;
    }
    int x, y;       // 출구 입력받기
    cin >> x >> y;
    grid[x-1][y-1] = -10;
}

bool IsFinish(){    // 프로그램이 종료되었는지 확인하는 함수
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            // 참가자가 한 명이라도 있으면 아직 끝나지 않음
            if(grid[i][j] > 0)
                return false;
        }
    }
    return true;
}

void Initialize_temp(){     // temp 배열을 초기화하는 함수
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            temp[i][j] = 0;
        }
    }
}

pair<int, int> FindExitLoc(){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(grid[i][j] == -10)
                return make_pair(i, j);
        }
    }
}

bool InRange(int x, int y){     // (x, y)가 범위 안에 있는지 확인하는 함수
    return 0 <= x && x < N && 0 <= y && y < N; 
}

bool CanGo(int x, int y){
    return InRange(x, y) && (-9 > grid[x][y] || grid[x][y] >= 0);
}

void move(int x, int y){
    pair<int, int> exit_loc = FindExitLoc();        // 출구 위치
    int eX = exit_loc.first, eY = exit_loc.second;
    int minL = abs(eX-x) + abs(eY-y), tX=-1, tY=-1; // 현재 위치에서 출구까지의 거리르 minL로

    for(int d=0; d<4; d++){
        int nx = x + dirs[d][0], ny = y + dirs[d][1];
        int curL = abs(eX-nx) + abs(eY-ny);
        // 범위 안에 있고, 벽이 없고, 거리가 더 가깝다면
        if(CanGo(nx, ny) && minL > curL){
            minL = curL, tX = nx, tY = ny;
        }
    }

    if(make_pair(-1, -1) == make_pair(tX, tY)){  // 이동할 수 없다면 기존 위치 리턴하기
        temp[x][y] += grid[x][y];   // 원래 있던 자리에 그대로 두기
        return;
    }
    // 이동할 수 있다면
    total_moved += grid[x][y];      // 이동한 거리 증가시키기
    if(make_pair(tX, tY) != exit_loc){  // 이동할 수 있는데 그 곳이 출구가 아니라면
        temp[tX][tY] += grid[x][y];     // 새로운 곳으로 참가자 이동시키기
    }
    return;
}

void MovePeople(){      // 격자 내에 있는 사람들 이동시키기 
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            // 1) 벽이나 출구인 경우
            if(grid[i][j] == 0) continue;   // 빈 칸이면 넘어가기
            if(grid[i][j] < 0)              // 만약 벽이나 출구라면 그대로 옮기기
                temp[i][j] = grid[i][j];
            else if(grid[i][j] > 0){    // 만약 참가자가 있다면
                move(i, j); // (i, j)에 있는 참가자 움직이기
            }
        }
    }
}

bool CanMakeSquare(int x, int y, int len){  // 정사각형을 만들 수 있는지 확인하는 함수
    bool IsPerson = false, IsExit = false;
    for(int i=x; i < x+len; i++){
        for(int j=y; j < y+len; j++){
            if(grid[i][j] == -10)
                IsExit = true;
            if(grid[i][j] > 0)
                IsPerson = true;
        }
    }
    return IsPerson && IsExit;
}

void Rotate(int x, int y, int len){     // (x, y)에서 len크기의 정사각형을 잡아서 회전하는 함수
    // 1. 먼저 정사각형 옮기기
    int tmp1[len][len];
    for(int i=x; i<x+len; i++)
        for(int j=y; j<y+len; j++){
            tmp1[i-x][j-y] = grid[i][j];
        }

    // 2. 해당 정사각형을 시계방향으로 90도 회전하기
    int tmp2[len][len];
    for(int i=0; i<len; i++){
        for(int j=0; j<len; j++){
            if(-9 <= tmp1[i][j] && tmp1[i][j] <= -1)
                tmp1[i][j]++;   // 만약 벽이라면 내구도 1 감소
            tmp2[j][len-1-i] = tmp1[i][j];
        }
    }
    // 3. 다시 옮겨놓기
    for(int i=x; i<x+len; i++)
        for(int j=y; j<y+len; j++)
            grid[i][j] = tmp2[i-x][j-y];
}


void Simulate(){    // 시뮬레이션을 진행하는 함수
    Initialize_temp();

    // Step 1. 모든 참가자는 한 칸씩 움직인다.
    MovePeople();
    // 다시 grid로 옮겨주기
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            grid[i][j] = temp[i][j];
        }
    }

    // Step 2. 한 명이상의 참가자와 출구를 포함하는 정사각형 잡기
    for(int l=1; l<=N; l++){    // 한 변의 길이가 l인 정사각형, 가장 작은 정사각형 잡기
        for(int i=0; i<=N-l; i++){ // 좌상단 r, c좌표가 작은 것이 우선
            for(int j=0; j<=N-l; j++){
                if(CanMakeSquare(i, j, l)){
                    Rotate(i, j, l);
                    return; // 찾아서 회전했으면 바로 리턴하기
                }
            }
        }
    }
}

int main() {
    // 입력 받기:
    Input();
    while(K--){ // K초동안 시뮬레이션 진행하기
        if(IsFinish())  // 프로그램이 종료되었다면 반복문 나가기
            break;
        Simulate();
    }

    // 출력하기:
    pair<int, int> exit_loc = FindExitLoc();
    cout << total_moved << '\n';
    cout << exit_loc.first +1 << ' ' << exit_loc.second +1 << '\n';
    return 0;
}
