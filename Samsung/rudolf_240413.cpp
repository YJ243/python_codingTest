#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <tuple>
#include <climits>

#define MAX_P 30
#define LOST make_pair(-1, -1)

using namespace std;

int n, m, p, C, D;      // n: 게임판 크기, m: 게임 턴수, p: 산타 수, C: 루돌프 힘, D: 산타의 힘

pair<int, int> rudolf;  // 루돌프의 위치
pair<int, int> santa[MAX_P+1]; // santa[i]: i번 산타의 위치
int faint[MAX_P+1];     // faint[i]: i번 산타가 해당 시간까지 기절해있다.
int score[MAX_P+1];     // score[i]: i번 산타의 점수
int dirs[8][2] = {{-1,0},{0,1},{1,0},{0,-1},{-1,1},{1,1},{1,-1},{-1,-1}};     // 상우하좌, 대각선

void Input(){   // 입력을 받는 함수
    cin >> n >> m >> p >> C >> D;   // n: 게임판 크기, m: 게임 턴수, p: 산타 수, C: 루돌프 힘, D: 산타의 힘
    int r, c;
    cin >> r >> c;
    rudolf = make_pair(r-1, c-1);   // 루돌프 위치
    for(int i=0; i<p; i++){         // p명의 산타의 초기 위치 입력받기
        int num, r, c;
        cin >> num >> r >> c;
        santa[num] = make_pair(r-1, c-1);   // (r-1, c-1) 위치에 산타가 있음
    }
}

void Output(){
    for(int i=1; i<=p; i++){    // 각 산타가 얻은 최종 점수 출력
        cout << score[i] << ' ';
    }
    cout << '\n';
}

bool IsFinish(){    // 모든 산타가 게임에서 탈락했는지 확인하는 함수
    for(int i=1; i<=p; i++){
        if(santa[i] != LOST)
            return false;
    }
    return true;
}

int GetLength(int x1, int y1, int x2, int y2){  // (x1,y1) ~ (x2,y2)의 거리 구하기
    return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}

int FindClosestSanta(){
    int rx = rudolf.first, ry = rudolf.second;
    int minL = INT_MAX, maxR=0, maxC=0, targetIdx=0;

    for(int i=1; i<=p; i++){    // 1번부터 p번 산타 차례대로 보면서 타겟 산타 찾기
        if(santa[i] == LOST) continue;  // 탈락한 산타는 제외시키기
        int sx = santa[i].first, sy = santa[i].second;  // i번 산타의 위치
        int sL = GetLength(sx, sy, rx, ry);     // i번 산타에서 루돌프까지의 거리
        if(make_tuple(minL, -maxR, -maxC) > make_tuple(sL, -sx, -sy)){
            minL = sL, maxR = sx, maxC = sy, targetIdx = i;
        }
    }
    return targetIdx;
}

bool InRange(int x, int y){
    return 0 <= x && x < n && 0 <= y && y < n;
}

tuple<int, int, int> FindClosestLoctoSanta(int idx){
    int rx = rudolf.first, ry = rudolf.second;  // 루돌프 위치
    int sx = santa[idx].first, sy = santa[idx].second;  // 산타 위치
    int minL = GetLength(rx, ry, sx, sy), tX=0, tY=0, tD; // 새로운 루돌프 위치~산타 위치 거리, 새로운 루돌프 위치, 움직인 방향

    for(int d=0; d<8; d++){     // 인접한 8개 방향을 모두 확인하기
        int nx = rx + dirs[d][0], ny = ry + dirs[d][1]; // rudolf가 옮겨갈 위치
        if(!InRange(nx, ny)) continue;  // 범위를 벗어나면 넘어가기
        int nL = GetLength(nx, ny, sx, sy);     // 새로운 위치에서 타겟 산타까지의 거리
        if(minL > nL)   // 만약 새로운 위치가 더 가까워진다면
            minL = nL, tX = nx, tY = ny, tD = d;
    }
    return make_tuple(tX, tY, tD);
}

bool ExistSanta(int x, int y){
    for(int i=1; i<=p; i++){
        if(santa[i] == make_pair(x, y))
            return true;
    }
    return false;
}

int FindTargetSantaIdx(int x, int y){
    for(int i=1; i<=p; i++){
        if(santa[i] == make_pair(x, y)){
            return i;
        }
    }
}

void Bump(int idx, int x, int y, int d, int len){    // (x,y)에 있는 산타를 d 방향으로 len만큼 밀어내는 함수
    int nx = x + dirs[d][0]*len, ny = y + dirs[d][1]*len;
    // 만약 충돌해서 나간 곳이 범위 밖이라면
    if(!InRange(nx, ny)){   
        santa[idx] = LOST;  // 게임에서 탈락했다고 표시하기
        faint[idx] = INT_MAX;   // 무한대로 기절 표시
        return;
    }

    // 새로운 곳에 또 다른 산타가 없다면
    if(!ExistSanta(nx, ny)){
        // 산타 위치 업데이트 하기
        santa[idx] = make_pair(nx, ny);
        return;
    }
    // 새로운 곳에 또 다른 산타가 있다면
    else{
        int nextIdx = FindTargetSantaIdx(nx, ny);
        Bump(nextIdx, nx, ny, d, 1);            // 해당 산타를 또 1칸 밀어내기
        santa[idx] = make_pair(nx, ny);
    }
}

void MoveRudolf(int turn){      // 루돌프를 움직이는 함수
    // 1. 현재 위치에서 가장 가까운 산타를 찾기
    int targetIdx = FindClosestSanta();
        
    // 2. 해당 산타를 향해 1칸 돌진
    tuple<int, int, int> newLoc = FindClosestLoctoSanta(targetIdx);
    int nx, ny, dir;
    tie(nx, ny, dir) = newLoc;
    rudolf = make_pair(nx, ny);    // 루돌프 위치 업데이트
    
    // 3. 충돌 처리하기
    // 루돌프와 같은 위치에 있는 산타가 있는지 확인하기
    for(int i=1; i <= p; i++){
        if(santa[i] == LOST) continue;
        if(rudolf == santa[i]){
            Bump(i, nx, ny, dir, C);   // (nx, ny)에 있는 i번 산타를 dir방향으로 C만큼 밀어내는 함수
            faint[i] = turn+1;      // turn+1까지 기절시키기
            score[i] += C;          // 점수 C 증가
        }
    }
}

void MoveSanta(int idx, int turn){    // idx번 산타를 움직이는 함수
    // 1. 루돌프에게 가장 가까워지는 방향으로 움직이기, 상우하좌 우선순위
    int rx = rudolf.first, ry = rudolf.second;
    int sx = santa[idx].first, sy = santa[idx].second;
    int minL = GetLength(rx, ry, sx, sy), tX = sx, tY = sy, tD = 0;
    for(int d=0; d<4; d++){
        int nx = sx + dirs[d][0], ny = sy + dirs[d][1];
        // 만약 범위를 벗어나거나 다른 산타가 있다면 움직이지 않는다.
        if(!InRange(nx, ny) || ExistSanta(nx, ny)) continue;
        int currL = GetLength(rx, ry, nx, ny);
        if(minL > currL){
            minL = currL, tX = nx, tY = ny, tD = d;
        }
    }
    // 만약 움직일 수 없다면 리턴
    if(tX == sx && tY == sy) return;

    // 2. 해당 칸으로 움직이기
    santa[idx] = make_pair(tX, tY);

    // 3.  충돌 처리하기
    if(rx == tX && ry == tY){
        Bump(idx, tX, tY, (tD+2)%4, D);
        faint[idx] = turn+1;
        score[idx] += D;
    }
}

void Simulate(int turn){    // turn 번째 시뮬레이션 진행하는 함수
    // Step 1. 루돌프 움직이기
    MoveRudolf(turn);
    
    // Step 2. 산타 움직이기
    for(int i=1; i<=p; i++){
        // 이미 탈락했거나 기절한 산타는 움직일 수 없음
        if(santa[i] == LOST || faint[i] >= turn)
            continue;
        MoveSanta(i, turn);       // i번 산타를 turn번째 턴에서 움직이기
    }
    
    // Step 3. 점수 추가하기
    for(int i=1; i<=p; i++){
        // 매 턴 이후 아직 탈락하지 않은 산타들에게 1점씩 추가로 부여하기
        if(santa[i] == LOST) continue;  
        score[i]++; // i번 산타 1점 추가
        
    }
}

int main() {
    // 입력 받기:
    Input();
    
    // m번의 턴에 걸쳐 시뮬레이션 진행
    for(int turn=1; turn <= m; turn++){
        if(IsFinish())  // 만약 게임이 끝났다면 반복문 나가기
            break;
        Simulate(turn);     // turn번째 시뮬레이션 진행
    }

    // 출력하기:
    Output();
    return 0;
}
