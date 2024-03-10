/*
 * 2024.03.01
 * 내 풀이
*/

#include <iostream>
#define MAX_N 20
using namespace std;

int n, m, k;                    // n: 격자 크기, m: 플레이어 수, k: 독점 계약 턴 수
int grid[MAX_N][MAX_N];         // 0: 빈칸, p: p번 플레이어의 위치
int temp[MAX_N][MAX_N];         // 플레이어 한 번에 이동하기 위해 사용할 배
int validLeft[MAX_N][MAX_N];    // 양수: 해당 칸의 독점 계약이 끝나기까지 남은 턴수
int exclusive[MAX_N][MAX_N];    // 해당 칸에서 독점 계약을 맺은 숫자
int curDir[MAX_N*MAX_N+1];      // i번째 사람이 현재 바라보는 방향

int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};    // 위, 아래, 왼, 오
int dirPrior[MAX_N*MAX_N+1][4][4];
int curRound;          // 턴의 수

void Init(){                    // 입력 및 초기화를 진행하는 함수
    cin >> n >> m >> k;         // 격자 크기, 플레이어 수, 독점 계약 턴 수 입력받기
    for(int i=0; i<n; i++)      // 플레이어 위치 입력받기
        for(int j=0; j<n; j++){
            cin >> grid[i][j];
            if(grid[i][j] > 0){ // 만약 플레이어를 입력받았다면
                validLeft[i][j] = k;            // 해당 칸에 독점 계약이 끝나기까지의 턴 수 넣기
                exclusive[i][j] = grid[i][j];   // 해당 칸을 해당 플레이어가 독점하고 있다고 표시하기
            }
        }
    
    for(int i=1; i<=m; i++){    // 각 플레이어의 현재 위치 입력받기
        cin >> curDir[i];
        curDir[i]--;
    }
    
    for(int i=1; i<=m; i++){    // 각 플레이어들의 이동 우선순위 입력받기
        for(int j=0; j<4; j++){
            for(int k=0; k<4; k++){
                cin >> dirPrior[i][j][k];
                dirPrior[i][j][k]--;
            }
        }
    }
    
}

void Initialize_temp(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            temp[i][j] = 0;
    }
}

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

void Move(int x, int y){    // (x,y)에 있는 사용자 이동시켜주기
    int pNum = grid[x][y];
    int pDir = curDir[pNum];
    // 1. 우선순위대로 이동할 수 있는지 확인하기
    // 아무도 독점 맺지 않은 칸 -> 본인이 독점 계약한 칸으로 가기
    int nextX, nextY, nextD;
    bool checkExclusive = false;
    for(int d=0; d<4; d++){
        int nd = dirPrior[pNum][pDir][d];
        int nx = x + dirs[nd][0], ny = y + dirs[nd][1];
        if(InRange(nx, ny) && exclusive[nx][ny] == 0){
            // 다음 이동할 칸이 아무도 독점을 맺지 않은 칸이라면
            nextX = nx, nextY = ny, nextD = nd;
            break;
        }
        else if(InRange(nx, ny) && exclusive[nx][ny] == pNum && !checkExclusive){
            // 해당 사람이 독점을 맺은 칸이라면
            checkExclusive = true;
            nextX = nx, nextY = ny, nextD = nd;
        }
    }
    if(temp[nextX][nextY] == 0 || (temp[nextX][nextY] > 0 && temp[nextX][nextY] > pNum) ){        // 만약 사람이 없거나 현재 사람의 번호가 더 작다면 이동시키기
        temp[nextX][nextY] = pNum;      // 사람 이동하기
        curDir[pNum] = nextD;           // 다음 방향 집어넣기

    }
    
}

void DecreaseExclusive(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(validLeft[i][j]){     // 유효 턴수 1 감소시키기
                validLeft[i][j]--;
                // 만약 감소기키고 난 다음에 0이 되었다면
                if(validLeft[i][j] == 0){
                    exclusive[i][j] = 0;        // 해당 칸 비워주기
                }
            }
        }
    }
}

void MakeExclusive(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j] > 0){
                exclusive[i][j] = grid[i][j];
                validLeft[i][j] = k;
            }
        }
    }
}

void MoveAll(){
    // Step 1. 사용자 한 명씩 이동시키기
    Initialize_temp();                  // 먼저 temp 배열 초기화


    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j] > 0){
                // 만약 사용자가 있다면
                Move(i,j);      // 해당 사용자 이동시키기
            }
        }
    }
    // Step 2. temp배열을 다시 grid로 바꾸기
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            grid[i][j] = temp[i][j];
        }
    }    
    DecreaseExclusive();                // 이동 전 유효 턴 수 1 감소
    MakeExclusive();
    
}

void Simulate(){
    // Step 1. 각 사용자 이동시키기
    MoveAll();
    

}

bool IsFinish(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j] > 1)
                return false;
        }
    }
    return true;
}

int main() {
    // 입력 및 초기화
    Init();

    // 시뮬레이션 진행
    while(curRound < 1000){
        curRound++;
        Simulate();

        if(IsFinish())
            break;
    }
    if(curRound >= 1000)
        cout << -1;
    else
        cout << curRound;
    return 0;
}