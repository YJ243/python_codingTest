#include <iostream>
#include <algorithm>
#define NM 15

using namespace std;
/* maze[i][j]
 * 0            : 빈 칸
 * -1 ~ -9      : 벽을 의미하고, 내구도는 양수 버전
 * -10          : 출구
 * 1 이상 자연수 : 해당 칸에 존재하는 참가자 수
*/
int maze[NM][NM];
int N, K;       // 미로의 크기, 게임 시간
int moveCnt;    // 모든 참가자들의 이동 거리 합

void input(){ // 입력 받기
    int M;
    cin >> N >> M >> K; // 미로 크기, 참가자 수, 게임 시간
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            int x;
            cin >> x;
            maze[i][j] = -x; // 해당 위치에벽 생성
        }
    }
    for(int i=1; i<=M; i++){
        int x,y;
        cin >> x >> y;
        // 모든 참가자는 초기에 빈 칸에만 존재
        maze[x][y]++; // 해당 위치의 참가자 수를 1 증가
    }

    // 출구 위치
    int x, y;
    cin >> x >> y;
    maze[x][y] = -10;

}

pair<int, int> findExit(){ // 출구의 위치를 돌려주는 함수
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            if(maze[i][j] == -10) // 만약 특정 격자에 -10이 적혀있다면, 출구
                return {i,j};
        }
    }
}

int dirs[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}}; // 상, 하, 좌, 우 순서로 인접한 네 방향 
void moveAll(){ // 1. 모든 참가자들 한 칸씩 이동시키기
    int newMaze[NM][NM] = {0, }; // 이동 결과를 저장할 배열
    auto ex = findExit();

    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            if (maze[i][j] < 0) { // 해당 격자에 벽이나 출구가 있다면, 그대로 복사
                newMaze[i][j] = maze[i][j];
                continue;
            }
            if (maze[i][j] == 0) continue; // 빈칸이면 패스
            // 만약 사람이 있다면 이제 이동할 수 있는지 확인해야 함
            int curDist = abs(i-ex.first) + abs(j-ex.second); // 현재 머물러 있는 칸부터 출구까지 최단 거리
            int minDist = curDist
            int minI, minJ;
            for(int k=0; k<4; k++){
                int ni = i + dirs[k][0];
                int nj = j + dirs[k][1];
                // (i,j) => (ni, nj)
                if (ni < 1 || nj < 1 || ni > N || nj > N) continue; // 만약 격자를 벗어나면 무효
                if (-9 <= maze[ni][nj] && maze[ni][nj] <= -1) continue; // 만약 벽을 향한 이동이면 무효
                int dist = abs(ni-ex.fisrt) + abs(nj-ex.second); // 출구 ~ (ni,nj)거리

                if (minDist > dist){ // 출구까지의 거리가 "현재보다" 더 가까워 졌다면 갱신
                    // 이 조건으로 인해서 만약에 '상', '좌'가 모두 현재보다 가까워도
                    // '상'에서 이미 minDist에 넣어놨으니, "상하" 우선순위가 지켜짐
                    minDist = dist
                    minI = ni;
                    minJ = nj;
                }
                // 만약 아무 곳으로 갈 수 없는 경우
                if (minDist == curDist){
                    newMaze[i][j] += maze[i][j]; // 그대로 위치 유지
                    continue;
                }
                // 갈 수 있는 경우(+1이 아니라, 참가자들수 만큼!!)
                moveCnt += maze[i][j]; // 참가자들이 1만큼 움직임
                // 탈출에 성공하는 경우 
                if(maze[minI][minJ] == -10){
                    continue; // 참가자들 출구로 보내버리기 (참가자 수 기록 안해서 없애기)
                }
                // 간 곳이 출구가 아니면 누적으로 합!!! 바로 대입하면 원래 있던 참가자 수가 덮어씌워질 수 있음
                newMaze[minI][minJ] += maze[i][j]; // (i,j) => (minI, minJ)
            }
        }
        // 미로 덮어쓰기
        for(int i=1; i<=N; i++){
            for(int j=1; j<=N; j++){
                maze[i][j] = newMaze[i][j];
            }
        }
    

}

void subRotate(int x, int y, int d){ // (x, y)에서 시작해서 한 변의 길이가 d인 정사각형을 회전
    int a[NM][NM] = {0, }; // dummy 배열
    int b[NM][NM] = {0, }; // dummy 배열

    // 회전해야 하는 부분을 a[1][1]부터 시작하도록 옮기기
    for(int i=x; i<=x+d){
        for(int j=y; j<=y+d; j++){
            a[i-x+1][j-y+1] = maze[i][j];
        }
    }

    // a 배열을 90도 회전해서 b배열에 저장하기
    int n = d+1; // 현재 옮겨야하는 정사각형의 한 변의 격자 개수
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(-9 <= a[i][j] && a[i][j] <= -1){
                // 벽이 회전한다면, 내구도 변화
                a[i][j]++;
            }
            // a[i][j] => a[j][n+1-i]
            b[j][n+1-i] = a[i][j];
        }
    }
    // 다시 미로에 복원하기
    for(int i=x; i<=x+d; i++){
        for(int j=y; j<=y+d; j++){
            maze[i][j] = b[i-x+1][j-y+1];
        }
    })

}

void rotate(){ // 출구와 참가자를 포함한 회전
    // 1. 정사각형의 크기를 먼저 결정
    // 가장 작은 정사각형의 크기 = 출구 & (출구랑 가장 가까운 참가자)
    int minDist = 1000000;
    auto ex = findExit();

    // 배열을 처음부터 돌면서 참가자를 발견하면 거리 계산    
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            if(maze[i][j] > 0){
                int dist;
                dist = max(abs(i-ex.first),abs(j-ex.second));
                minDist = min(minDist, dist);
            }
        }
    }
    // 2. 그 이후 정사각형 위치 결정
    int bestRow = 0, bestCol = 0; // 결정된 정사각형의 좌상단 좌표
    for(int i=1; i<=N-minDist; i++){
        for(int j=1; j<=N-minDist; j++){
            // (i,j) := 이번에 결정한 정사각형의 좌상단 좌표
            // 행 := i ~ i + minDist
            // 열 := j ~ j + minDist
            bool flagExit = false, flagPerson = false;
            for(int r=i; r <= i + minDist; r++){
                for(int c=j; c <= j+minDist; c++){
                    if (maze[r][c] == -10) flagExit = true;
                    if (maze[r][c] > 0) flagPerson = true;
                }
            }
            if (flagExit && flagPerson){ // 이번에 결정한 정사각형이 사람과 출구룰 모두 포함한다면
                bestRow = i;
                bestCol = j;
                break; // r작은것-> c작은 순으로 보고 있으니
            }
        }
        if (bestRow != 0) break;
    }
    // 3. 회전하기
    subRotate(bestRow, bestCol, minDist);
}



void output(){ // 정답 출력
    cout << moveCnt << '\n';
    auto ex = findExit();
    cout << ex.first << ' ' << ex.second << '\n';
}
int main(){
    // 입력 받기
    input();
    while (K--){
        // 시뮬레이션 진행
        // 1. 모든 참가자들 한 칸씩 이동시키기
        moveAll();
        if (isFinish()){ // 게임 종료 조건 확인
            // 현재 시간에 모든 참가자 이동후에 확인
            break;
        }

        // 2. 출구와 참가자를 포함한 회전
        rotate();
    }
    // 정답 출력
    output();
    return 0;
}