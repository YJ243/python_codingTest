#include <iostream>
#include <algorithm>
using namespace std;
#define NM 15
#define INF 10000000

int N, M, K;                // N, M, K := 미로의 크기, 참가자 수, 게임 시간
int maze[NM][NM]={0,};      // -1 ~ -9: 벽 내구도, -10: 출구, 0: 빈칸, 양수: 참가자 수
int move_distance=0;        // 모든 참가자들 이동 거리 합
pair<int, int> maze_exit;   // 출구 좌표

void input(){ // 입력값 받기
    cin >> N >> M >> K; 
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            int val;
            cin >> val; // 격자 입력받기
            maze[i][j]= -val;
        }
    }
    for(int i=1; i<=M; i++){ // 참가자들 입력받기
        int x, y;
        cin >> x >> y;
        maze[x][y] += 1; // 격자에 참가자 수 증가
    }
    int e_x, e_y;
    cin >> e_x >> e_y; // 출구 입력받기 
    maze[e_x][e_y] = -10;
}

pair<int, int> exitLoc(){ // 출구 좌표 반환
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            if(maze[i][j] == -10)
                return make_pair(i, j);
        }
    }
}

void moveAll(){
    // 모든 격자에서 참가자가 이동할 수 있는지 보기
    int tmp_maze[NM][NM]={0,}; // 참가자들 한 번에 이동하기 위해 복사해놓을 임시 격자
    pair<int, int> exit_location = exitLoc();
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            tmp_maze[i][j] = maze[i][j];
        }
    }
    int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}}; // 상하, 좌우 우선순위
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            if(tmp_maze[i][j] > 0){ // 만약 해당 칸에 참가자가 존재한다면
                for(int k=0; k<4; k++){ // 상하, 좌우 살펴보기
                    int nx, ny;
                    nx = i+dirs[k][0];
                    ny = j+dirs[k][1];

                    if(nx < 1 or ny < 1 or nx > N or ny > N) continue; // 범위 벗어나면 패스
                    if(-9 <= tmp_maze[nx][ny] && tmp_maze[nx][ny] <= -1) continue; // 벽이 존재하면 패스
                    if(tmp_maze[nx][ny] == -10){
                        tmp_maze[i][j] = 0;
                        break;
                    }
                    // 현재 위치부터 출구까지 최단 거리 확인
                    int now_distance = 0;
                    int new_distance = 0;

                    now_distance = abs(i-exit_location.first) + abs(j-exit_location.second);
                    new_distance = abs(nx-exit_location.first) + abs(ny-exit_location.second);

                    if(now_distance < new_distance) continue; // 만약 현재 위치보다 새로운 곳에서 출구까지가 더 멀면 패스
                    // 만약 움직일 수 있다면
                    tmp_maze[nx][ny] += tmp_maze[i][j]; // 움직이는 칸으로 참가자수 증가
                    move_distance += tmp_maze[i][j]; // 참가자들 이동 거리 합 증가
                    break; // 만약 발견했으면 그대로 나가기                
                
                }

            }
        }
    }
    for(int i=1; i<=N; i++){ // 미로 원래대로 옮기기
        for(int j=1; j<=N; j++){
            maze[i][j] = tmp_maze[i][j];
        }
    }
}

void subrotate(int x, int y, int d){
    int tmp_grid[NM][NM] = {0,}; // 회전할 정사각형 크기만큼 임시로 배열 만들
    int moved_grid[NM][NM] = {0,};
    for(int i=x; i<x+d; i++){
        for(int j=y; j<y+d; j++){ // tmp_grid[1][1]부터 시작
            tmp_grid[i-x+1][j-y+1] = maze[i][j];
            
        }
    }
    for(int i=1; i<=d; i++){
        for(int j=1; j<=d; j++){
            moved_grid[j][d-i+1]=tmp_grid[i][j];
        }
    }
    for(int i=x; i<x+d; i++){
        for(int j=y; j<y+d; j++){ // 미로 원래대로 복구하기
            maze[i][j] = moved_grid[i-x+1][j-y+1];
            
        }
    }
}
void rotate(){
    pair<int, int> exit_location = exitLoc();
    //cout << exit_location.first << ' ' << exit_location.second << "Dfd"<<'\n';
    int minLength = INF;
    int curLength = 0;
    int minI, minJ;

    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            if(maze[i][j] > 0){ // 만약 참가자가 있다면
                curLength = max(abs(exit_location.first-i), abs(exit_location.second-j))+1;
                if(curLength<minLength){
                    minLength = curLength;
                    minI=exit_location.first-minLength+1;
                    minJ=exit_location.second-minLength+1;
                }

            }
        }
    }
    subrotate(minI, minJ, minLength); // 회전할 정사각형 보내기
}

void output(){
    cout << move_distance << '\n';
    cout << maze_exit.first << ' ' << maze_exit.second << '\n';
}
bool finish(){
    int cnt = 0;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            if(maze[i][j] > 0) cnt++;
        }
    }
    if(cnt==0) return true;
    else return false;
}

int main(){
    // 입력 받기
    input();
    // K초 동안 시뮬레이션 시작
    while(K--){
        // 1. 모든 참가자 이동
        moveAll();
        // 끝나는 조건 확인
        if(finish()) break;
        // 2. 미로 회전
        rotate();
    }
    // 결과 출력
    output();
}