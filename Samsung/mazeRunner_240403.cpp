/*
 * 24.04.03
 * 내 풀이
 * 중간에 실수를 많이 함...
 * 하.. 다시 작년 10월이 된 것만 같다..
*/

#include <iostream>
#include <cstdlib>
#define MAX_N 10

using namespace std;

int N, M, K; // N: 미로 크기, M: 참가자 수, K: 게임 시간
int grid[MAX_N][MAX_N]; // 미로 정보
/*
 grid는 미로
 0: 빈칸, -1 ~ -9: 벽의 내구도, -10: 출구, 양수: 참가자 수
*/
int temp_grid[MAX_N][MAX_N];    // 참가자가 움직이고 난 다음 격자
int dirs[4][2] = {{-1,0},{1,0},{0,1},{0,-1}};   // 상하 우선순위 -> 좌우
int total_moved;        // 전체 움직인 거리 합

void Input(){           // 입력을 받는 함수
    cin >> N >> M >> K;                     // N: 미로 크기, M: 참가자 수, K: 게임 시간
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> grid[i][j];
            grid[i][j] = -grid[i][j];       // 벽 내구도 음수로 바꾸기
        }
    }
    for(int i=0; i<M; i++){                 // M명의 참가자 좌표 입력받기
        int r, c;
        cin >> r >> c;
        grid[r-1][c-1]++;
    }
    int r, c;                               // 출구 좌표 입력받기
    cin >> r >> c;
    grid[r-1][c-1] = -10;                   // 출구 표시
}

bool IsFinish(){        // 모든 참가자가 미로를 탈출했는지 확인하는 함수
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(grid[i][j] > 0){     // 만약 참가자가 남아 있다면
                return false;       // 아직 끝나지 않음
            }
        }
    }
    return true;                    // 반복문을 빠져나왔다면 끝남을 의미
}

void Initialize_before_search(){    // 탐색 전 temp_grid 초기화하는 함수
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            temp_grid[i][j] = 0;
        }
    }
}

pair<int, int> FindExit(){          // 출구 좌표를 찾아주는 함수 
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(grid[i][j] == -10){
                return make_pair(i,j);
            }
        }
    }
}

bool InRange(int x, int y){         // 범위 안에 있는지 확인하는 함수
    return 0 <= x && x < N && 0 <= y && y < N;
}

bool CanGo(int x, int y, int dist){ // 다음 칸인 (x,y) 으로 갈 수 있는지 확인하는 함수
    pair<int, int> exit_loc = FindExit();
    int curDist = abs(exit_loc.first - x) + abs(exit_loc.second - y);
    // 범위 안에 있고, 다음 격자가 벽이 아니면서 출구까지의 거리가 더 작아야 갈 수 있음 
    return InRange(x, y) && (grid[x][y] >= 0 || grid[x][y] == -10) && dist > curDist;
}

void MoveAll(){                     // 참가자를 모두 이동시키는 함수
    // 1. 탐색 전 초기화
    Initialize_before_search();
    pair<int, int> exit_loc = FindExit();
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(grid[i][j] > 0){     // 참가자가 있는 칸을 만났다면
                int dist = abs(exit_loc.first - i) + abs(exit_loc.second - j);      // 현재 위치에서 출구까지의 거리 구하기
                int curX = i, curY = j;         // 다음으로 이동할 위치 저장
                for(int d=0; d<4; d++){
                    int nx = i + dirs[d][0], ny = j + dirs[d][1];
                    if(CanGo(nx,ny, dist)){     // 만약 갈 수 있다면
                        curX = nx, curY = ny;   // 다음으로 이동할 위치 업데이트
                        total_moved += grid[i][j];      // 움직인 거리 증가하기
                        break;
                    }
                }
                if(curX == i && curY == j){     // 만약 네 방향을 모두 탐색했는데도 움직일 수 없는 상황이라면
                    temp_grid[i][j] += grid[i][j];  // 움직이지 않기
                }
                else{   // 다음 칸으로 움직일 수 있다면
                    if(grid[curX][curY] == -10)     // 그런데 그 칸이 출구라면
                        continue;                   // 참가자 수 다음 격자에 표시하지 않고 넘어가기
                    temp_grid[curX][curY] += grid[i][j];    // 그 외의 경우는 참가자 수 이동했다고 표시하기
                }
            }
            else if(grid[i][j] < 0) // 만약 벽이나 출구를 만났다면
                temp_grid[i][j] = grid[i][j];   // 바로 옮기기

        }
    }       
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            grid[i][j] = temp_grid[i][j];       // temp를 grid로 옮기기 
        }
    }
}

bool CanMakeSquare(int len, int x, int y){      // (x,y)에서 시작하여 len 길이만큼 정사각형을 만들 수 있는지 확인하는 함수
    bool IsPerson = false, IsExit = false;      // 사람이 존재하는지, 출구가 존재하는지 여부 
    for(int i=x; i<x+len; i++){
        for(int j=y; j<y+len; j++){
            if(grid[i][j] > 0)
                IsPerson = true;
            if(grid[i][j] == -10)
                IsExit = true;
        }
    }
    return IsPerson && IsExit;
}

void RotateSquare(int x, int y, int len){
    // 1. 일단 grid의 정사각형 부분을 tmp로 옮기기
    int tmp[MAX_N][MAX_N];
    for(int i=0; i<len; i++){
        for(int j=0; j<len; j++){
            tmp[i][j] = grid[i+x][j+y];
        }
    }
    // 2. tmp를 90도 회전하기
    int rotate_tmp[MAX_N][MAX_N];
    for(int i=0; i<len; i++){
        for(int j=0; j<len; j++){
            rotate_tmp[j][len-1-i] = tmp[i][j];     // 시계방향으로 90도 회전
            if(-9 <= rotate_tmp[j][len-1-i] && rotate_tmp[j][len-1-i] <= -1)    // 만약 벽이라면
                rotate_tmp[j][len-1-i]++;       // 내구도 감
        }
    }
    // 3. rotate_tmp를 grid로 넣기
    for(int i=0; i<len; i++){
        for(int j=0; j<len; j++){
            grid[i+x][j+y] = rotate_tmp[i][j];
        }
    }
}

bool Simulate(int turn){
    // Step 1. 모든 참가자 한 칸 이동
    MoveAll();
    // Step 2. 가장 작은 정사각형 잡기
    if(IsFinish())
        return false;
    int firstX, firstY, minLen;
    bool FindSquare = false;
    for(int k=1; k<=N; k++){    // 정사각형 한 변의 길이는 1부터 N까지
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                if(i+k-1 >= N || j+k-1 >= N) continue;      // 정사각형을 만들지 못하면 넘어가기 
                if(CanMakeSquare(k, i, j)){                 // 한 명 이상의 참가자와 출구를 포함한 정사각형을 만들 수 있다면
                    firstX = i, firstY = j, minLen = k;     // 좌상단 좌표와 길이 저장하기
                    FindSquare = true;                      // 정사각형 찾았다고 표시하기
                    break;
                }
            }
            if(FindSquare) break;
        }
        if(FindSquare) break;
    }

    // Step 3. 회전하기
    RotateSquare(firstX, firstY, minLen);
    return true;
}

int main() {
    // 입력 받기:
    Input();
    // K초 동안 이동하기
    for(int i=1; i<=K; i++){
        bool CanGo = Simulate(i);
        if(!CanGo)  break;
    }
    cout << total_moved << '\n';
    pair<int, int> exit_loc = FindExit();
    cout << exit_loc.first+1 << ' ' << exit_loc.second+1 << '\n';
    return 0;
}