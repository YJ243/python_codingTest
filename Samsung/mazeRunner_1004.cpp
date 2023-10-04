/*
2023.10.04
- 시간이 줄어들었는가?
    디버깅까지 1시간 30분만에 풀었음 (어제는 2시간풀고 2시간 디버깅함)

- 실수가 줄어들었는가?
    처음보다 줄어들었지만, 
    1) minX, minY 를 minI, minJ로 잘못씀
    2) 배열 옮길 때 tmpMaze를 그냥 maze라고 쓰면서 잘못 옮김
       이것때문에 찾느라 30분 잡아먹음...
*/

#include <iostream>
#include <algorithm>
#define NM 15
int N, M, K; // N: 미로 크기, M: 참가자 수, K: 게임 시간
int maze[NM][NM] = {0,};
// maze[i][j]: 미로
// 0       :빈칸
// -1 ~ -9 :벽, 내구도는 격자 값의 음수값
// -10     :츨구
// 양수     :참가자 수

int moveCnt = 0; // 총 움직인 횟수

using namespace std;

void input(){ // 입력값 받아들이기
    cin >> N >> M >> K;
    for(int i=1; i<=N; i++){ // 미로 채우기
        for(int j=1; j<=N; j++){
            int c;
            cin >> c;
            maze[i][j] = -c;
        }
    }
    for(int i=1; i<=M; i++){
        int x, y;
        cin >> x >> y;
        maze[x][y] += 1; // 참가자 수 증가
    }

    int x, y;
    cin >> x >> y;
    maze[x][y] = -10; // 출구 표시

}

pair<int, int> exitLoc(){ // 출구 위치 반환
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            if(maze[i][j] == -10) return make_pair(i,j);
        }
    }
}

void moveAll(){ // 모든 참가자 한 칸씩 이동
    pair<int, int> ex = exitLoc(); // 출구 위치
    int tmpMaze[NM][NM] = {0,}; // 한 번에 이동하는 미로 저장을 위한 임시 격자
    
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            if(maze[i][j] < 0){ // 벽이거나 출구면 바로 복사
                tmpMaze[i][j] = maze[i][j];
                continue;
            }
            if(maze[i][j] == 0){ // 빈칸이면 복사 안하고 바로 넘어가기
                // 해당 칸으로 다른 참가자가 왔을 수도 있음, 아니라고 해도 이미 해당 칸은 0으로 초기화 되어있음
                continue;
            }
            // 이제부터 참가자가 있는 칸
            int curD, minD, minI, minJ;
            curD = abs(i-ex.first)+abs(j-ex.second); // 현재 위치에서 출구까지의 최단 거리
            minD = curD; // 현재 위치를 최단 거리로 잡아놓기
            
            int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}}; // 상하->좌우 순으로 움직임
            for(int d=0; d<4; d++){ // 상하좌우 보면서 갈 수 있는지 확인
                int nx = i + dirs[d][0];
                int ny = j + dirs[d][1];

                if(nx < 1 or ny <1 or nx > N or ny > N) continue; // 범위 벗어나면 패스
                if(-9 <= maze[nx][ny] && maze[nx][ny] <= -1) continue; // 벽이면 패스

                int nextD = abs(nx-ex.first)+abs(ny-ex.second); // 움직인 곳으로부터 출구까지의 거리
                if(nextD < minD){ // 만약 움직인 곳이 출구까지 거리가 더 짧아진다면
                    minD = nextD;
                    minI = nx;
                    minJ = ny;
                }
            }
            
            // 네 방향 다 보고 나왔는데, 움직일 수 없다면
            if(curD == minD){ // minD가 그대로야
                tmpMaze[i][j] += maze[i][j]; // 현재 위치에 있는 참가자 수를 tmpMaze 같은 위치에 그대로 추가
                continue;
            }

            // 움직일 수 있다면
            moveCnt += maze[i][j]; // 움직인 횟수 증가

            // 움직일 수 있는데, 만약 그곳이 출구라면?
            if(maze[nx][ny] == -10){
                continue;
            }
            
            // 출구가 아니라면? 새로운 곳에 이전 위치에 있는 참가자 수 추가
            tmpMaze[nx][ny] += maze[i][j];
        }
    }
    // 원래 미로로 격자 복사
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            maze[i][j] = tmpMaze[i][j];
        }
    }

}

void subRotate(int x, int y, int l){ // 해당 정사각형 회전
    int subMaze[NM][NM] = {0,}; // 원 격자의 (x,y)부터 시작하는 정사각형을 subMaze의 (1,1)부터 시작하도록 옮기기
    int rotMaze[NM][NM] = {0,}; // 그 subMaze를 90도 회전한 격자

    // (x,y) => (1,1)
    for(int i=x; i<x+l; i++){
        for(int j=y; j<y+l; j++){
            subMaze[1+i-x][1+j-x]=maze[i][j]
        }
    }

    // subMaze 시계방향으로 90도 회전
    for(int i=1; i<=l; i++){
        for(int j=1; j<=l; j++){
            // (a,b)=>(b,l-x+1)
            if(-9 <= subMaze[i][j] && subMaze[i][j] <= -1) subMaze[i][j] -= 1; // 내구도 1 감소
            rotMaze[j][l-i+1]=subMaze[i][j];
        }
    }

    // 회전한 정사각형 다시 원래 격자에 넣기
    for(int i=x; i<x+l; i++){
        for(int j=y; j<j+l; j++){
            maze[i][j] = rotMaze[1+i-x][i_j-x];
        }
    }
}

void rotate(){ // 미로 회전
    // 한 명 이상의 참가자와 출구를 포함한 가장 작은 정사각형 잡기
    pair<int, int> ex = exitLoc(); // 출구 위치
    int minL = 100000; // 가장 작은 정사각형의 한 변의 길이
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            if(maze[i][j] > 0){ // 참가자가 있는 격자를 만나면
                // 참가자부터 출구까지 정사각형의 가로/세로 중 큰 변을 잡기
                int curL = max(abs(i-ex.first),abs(j-ex.second))+1; // 길이니 끝에 +1 더해주기
                if(curL > minL){    // 만약 현재 길이가 최소 길이보다 작다면
                    minL = curL; // 현재 길이로 업데이트
                }
            }
        }
    }

    // 현재 길이를 가지고 전체 격자를 순회하면서 (r,c) 좌표가 r->c 작은 순으로 정사각형 확인
    int r,c;
    bool isExit = false;
    bool isPerson = false;

    for(int i=1; i<=N-minL+1;i++){
        for(int j=1; j<=N-minL+1; j++){
            isExit = false;
            isPerson = false;

            // (i,j)가 좌상단인 정사각형 확인
            for(int x=i; x<i+minL; x++){
                for(int y=j; y<j+minL; y++){
                    if(maze[x][y] == -10) isExit = true; // 출구가 존재
                    if(maze[x][y] > 0) isPerson = true; // 사람 존재
                }
            }
            if(isExit && isPerson){ // 만약 정사각형 찾았으면 반복문 빠져나오기
                r = i;
                c = j;
                break;
            }
        }
        if(isExit && isPerson) break; // 정사각형 찾았으면 바깥 for문도 빠져나오기

        //(r,c)를 좌상단으로 하고, 한 변의 길이가 minL인 정사각형 회전하기
        subRotate(r,c,minL);
    }

}