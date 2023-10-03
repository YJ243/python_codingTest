#include <iostream>
#include <algorithm>
using namespace std;
#define NM 15

int N, M, K; // N: 미로 크기, M: 참가자 수, K: 게임 시간
int maze[NM][NM]={0,};
// 0 : 빈칸, 이동 가능
// -1 ~ -9: 벽, 내구도는 격자의 -값
// -10: 출구
// 양수 : 참가자 수

int allMoved = 0;

void input(){ // 입력값 받기
    cin >> N >> M >> K;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            int a;
            cin >> a;
            maze[i][j] = -a;
        }
    }
    for(int i=1; i<=M; i++){
        int x, y;
        cin >> x >> y;
        maze[x][y] += 1;
    }
    int x,y;
    cin >> x >> y;
    maze[x][y] = -10;
}

bool isFinish(){ // 프로그램 종료 조건 확인
    int cnt = 0;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            if(maze[i][j] > 0) cnt++;
        }
    }
    if(cnt > 0) return false;
    return true;
}

pair<int, int> exitLoc(){ // 출구 좌표 반환
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            if(maze[i][j] == -10) return make_pair(i,j);
        }
    }
}


void moveAll(){ // 모든 참가자 이동
    int tmpMaze[NM][NM] = {0,};
    pair<int,int> exit_location = exitLoc();
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){ // 바뀔 수 있는 격자는 빈칸인 0과 참가자 수인 양수
            if(maze[i][j] < 0) tmpMaze[i][j] = maze[i][j]; // 벽은 그대로 옮기기
            else if(maze[i][j] == 0) continue;
            else{ // 참가자가 있는 격자라면
                int curDistance, minDistance, minI, minJ;
                curDistance = abs(i-exit_location.first) + abs(j-exit_location.second);
                minDistance = curDistance;
                int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}}; // 상하좌우 우선순위
                for(int d=0; d<4; d++){ // 현재 있는 칸의 상하좌우 살피면서
                    int dx, dy;
                    dx = i+dirs[d][0];
                    dy = j+dirs[d][1];
                    // 범위 벗어나면 패스
                    if(dx < 1 or dy < 1 or dx > N or dy > N) continue;
                    // 벽이 있으면 패스
                    if(maze[dx][dy] >= -9 && maze[dx][dy] <= -1) continue;

                    // 현재 머물러 있던 칸보다 출구까지의 최단 거리가 가까운지 확인
                    int nextDistance = abs(dx-exit_location.first) + abs(dy-exit_location.second);
                    if(minDistance > nextDistance){ // 움직일 곳이 가깝다면
                        minDistance = nextDistance; // 현재 격자에서 움직였을 때 최소 거리 업데이트
                        minI=dx;
                        minJ=dy;
                    }
                }

                if(minDistance == curDistance){ // 상하좌우 다 살피고 나왔는데, 갈 곳이 없다면
                    tmpMaze[i][j] += maze[i][j]; // 현재 위치의 참가자수 그대로 복사
                    continue;
                }
                
                allMoved += maze[i][j]; // 움직인 거리 업데이트
                // 만약 움직일 수 있는 곳이 출구라면
                if(maze[minI][minJ] == -10){
                    continue;
                }
                tmpMaze[minI][minJ] += maze[i][j]; // 새로운 격자에다가 현재 위치의 참가자수 더하기
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

void subRotate(int r, int c, int l){ // 해당 정사각형 회전하기
    int tmpMaze[NM][NM] = {0,}; // 원래 격자(r,c)에서 시작하는 정사각형 복사
    int subMaze[NM][NM] = {0,}; // 회전한 정사각형

    // 1. (r,c)에서 시작하는 정사각형을 tmpMaze의 (1,1)으로 옮기기
    for(int i=r; i<r+l; i++){
        for(int j=c; j<c+l; j++){
            //cout<<1+i-r << ' ' << 1+j-c << "ij to "<<'\n';
            tmpMaze[1+i-r][1+j-c] = maze[i][j]; 
        }
    }

/*
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cout<<maze[i][j] << ' ';
        }
        cout<<'\n';
    }
    */

    // 2. tmpMaze를 (1,1)부터 시계방향으로 90도 회전한 것을 subMaze에 담기
    for(int i=1; i<=l;i++){
        for(int j=1; j<=l; j++){
            if(tmpMaze[i][j] <= -1 && tmpMaze[i][j] >= -9)
                tmpMaze[i][j] += 1;
            subMaze[j][l-i+1] = tmpMaze[i][j];
        }
    }
    

    // 3. 회전한 subMaze를 원래 maze에 넣기 
    for(int i=r; i<r+l; i++){
        for(int j=c; j<c+l; j++){
            //cout<< 1+i-r << ' ' << 1+j-c << '\n';
            maze[i][j]=subMaze[1+i-r][1+j-c]; 
        }
    }


}


void rotate(){ // 미로 회전
    pair<int,int> exit_location = exitLoc();
    
    int minLength = NM;

    // 1. 가장 작은 정사각형 크기 구하기
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            if(maze[i][j] > 0){ // 만약 참가자가 존재한다면
                int curLength = max(abs(i-exit_location.first), abs(j-exit_location.second))+1;
                // 만약 현재 정사각형 한 변 길이보다 작은 정사각형 찾으면
                if(minLength > curLength) {
                    minLength = curLength;
                }
            }
        }
    }

    // 2. r->c 우선순위대로 가장 작은 정사각형의 좌상단 좌표 찾기

    int locX, locY;
    locX = 0;
    locY = 0;
    bool isExit = false;
    bool isPerson = false;
    bool isFind = false;
    for(int i=1; i<=N-minLength+1; i++){
        for(int j=1; j<=N-minLength+1; j++){ // 전체 격자 내에서 만들 수 있는 정사각형 범위 내에서 확인
            isExit = false;
            isPerson = false;
            // (i,j) 좌표에서 시작하는 정사각형 확인
            for(int v=i; v<i+minLength; v++){
                for(int w=j; w<j+minLength; w++){
                    if(maze[v][w] == -10) isExit = true;
                    if(maze[v][w] > 0) isPerson = true;
                }
            }
            // 만약 현재 정사각형에서 한 명 이상의 참가자와 출구를 포함한다면
            if(isExit && isPerson){
                locX = i;
                locY = j;
                isFind = true;
                break;
            }
        }
        if(isFind) break;
    }
        //cout<< locX << ' ' << locY << ' ' << minLength << '\n';
    

    
    // 3. 해당 정사각형 회전하기
    subRotate(locX, locY, minLength);
}



void output(){
    cout << allMoved << '\n';
    pair<int, int> exit_coor;
    exit_coor = exitLoc();
    cout << exit_coor.first << ' ' << exit_coor.second << '\n';
}

int main(){
    // 1. 입력 받기
    input();

    // 2. 시뮬레이션 시작
    while(K--){
        // 2-1. 모든 참가자 이동
        moveAll();

        // 2-2. 종료 조건 확인
        if(isFinish()) break;
        /*
          for(int i=1; i<=N; i++){
            for(int j=1; j<=N; j++){
                cout << maze[i][j] << ' ';
            }
            cout<< '\n';
        }
        cout<<"****************"<<'\n';
        */
        
        // 2-3. 미로 회전
        rotate();
        /*
                  for(int i=1; i<=N; i++){
            for(int j=1; j<=N; j++){
                cout << maze[i][j] << ' ';
            }
            cout<< '\n';
        }
        cout<<"########################"<<'\n';
        */
        

        
    }

    // 4. 출력 하기
    output();
}