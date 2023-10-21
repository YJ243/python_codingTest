/*
 * date: 2023.09.28 오답노트
 * 1. 한 칸에 두 명 이상의 모험자가 있을 수 있다는 조건을 코드에 넣지 않았음
    --> 미로, 참가자 위치, 출구를 모두 각기 다른 배열에 넣음
    --> 하나의 2차원 배열에 0, 음수, 양수, -10으로 구분함
 * 2. 회전할 때 벽과 0만 돌렸고, 출구/참가자는 돌리지 못했음
 * 3. 시계방향으로 90도 회전한다고 했을 때, 한칸씩 오른쪽으로 간다고 코드를 짬(90도가 아님)
 * 4. 만약 회전해서 참가자들이 여러명 오는 경우를 고려하지 못했음
*/


#include <iostream>
//#include <algorithm>
#define NM 15
using namespace std;
int maze[NM][NM];
// maze[i][j]
// 0 -> 빈 칸
// -1 ~ -9 -> 벽을 의미하고, 내구도는 양수 버전입니다.  (예, -5 => 내구도가 5인 벽)
// -10 -> 출구
// 1 이상의 자연수 -> 해당 칸에 존재하는 참가자의 수  (예, 8 => 8명의 참가자가 해당 칸에 존재)
int N, K;       // 미로의 크기, 게임 시간
int moveCnt;    // 모든 참가자들의 이동 거리 합
void input() {  // 입력 받기
    int M;
    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            int x;
            cin >> x;
            maze[i][j] = -x;  // 해당 위치에 벽 생성
        }
    }
    for (int i = 1; i <= M; i++) {
        int x, y;
        cin >> x >> y;
        maze[x][y]++;  // 해당 위치의 참가자 수를 1 증가
    }
    
    int x, y;
    cin >> x >> y;
    maze[x][y] = -10;
}
pair<int, int> findExit() {  // 출구의 좌표를 돌려주는 함수
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (maze[i][j] == -10) {  // 만약 특정 격자에 -10 이 적혀있다면, 출구를 의미한다.
                return { i,j };
            }
        }
    }
}
int dirs[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };  // 상, 하, 좌, 우 순서로 인접한 네 방향
void moveAll() { // 1. 모든 참가자를 한 칸씩 이동시키기
    int newMaze[15][15] = { 0, };  // 이동 결과를 저장할 배열
    auto ex = findExit();
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (maze[i][j] < 0) {  // 해당 격자에 벽이나 출구가 있다면, 그대로 복사하기
                newMaze[i][j] = maze[i][j];
                continue;
            }
            if (maze[i][j] == 0) {
                continue;
            }
            int curDist = abs(i - ex.first) + abs(j - ex.second);
            int minDist = curDist, minI, minJ;
            for (int k = 0; k < 4; k++) {
                int ni = i + dirs[k][0];
                int nj = j + dirs[k][1];
                // (i, j) => (ni, nj)
                if (ni < 1 || nj < 1 || ni > N || nj > N) continue; // 만약 격자를 벗어나면 무효
                if (-9 <= maze[ni][nj] && maze[ni][nj] <= -1) continue; // 만약 벽을 향한 이동이면 무효
                int dist = abs(ni - ex.first) + abs(nj - ex.second); // 출구와 (ni, nj) 사이의 거리
                if (minDist > dist) { // 출구까지의 거리가 "현재보다" 더 가까워졌다면, 갱신
                    minDist = dist;
                    minI = ni;
                    minJ = nj;
                }
            }
            // 만약 아무 곳도 갈 수가 없는 경우
            if (minDist == curDist) {
                newMaze[i][j] += maze[i][j];  // 그대로 위치가 유지
                continue;
            }
            moveCnt += maze[i][j]; // 참가자들이 1만큼 움직인다.
            // 탈출에 성공하는 경우
            if (maze[minI][minJ] == -10) {
                continue;
            }
            newMaze[minI][minJ] += maze[i][j];  // (i, j) -> (minI, minJ)
        }
    }
    // 미로 덮어쓰기
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            maze[i][j] = newMaze[i][j];
        }
    }
}
void subRotate(int x, int y, int d) {  // (x, y)에서 시작해서 한 변의 길이가 d 인 정사각형을 회전
    int a[NM][NM] = { 0, };  // 더미 배열
    int b[NM][NM] = { 0, };  // 더미 배열
    // 회전해야 하는 부분을 a[1][1] 부터 시작하도록 옮기기
    for (int i = x; i <= x + d; i++) {
        for (int j = y; j <= y + d; j++) {
            a[i - x + 1][j - y + 1] = maze[i][j];
        }
    }
    // a 배열을 90도 회전해서 b 배열에 저장하기
    int n = d + 1;  // 현재 옮겨하는 정사각형의 한 변의 격자 개수
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (-9 <= a[i][j] && a[i][j] <= -1) {  // 벽이 회전한다면, 내구도 변화
                a[i][j]++;
            }
            // a[i][j] => a[j][n + 1 - i]
            b[j][n + 1 - i] = a[i][j];
        }
    }
    
    // 다시 미로에 복원하기
    for (int i = x; i <= x + d; i++) {
        for (int j = y; j <= y + d; j++) {
            maze[i][j] = b[i - x + 1][j - y + 1];
        }
    }
}
void rotate() { // 출구와 참가자를 포함한 회전
    // 1. 정사각형의 크기를 먼저 결정하자.
    // 가장 작은 정사각형의 크기 = 출구 & (출구랑 가장 가까운 참가자)
    int minDist = 1000000;
    auto ex = findExit();
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (maze[i][j] <= 0) continue;  // 해당 위치에 참가자가 없다면 무시하기
            int dist = max(abs(i - ex.first), abs(j - ex.second));  // (i, j) 와 출구 사이의 거리
            minDist = min(minDist, dist);
        }
    }
    // 2. 정사각형의 위치를 그 다음으로 결정하자.
    int bestRow = 0, bestCol = 0; // 결정된 정사각형의 좌상단 좌표
    for (int i = 1; i <= N - minDist; i++) {
        for (int j = 1; j <= N - minDist; j++) {
            // (i, j) := 이번에 결정한 정사각형의 좌상단 좌표
            // 행 := i ~ i + minDist
            // 열 := j ~ j + minDist
            bool flagExit = false, flagPerson = false;
            for (int r = i; r <= i + minDist; r++) {
                for (int c = j; c <= j + minDist; c++) {
                    if (maze[r][c] == -10) flagExit = true;
                    if (maze[r][c] > 0) flagPerson = true;
                }
            }
            if (flagExit && flagPerson) {  // 이번에 결정한 정사각형이 사람과 출구를 모두 포함!
                bestRow = i;
                bestCol = j;
                break;
            }
        }
        if (bestRow != 0) break;
    }
    // 3. 회전하기
    subRotate(bestRow, bestCol, minDist);
}
void output() {  // 정답 출력
    cout << moveCnt << "\n";
    auto ex = findExit();
    cout << ex.first << " " << ex.second;
}
bool isFinish() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (maze[i][j] > 0) {  // 한 번이라도 참가자가 발견되면
                return false;
            }
        }
    }
    return true;
}
int main() {
    // 입력 받기
    input();
    while (K--) {
        // 시뮬레이션 진행
        // 1. 모든 참가자를 한 칸씩 이동시키기
        moveAll();
        if (isFinish()) {  // 게임 종료 조건 확인
            break;
        }
        // 2. 출구와 참가자를 포함한 회전
        rotate();
    }
    // 정답 출력
    output();
    return 0;
}









void moveAll(){ // 모든 참가자 이동
    int tmpMaze[NM][NM] = {0,};
    pair<int,int> ex = exitLoc();
        for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (maze[i][j] < 0) {  // 해당 격자에 벽이나 출구가 있다면, 그대로 복사하기
                tmpMaze[i][j] = maze[i][j];
                
            }
            else if (maze[i][j] == 0) {
                continue;
            }
            else{
            int curDist = abs(i - ex.first) + abs(j - ex.second);
            int minDist = curDist, minI, minJ;
            for (int k = 0; k < 4; k++) {
                int ni = i + dirs[k][0];
                int nj = j + dirs[k][1];
                // (i, j) => (ni, nj)
                if (ni < 1 || nj < 1 || ni > N || nj > N) continue; // 만약 격자를 벗어나면 무효
                if (-9 <= maze[ni][nj] && maze[ni][nj] <= -1) continue; // 만약 벽을 향한 이동이면 무효
                int dist = abs(ni - ex.first) + abs(nj - ex.second); // 출구와 (ni, nj) 사이의 거리
                if (minDist > dist) { // 출구까지의 거리가 "현재보다" 더 가까워졌다면, 갱신
                    minDist = dist;
                    minI = ni;
                    minJ = nj;
                }
            }
            // 만약 아무 곳도 갈 수가 없는 경우
            if (minDist == curDist) {
                tmpMaze[i][j] += maze[i][j];  // 그대로 위치가 유지
                continue;
            }
            allMoved += maze[i][j]; // 참가자들이 1만큼 움직인다.
            // 탈출에 성공하는 경우
            if (maze[minI][minJ] == -10) {
                continue;
            }
            tmpMaze[minI][minJ] += maze[i][j];  // (i, j) -> (minI, minJ)
            }
        }
    }
    
    // 원래 격자에다가 옮기기
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            maze[i][j] = tmpMaze[i][j];
            //cout<<maze[i][j] << ' ';
        }
        //cout<<'\n';
    }
    //cout<<'\n';

}
