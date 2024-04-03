/*
 * 2024.03.31
 * 내 풀이
 * 중간에 인덱스 num번째-1로 저장을 안하고 num번으로 저장해서 틀림
*/

#include <iostream>
#include <algorithm>
#include <climits>
#include <tuple>

#define MAX_P 30
#define ELIMINATED make_pair(-1, -1)

using namespace std;

int n, m, p, C, D;                  // n: 게임판 크기, m: 게임 턴 수, p: 산타 수, C: 루돌프 힘, D: 산타 힘
pair<int, int> santa_loc[MAX_P];    // 산타의 위치
pair<int, int> rudolf;              // 루돌프 위치
int faint[MAX_P];                   // 산타가 기절하게 되는 시간
int score[MAX_P];                   // 산타의 점수
int dirs[8][2] = {{-1,0},{0,1},{1,0},{0,-1},{-1,1},{1,1},{1,-1},{-1,-1}};    // 8방향, 앞의 4개는 상우하좌 우선순위           

void Input(){
    cin >> n >> m >> p >> C >> D;   // n: 게임판 크기, m: 게임 턴 수, p: 산타 수, C: 루돌프 힘, D: 산타 힘
    int r, c;                       // 루돌프 초기 위치
    cin >> r >> c;
    rudolf = make_pair(r-1, c-1);

    for(int i=0; i<p; i++){         // 산타 위치 입력 받
        int num, r, c;
        cin >> num >> r >> c;
        santa_loc[num-1] = make_pair(r-1, c-1);
    }
}

int GetDist(int x1, int y1, int x2, int y2){        // (x1, y1) ~ (x2, y2) 까지의 거리를 반환하는 함수
    return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}

bool InRange(int x, int y){         // (x, y)가 범위 안에 있는지 확인하는 함수 
    return 0 <= x && x < n && 0 <= y && y < n;
}

int MoveRudolf(){
    // 1. 가장 가까운 산타를 찾기
    int rx = rudolf.first, ry = rudolf.second;      // 루돌프 위치
    int minDist = INT_MAX, tx = -1, ty = -1;        // 최소 거리, 타겟 산타의 좌표
    for(int i=0; i<p; i++){
        if(santa_loc[i] == ELIMINATED) continue;    // 만약 탈락한 산타면 넘어가기
        int sx = santa_loc[i].first, sy = santa_loc[i].second;
        int curDist = GetDist(rx, ry, sx, sy);      // 현재 루돌프 위치에서 산타까지의 거리
        // 가장 가까운 산타, r좌표가 큰 산타, c좌표가 큰 산타 순 우선순위 따라서 선택하기
        if(make_tuple(minDist, -tx, -ty) > make_tuple(curDist, -sx, -sy)){
            minDist = curDist, tx = sx, ty = sy;
        }
    }

    // 2. 해당 산타로 가장 가까워지는 방향으로 돌진하기
    minDist = INT_MAX;      // 루돌프 현재 위치에서 한 칸 전진했을 때 (tx, ty)까지의 최소 거리 
    int direction;          // 최소 거리를 만드는 쪽으로 가는 방향
    for(int d=0; d<8; d++){
        int nx = rx + dirs[d][0], ny = ry + dirs[d][1];
        if(InRange(nx, ny)){    // 만야 범위 안에 있다면
            int curDist = GetDist(tx, ty, nx, ny);      // 타겟 산타부터 한칸 전진했을 때 칸까지의 거리
            if(minDist > curDist){
                minDist = curDist;
                direction = d;
            }
        }
    }

    // 3. 루돌프 이동하기
    // 최소 거리를 만드는 해당 방향으로 1칸 이동하기
    rudolf = make_pair(rudolf.first + dirs[direction][0], rudolf.second + dirs[direction][1]);  
    return direction;      // 해당 방향 리턴하기           
}

void Bump(int arrive_x, int arrive_y, int dir, int diff, int turn){     // 충돌을 처리하는 함수
    // 산타를 차례대로 보면서 (arrive_x, arrive_y)와 겹치는 것이 있는지 확인하기
    for(int i=0; i<p; i++){
        int sx = santa_loc[i].first, sy = santa_loc[i].second;
        if(arrive_x == sx && arrive_y == sy){
            // 만약 산타가 arrive자리에 있다면, 다음에 이동할 자리 구하기
            int nx = arrive_x + dirs[dir][0]*diff, ny = arrive_y + dirs[dir][1]*diff;
            // 그 해당 자리에 산타가 있는지 확인하고 있다면 1만큼 이동시키기
            Bump(nx, ny, dir, 1, turn);

            // 이제 비었으니 arrive 자리에다가 santa 업데이트하기
            santa_loc[i] = make_pair(nx, ny);

            // 그런데 만약 도착한 곳에 있던 산타가 루돌프와 위치가 같았다면
            if(arrive_x == rudolf.first && arrive_y == rudolf.second){
                faint[i] = turn+1;      // 산타 기절시키기
                score[i] += diff;          // 점수 증가하기
            }

            // 만약 nx, ny 자리가 범위를 넘어간다면 탈락했다 표시하기
            if(!InRange(nx, ny))
                santa_loc[i] = ELIMINATED;
        }
    }
}

bool IsExistSanta(int x, int y){        // (x, y) 자리에 산타가 존재하는지 확인하는 함수 
    for(int i=0; i<p; i++){
        if(santa_loc[i].first == x && santa_loc[i].second == y)
            return true;
    }
    return false;
}

int MoveSanta(int idx){     // idx번 산타를 루돌프와 가장 가까워지는 방향으로 1칸 이동시키는 함수
    // Step 1. 루돌프와 가장 가까워지는 방향 찾기
    int rx = rudolf.first, ry = rudolf.second;                  // 루돌프 위치
    int x = santa_loc[idx].first, y = santa_loc[idx].second;    // 현재 idx번 산타 위치
    int minDist = GetDist(x, y, rx, ry), direction = -1;
    for(int d=0; d<4; d++){
        int nx = x + dirs[d][0], ny = y + dirs[d][1];
        if(InRange(nx, ny) && !IsExistSanta(nx, ny)){     // 범위 안에 있고, 다른 산타가 없어야 이동가능
            int curDist = GetDist(nx, ny, rx, ry);
            if(minDist > curDist){      // 만약 현재까지 최소라면
                minDist = curDist, direction = d;
            }
        }
    }
    // Step 2. 산타 위치 업데이트
    if(direction != -1){    // 만약 움직일 수 있다면
        santa_loc[idx] = make_pair(x + dirs[direction][0], y + dirs[direction][1]);
    }
    // 산타가 이동해온 방향 리턴하기
    return direction;
}

bool Simulate(int turn){
    // Step 1. 루돌프 움직이기
    int rudolf_direction = MoveRudolf();

    // 1-1. 충돌 처리
    // rudolf자리에서 충돌이 일어났는지 확인하고, 충돌 시 점수 업데이트
    // (rudolfX, rudolfY)에서 충돌나면 rudolf_direction 방향으로 C만큼 산타 튕겨놔야 함
    Bump(rudolf.first, rudolf.second, rudolf_direction, C, turn); 

    // Step 2. 산타 움직이기
    for(int i=0; i<p; i++){     // 0번 ~ p-1번 산타 차례로 보면서 순서대로 움직이기
        if(santa_loc[i] == ELIMINATED) continue;        // 이미 탈락한 산타면 지나가기
        if(faint[i] >= turn)    continue;               // 기절해있는 산타면 넘어가기
        int santa_direction = MoveSanta(i);             // i번 산타 움직이기
        // 2-1. 충돌 처리
        if(santa_direction != -1)       // 만약 산타가 이동했다면 충돌났는지 확인해주기
            Bump(rudolf.first, rudolf.second, santa_direction ^ 2, D, turn);             
    }

    // Step 3. 탈락하지 않은 산타들에게 점수 1점 부여하기
    int remain_santa_cnt = 0;
    for(int i=0; i<p; i++){
        if(santa_loc[i] == ELIMINATED) continue;        // 이미 탈락한 산타면 넘어가기
        score[i]++;
        remain_santa_cnt++;
    }

    if(remain_santa_cnt == 0)       // 만약 남아있는 산타가 한 명도 없으면
        return false;               // 더 갈 수 없다는 의미로 false 반환
    return true;
}

void Output(){
    for(int i=0; i<p; i++){
        cout << score[i] << ' ';
    }
    cout << '\n';
}

int main() {
    // 입력 받기:
    Input();

    // M번의 턴에 걸쳐 시뮬레이션 시작
    for(int i=1; i<=m; i++){
        bool CanGo = Simulate(i);
        if(!CanGo)
            break;
    }

    // 출력하기:
    Output();
    return 0;
}