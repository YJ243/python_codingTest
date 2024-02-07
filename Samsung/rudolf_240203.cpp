#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <climits>

#define MAX_N 50
#define MAX_P 30
using namespace std;

int n, m, p, c, d;  // n: 게임판 크기, m: 게임 턴 수, p: 산타 수, c: 루돌프 힘, d: 산타 

pair<int, int> SantaLoc[MAX_P+1]; // SantaLoc[i]: i번 산타의 위치 좌표
int faint[MAX_P+1];               // faint[i]: i번 산타가 기절해있는 시간 
int score[MAX_P+1];               // score[i]: i번 산타의 점수
bool IsFail[MAX_P+1];              // IsFail[i]: i번 산타가 탈락했는지

int grid[MAX_N][MAX_N];           // 격자판, 0: 빈칸, 1~ 양수: 산타 번호, -1: 산타 위치
// 방향을 나타내는 배열, 상우하좌 우선순위 + 4가지 대각선방향
int dxs[8] = {-1,0,1,0,-1,1,1,-1};
int dys[8] = {0,1,0,-1,1,1,-1,-1};

pair<int, int> GetRudolfLoc(){     // 루돌프 위치를 반환하는 함수
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(grid[i][j] == -1){
                return make_pair(i,j);
            }
        }
    }
}

void Input(){                       // 입력받는 함수
    // n: 게임판 크기, m: 게임 턴 수, p: 산타 수, c: 루돌프 힘, d: 산타 
    cin >> n >> m >> p >> c >> d;
    // 루돌프 위치
    int r, c;
    cin >> r >> c;  
    grid[r-1][c-1] = -1;             // 격자에 루돌프 위치 표기
    // 산타 위치 입력받기
    for(int i=0; i<p; i++){ 
        int idx,sx, sy;
        cin >> idx >> sx >> sy;
        SantaLoc[idx] = make_pair(sx-1,sy-1);
        grid[sx-1][sy-1] = idx;
    }
}

void Output(){                      // 산타의 최종 점수를 출력하는 함수
    for(int i=1; i<=p; i++){
        cout << score[i] << ' ';
    }
    cout << '\n';
}

void PrintGrid(){                   // 격자 현재 상태 출력
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << grid[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

int GetDist(int x1, int y1, int x2, int y2){ // (x1, y1) ~ (x2, y2) 까지의 거리를 구해주는 함수
    return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}

bool InRange(int x, int y){         // 범위 안에 있는지 확인하는 함수
    return 0 <= x && x < n && 0 <= y && y < n;
}

int FindClosestSanta(){      // 루돌프에서 가장 가까운 산타를 찾아 인덱스를 반환하는 함수
    int RudolfX, RudolfY;
    tie(RudolfX, RudolfY) = GetRudolfLoc();

    int minDist = INT_MAX, maxX = 0, maxY = 0;  // 산타부터 가장 가까운 산타까지 거리, 그때의 산타 좌표 구하기
    for(int i=1; i<=p; i++){
        // p명의 산타를 확인하면서 가장 가까운 산타 구하기
        if(IsFail[i]) continue;     // 게임에서 탈락했다면 넘어가기
        int SantaX, SantaY;
        tie(SantaX, SantaY) = SantaLoc[i];
        int curDist = GetDist(RudolfX, RudolfY, SantaX, SantaY);
        if(minDist > curDist){      // 만약 현재 최소 거리보다 더 가까운 산타를 만났다면
            minDist = curDist;
            maxX = SantaX, maxY = SantaY;
        }
        else if(minDist == curDist){    // 만약 최소 거리가 같은경우
            if(maxX < SantaX || (maxX == SantaX && maxY < SantaY)){   // 우선순위 대로 처리
                minDist = curDist;
                maxX = SantaX, maxY = SantaY;
            }
        }
    }
    return grid[maxX][maxY];
}

tuple<int, int, int> FindClosestDistToSanta(){
    // 게임에서 탈락하지 않은 가장 가까운 산타 찾기
    int tgt = FindClosestSanta();
    int sx, sy;
    tie(sx, sy) = SantaLoc[tgt];

    int rx, ry;     // 루돌프 위치
    tie(rx, ry) = GetRudolfLoc();
    int minDist = GetDist(rx, ry, sx,sy);   // 산타부터 가장 가까운 산타까지 거리
    int minX = 0, minY = 0, minD = 0;                 // 그때의 산타 좌표와 방향 구하기
    for(int d=0; d<8; d++){
        int nx = rx+dxs[d], ny = ry+dys[d];
        int curDist = GetDist(sx, sy, nx, ny);
        if(InRange(nx,ny) and minDist > curDist){
            minDist = curDist, minX = nx, minY = ny, minD = d;
        }
    }
    return make_tuple(minX, minY, minD);
}



void Bump(int id, int dX, int dY, int RudolfMove, int turn){        //  (x,y) 자리에 direction 방향으로 이동했을 때 충돌 처리, 누가 이동했는지는 RudolfMove로 보기
    // id번 산타가 움직여야 함
    int sx, sy;
    tie(sx, sy) = SantaLoc[id];
    int dx,dy, dist, plus_score;
    // 만약 RudolfMove가 참이면 Santa는 direction방향으로 c만큼 움직이기 
    if(RudolfMove==1){
        dx = dX, dy = dY;
        dist = c;
        plus_score = c;
    }
    // 만약 RudolfMove가 거짓이면 Satna는 -direction 방향으로 d-1만큼 움직이기
    else if(RudolfMove==0){
        dx = -dX, dy = -dY;
        dist = d-1;    
        plus_score = d;
    }
    else{ // 상호작용 한 아이라면
        dx = dX, dy = dY;
        dist = 1;
        plus_score = 0;
    }
    int firstX = sx+dx*dist, firstY = sy+dy*dist;
    //cout << "움직일 곳" << firstX << ' ' <<firstY << ' ' << dist <<'\n';
    if(!InRange(firstX, firstY)){
        // 만약 튕겨나가 자리가 범위를 벗어난다면
        // id번 산타는 탈락
        faint[id] = INT_MAX;
        IsFail[id] = true;
        grid[sx][sy] = 0;

    }
    else{   // 범위 안에 있다면
        if(grid[firstX][firstY] != 0){
            //cout << grid[firstX][firstY] << ' ' << firstX << ' ' <<firstY << '\n';
            // 튕겨난 곳에 산타가 있다면
            // 상호작용하면서 산타 밀기
            if(firstX != sx || firstY != sy)
                Bump(grid[firstX][firstY], dx, dy, 2, turn);
        }
        // 그럼 이제 firstX, firstY가 비어있는 상황
        // 여기로 이동시키기
        grid[sx][sy] = 0;   // 원래 산타가 있던 자리는 0으로 표기
        SantaLoc[id] = make_pair(firstX, firstY);   // 산타 위치 바꿔주기
        grid[firstX][firstY] = id;

    }
    // id번 산타 점수 증가시키기
    score[id] += plus_score;
    return;
}

void MoveRudolf(int turn){                  // 루돌프를 이동시키는 함수
    int rx, ry;     // 루돌프 위치
    tie(rx, ry) = GetRudolfLoc();

    // Step 1. 가장 가까운 산타로 가장 가까워지는 방향으로 돌진
    // 2-1. 돌진할 좌표 구하기
    int toX, toY, toD;
    tie(toX, toY, toD) = FindClosestDistToSanta();

    // 2-2. 충돌 여부 확인
    int id = 0;
    if(grid[toX][toY] != 0){
        // 만약 산타가 있다면
        id = grid[toX][toY];
        //cout << "루돌프가 이동해서 충돌" << id << ' ' << toX << ' ' <<toY << '\n';
        Bump(id, dxs[toD],dys[toD], 1, turn);      // (toX, toY) 자리에서 충돌 처리, 해당 칸을 빈칸으로 만들기
    }
    if(!IsFail[id])
        faint[id] = turn+1;  // id번 산타는 기절
    grid[rx][ry] = 0;       // 원래 루돌프가 있는 칸을 빈칸으로 만들기
    grid[toX][toY] = -1;    // 루돌프 옮겨주기

}

void MoveSanta(int id, int turn){             // turn번째 턴에 id번 산타 이동시키기
    int rx, ry; tie(rx, ry) = GetRudolfLoc();    // 루돌프 위치
    int sx, sy; tie(sx, sy) = SantaLoc[id];     // 현재 움직이려는 산타 위치
    int curDist = GetDist(sx, sy, rx, ry);
    int minDist = curDist;

    int minX = 0, minY = 0, minDX, minDY;  // 루돌프로 가장 가까워지는 방향으로 가는 좌표 구하기
    for(int d=0; d<4; d++){
        int nx = sx+dxs[d], ny = sy+dys[d];

        if(InRange(nx,ny) && grid[nx][ny] <= 0 && minDist > GetDist(nx,ny,rx,ry)){
            minDist = GetDist(nx,ny,rx,ry), minX = nx, minY = ny, minDX = dxs[d], minDY = dys[d];
        }
    }
    if(minDist == curDist){
        // 만약 해당 산타를 움직일 수 없다면 바로 리턴
        return;
    }

    if(grid[minX][minY] == -1){
        //cout << "루돌프" << sx << ' ' << sy << '\n';
        // 만약 해당 좌표에 루돌프 있다면
        Bump(id, minDX,minDY, 0, turn);       // 충돌 처리
        if(!IsFail[id])
            faint[id] = turn+1;  // id번 산타는 기절
    }
    else{
        // 산타가 없는 빈칸이라면 이동시켜주기
        grid[sx][sy] = 0;
        SantaLoc[id] = make_pair(minX, minY);
        grid[minX][minY] = id;
    }
    //cout << id << ": " << minX << ' ' << minY << '\n';

}

void Simulate(int turn){            // turn번째 턴 게임 시작
    // Step 1. 루돌프 이동시키기
    MoveRudolf(turn);

    // Step 2. 산타 이동시키기
    for(int i=1; i<=p; i++){
        // 1번부터 p번까지 산타를 차례대로 이동
        if(IsFail[i] or faint[i] >= turn) continue;     // 게임에서 탈락했거나, 기절한 산타라면 넘어가기
        MoveSanta(i, turn);

    }
    //PrintGrid();
    // Step 3. 탈락하지 않은 산타들에 대해 점수 1 증가시키기
    for(int i=1; i<=p; i++){
        if(!IsFail[i]) 
            score[i]++;
    }
    //Output();
    /*
    for(int i=1; i<=p; i++){
        cout << faint[i] << ' ';
    }
    cout << '\n';
    */
}

bool IsFinish(){  // 게임이 종료됐는지 확인
    for(int i=1; i<=p; i++){
        if(!IsFail[i]){
            // 산타가 남아있다면
            return false;
        }
    }
    return true;
}

int main() {
    // 입력 받기:
    Input();

    // M번의 턴에 걸쳐 루돌프, 산타가 순서대로 움직임
    for(int i=1; i<=m; i++){
        if(IsFinish()) break;   // 만약 게임이 종료됐다면 반복문 나가기
        Simulate(i);
        //cout << '\n';
    }

    //cout << "hey" << '\n';
    // 결과 출력:
    Output();
    return 0;
}